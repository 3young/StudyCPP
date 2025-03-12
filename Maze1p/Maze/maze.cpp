#include "maze.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <random>
#include <locale>

Maze::Maze(int width, int height) : width(width), height(height), playerX(1), playerY(1)
{
    GenerateMaze();
}

void Maze::GenerateMaze()
{
    srand(time(nullptr));

    // 모든 칸을 벽으로 초기화
    maze = std::vector<std::vector<wchar_t>>(height, std::vector<wchar_t>(width, L'█'));

    // 출발점(ⓟ) 설정
    startX = 1;
    startY = 1;
    maze[startY][startX] = L'ⓟ';

    // 목표 지점(★) 설정
    int goalX = width - 2;
    int goalY = height - 2;

    // 경로 생성
    CarveMaze(startX, startY);

    // 목표 지점까지 경로를 보장하기 위해 EnsurePath 실행
    if (!EnsurePath(startX, startY, goalX, goalY))
    {
        // 경로가 보장되지 않으면 목표 지점 삭제하고 다시 시도
        maze[goalY][goalX] = L' '; // 목표 지점 삭제
        EnsurePath(startX, startY, goalX, goalY);
        maze[goalY][goalX] = L'★'; // 목표 지점 재설정
    }

    // 목표 지점이 벽에 막히지 않도록 경로를 생성한 후, 목표 지점으로 설정
    maze[goalY][goalX] = L'★';
}




void Maze::PathBetweenStartAndGoal(int startX, int startY, int goalX, int goalY)
{
    // 출발점과 목표 지점 사이에 경로를 생성하는 함수
    int x = startX, y = startY;

    // 가로로 연결
    if (x < goalX) {
        for (int i = x; i <= goalX; i++) {
            maze[y][i] = L' ';
        }
    }
    else {
        for (int i = x; i >= goalX; i--) {
            maze[y][i] = L' ';
        }
    }

    // 세로로 연결
    if (y < goalY) {
        for (int i = y; i <= goalY; i++) {
            maze[i][goalX] = L' ';
        }
    }
    else {
        for (int i = y; i >= goalY; i--) {
            maze[i][goalX] = L' ';
        }
    }
}

void Maze::CarveMaze(int x, int y)
{
    std::vector<std::pair<int, int>> directions = { {2, 0}, {-2, 0}, {0, 2}, {0, -2} };
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(directions.begin(), directions.end(), g);  // 방향 무작위 섞기

    for (const auto& [dx, dy] : directions)
    {
        int nx = x + dx;
        int ny = y + dy;

        if (nx > 0 && nx < width - 1 && ny > 0 && ny < height - 1 && maze[ny][nx] == L'█')
        {
            maze[ny][nx] = L' ';              // 새로운 경로 만들기
            maze[y + dy / 2][x + dx / 2] = L' '; // 벽을 제거하여 경로 연결

            // 새롭게 만들어진 경로에서 다시 CarveMaze 호출
            CarveMaze(nx, ny);
        }
    }
}


bool Maze::EnsurePath(int x, int y, int goalX, int goalY)
{
    // 목표 지점까지 연결된 경로를 보장하는 함수
    std::vector<std::pair<int, int>> stack;
    stack.push_back({ x, y });
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));
    visited[y][x] = true;

    std::random_device rd;
    std::mt19937 g(rd());

    while (!stack.empty())
    {
        auto [cx, cy] = stack.back();
        stack.pop_back();

        // 목표지점에 도달하면 경로를 연결
        if (cx == goalX && cy == goalY)
        {
            maze[cy][cx] = L' ';  // 목표 지점은 경로로 설정
            return true;
        }

        std::vector<std::pair<int, int>> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
        std::shuffle(directions.begin(), directions.end(), g);

        for (const auto& [dx, dy] : directions)
        {
            int nx = cx + dx;
            int ny = cy + dy;

            // 방문하지 않은 칸이면서, 벽이 아니면 스택에 추가
            if (nx >= 0 && nx < width && ny >= 0 && ny < height && maze[ny][nx] == L' ' && !visited[ny][nx])
            {
                stack.push_back({ nx, ny });
                visited[ny][nx] = true;
                maze[ny][nx] = L' '; // 경로를 공백으로 설정
            }
        }
    }

    // 경로 보장 안될 경우 강제로 경로를 연결
    maze[goalY][goalX] = L' ';  // 강제로 목표 지점 연결
    return true;
}



void Maze::Display() const
{
    std::wcout.imbue(std::locale("ko_KR.UTF-8"));  // 올바른 로케일 설정
    for (const auto& row : maze)
    {
        for (const auto& cell : row)
        {
            if (cell == L' ')
            {
                std::wcout << L"  "; // 공백을 두 번 출력
            }
            else if (cell == L'ⓟ')
            {
                std::wcout << L"ⓟ"; // 출발점을 ⓟ로 출력
            }
            else if (cell == L'★')
            {
                std::wcout << L"★"; // 목표지점을 ★로 출력
            }
            else
            {
                std::wcout << L"██"; // 벽을 두 번 출력
            }
        }
        std::wcout << std::endl;
    }
}



bool Maze::MovePlayer(char direction)
{
    int newX = playerX;
    int newY = playerY;

    switch (direction)
    {
    case 'w': newY--; break;
    case 'a': newX--; break;
    case 's': newY++; break;
    case 'd': newX++; break;
    default: return false;
    }

    if (newX < 0 || newX >= width || newY < 0 || newY >= height || maze[newY][newX] == L'█')
    {
        return false;
    }

    if (maze[newY][newX] == L'★')
    {
        std::wcout << L"Congratulations! You've reached the goal!" << std::endl;
        return true;
    }

    // 이동 후 플레이어 위치 업데이트
    maze[playerY][playerX] = L' '; // 이전 플레이어 위치는 공백으로
    playerX = newX;
    playerY = newY;
    maze[playerY][playerX] = L'ⓟ'; // 새로운 플레이어 위치에 출발점 표시

    return false;
}

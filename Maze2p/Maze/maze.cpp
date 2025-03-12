
#include "maze.h"
#include "TwoPlayerGame.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <random>
#include <locale>
#include <conio.h>
#include <thread>
#include <chrono>


const std::vector<std::vector<wchar_t>>& Maze::GetMaze() const
{
    return maze;
}

int Maze::GetWidth() const
{
    return width;
}

int Maze::GetHeight() const
{
    return height;
}

Maze::Maze(int width, int height) : width(width), height(height), player1X(1), player1Y(1), player2X(1), player2Y(1)
{
    GenerateMaze();
}

void Maze::GenerateMaze()
{
    srand(time(nullptr));

    maze = std::vector<std::vector<wchar_t>>(height, std::vector<wchar_t>(width, L'█'));

    // 시작 위치와 도착 지점 설정
    startX = 1;
    startY = 1;
    maze[startY][startX] = L'☆';

    int goalX = width - 2;
    int goalY = height - 2;

    CarveMaze(startX, startY);

    if (!EnsurePath(startX, startY, goalX, goalY))
    {
        // 경로가 보장되지 않으면 목표 지점 삭제하고 다시 시도
        maze[goalY][goalX] = L' ';  // 목표 지점 삭제
        EnsurePath(startX, startY, goalX, goalY);
        maze[goalY][goalX] = L'★'; // 목표 지점 재설정
    }

    // 목표 지점이 벽에 막히지 않도록 경로 생성 후, 목표 지점으로 설정
    maze[goalY][goalX] = L'★';
}



void Maze::PathBetweenStartAndGoal(int startX, int startY, int goalX, int goalY)
{
    // 출발점과 목표 지점 사이에 경로를 생성하는 함수
    int x = startX, y = startY;

    // 가로로 연결
    if (x < goalX) {
        for (int i = x; i <= goalX; i++)
        {
            maze[y][i] = L' ';
        }
    }
    else {
        for (int i = x; i >= goalX; i--)
        {
            maze[y][i] = L' ';
        }
    }

    // 세로로 연결
    if (y < goalY) {
        for (int i = y; i <= goalY; i++)
        {
            maze[i][goalX] = L' ';
        }
    }
    else {
        for (int i = y; i >= goalY; i--)
        {
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
            maze[ny][nx] = L' ';                 // 새로운 경로 만들기
            maze[y + dy / 2][x + dx / 2] = L' '; // 벽을 제거하여 경로 연결

            // 새로운 경로에서 다시 CarveMaze 호출
            CarveMaze(nx, ny);
        }
    }
}



bool Maze::EnsurePath(int x, int y, int goalX, int goalY)
{
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


bool Maze::MovePlayer(char direction, int playerNumber)
{
    int newX, newY;
    if (playerNumber == 1)
    {
        newX = player1X;
        newY = player1Y;
    }
    else
    {
        newX = player2X;
        newY = player2Y;
    }

    switch (direction)
    {
    case 'w': newY--; break;
    case 'a': newX--; break;
    case 's': newY++; break;
    case 'd': newX++; break;
    case 'i': newY--; break;
    case 'j': newX--; break;
    case 'k': newY++; break;
    case 'l': newX++; break;
    default: return false;
    }

    if (newX < 0 || newX >= width || newY < 0 || newY >= height || maze[newY][newX] == L'█')
    {
        return false;
    }

    if (maze[newY][newX] == L'★')
    {
        return true; // 게임 종료
    }

    if (playerNumber == 1)
    {
        maze[player1Y][player1X] = (player1X == startX && player1Y == startY) ? L'☆' : L' ';
        player1X = newX;
        player1Y = newY;
        maze[player1Y][player1X] = L'ⓟ';
    }
    else
    {
        maze[player2Y][player2X] = (player2X == startX && player2Y == startY) ? L'☆' : L' ';
        player2X = newX;
        player2Y = newY;
        maze[player2Y][player2X] = L'ⓟ';
    }
    return false;
}

void ClearScreen()
{
#ifdef _WIN32
    system("chcp 65001");
    system("cls");
#else
    system("clear");
#endif
}

void DisplayGameStartScreen()
{
    std::wcout.imbue(std::locale("ko_KR.UTF-8"));
    system("cls");
    std::wcout << L"\n\n\n\n\n\n"<< std::endl;
    std::wcout << L"                                       ████████████████████████████" << std::endl;
    std::wcout << L"                                       ██                        ██" << std::endl;
    std::wcout << L"                                       ██       GAME START       ██" << std::endl;
    std::wcout << L"                                       ██                        ██" << std::endl;
    std::wcout << L"                                       ████████████████████████████" << std::endl;
    std::wcout << L"\n\n                                      Press Enter to start the game..." << std::endl;

    while (!_kbhit() || _getch() != 13) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::wcout << L"                                      Starting game..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    ClearScreen();

}



void GameLoop()
{
    const int width = 51;
    const int height = 21;

    while (true)
    {
        // 게임 시작
        TwoPlayerGame game(width, height);
        game.Display();

        while (true)
        {
            if (_kbhit())
            {
                int direction = _getch();

                if (direction == 27)  // Esc로 게임 종료
                {
                    return; // 게임 종료
                }
                else if (direction == 13)  // Enter로 게임 종료
                {
                    return; // 게임 종료
                }

                // 플레이어 1의 이동 (WASD 키)
                if (direction == 'w' || direction == 'a' || direction == 's' || direction == 'd')
                {
                    game.MovePlayer(direction, 1);
                }
                // 플레이어 2의 이동 (IJKL 키)
                if (direction == 'i' || direction == 'j' || direction == 'k' || direction == 'l')
                {
                    game.MovePlayer(direction, 2);
                }

                // 게임 화면 업데이트
                ClearScreen();
                game.Display();
            }
        }
    }
}



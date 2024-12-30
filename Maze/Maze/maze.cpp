#include "Maze.h"
#include <iostream>
#include <ctime> 
#include <cstdlib>

Maze::Maze(int width, int height) : width(width), height(height), playerX(1), playerY(1)
{
    GenerateMaze();
}

void Maze::GenerateMaze()
{
    srand(time(nullptr));

    maze = std::vector<std::string>(height, std::string(width, '#'));

    // 출발점
    startX = 1;
    startY = 1;
    maze[startY][startX] = 'S';

    // 플레이어 시작 위치 설정 
    playerX = startX;
    playerY = startY;
    maze[playerY][playerX] = 'P'; // 플레이어 위치

    // 목표지점 설정 
    int goalX = width - 2;
    int goalY = height - 2;
    maze[goalY][goalX] = 'G';

    // 랜덤으로 길 생성
    for (int y = 1; y < height - 1; y++)
    {
        for (int x = 1; x < width - 1; x++)
        {
            if (rand() % 4 != 0)
            {
                maze[y][x] = '.';
            }
        }
    }

    maze[startY][startX] = 'S';
    maze[goalY][goalX] = 'G';
}

void Maze::Display() const
{ 
    for (const auto& row : maze) 
    { 
        std::cout << row << std::endl; 
    } 
}

bool Maze::MovePlayer(char direction)
{
 int newX = playerX; 
 int newY = playerY; 

 switch (direction)
 { 
     case 'w': newY--; 
     break; 
     
     case 'a': newX--; 
     break; 
     
     case 's': newY++; 
     break; 
     
     case 'd': newX++; 
     break; 
     
     default: return false; 
 } 
 
 if (newX < 0 || newX >= width || newY < 0 || newY >= height || maze[newY][newX] == '#') 
 { 
     return false; 
 } 
 
 if (maze[newY][newX] == 'G') 
 { 
     std::cout << "Congratulations! You've reached the goal!" << std::endl; 
     return true; 
 } 
 
 std::swap(maze[playerY][playerX], maze[newY][newX]); 
 maze[playerY][playerX] = '.'; // 이전 플레이어 위치
 maze[newY][newX] = 'P';       // 새로운 플레이어 위치 
 playerX = newX; 
 playerY = newY; 
 return false; 
}

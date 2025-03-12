#include "TwoPlayerGame.h"
#include "maze.h"
#include <iostream>
#include <cstdlib>
#include <conio.h>


TwoPlayerGame::TwoPlayerGame(int width, int height) :
    maze1(width / 2 - 2, height), maze2(width / 2 - 2, height), player1X(1), player1Y(1), player2X(width / 2 + 2), player2Y(1), width(width), height(height)
{
}

void TwoPlayerGame::Display() const
{
    std::wcout.imbue(std::locale("ko_KR.UTF-8"));

    const auto& maze1Data = maze1.GetMaze();
    const auto& maze2Data = maze2.GetMaze();
    int maze1Width = maze1.GetWidth();
    int maze2Width = maze2.GetWidth();
    int mazeHeight = maze1.GetHeight(); // maze1, maze2의 height는 동일

    for (int y = 0; y < mazeHeight; ++y)
    {
        // 왼쪽 미로
        for (int x = 0; x < maze1Width; ++x)
        {
            if (y == player1Y && x == player1X)
            {
                std::wcout << L'☆';
            }
            else if (maze1Data[y][x] == L' ')
            {
                std::wcout << L"  ";
            }
            else if (maze1Data[y][x] == L'☆')
            {
                std::wcout << L"☆";
            }
            else if (maze1Data[y][x] == L'ⓟ')
            {
                std::wcout << L"ⓟ";
            }
            else if (maze1Data[y][x] == L'★')
            {
                std::wcout << L"★";
            }
            else
            {
                std::wcout << L"██";
            }
        }

        // 두 미로 사이에 공백 추가
        std::wcout << L"      ";

        // 오른쪽 미로
        for (int x = 0; x < maze2Width; ++x)
        {
            if (y == player2Y && x == player2X)
            {
                std::wcout << L'☆';
            }
            else if (maze2Data[y][x] == L' ')
            {
                std::wcout << L"  ";
            }
            else if (maze1Data[y][x] == L'☆')
            {
                std::wcout << L"☆";
            }
            else if (maze2Data[y][x] == L'ⓟ')
            {
                std::wcout << L"ⓟ";

            }
            else if (maze2Data[y][x] == L'★')
            {
                std::wcout << L"★";
            }
            else
            {
                std::wcout << L"██";
            }
        }

        std::wcout << std::endl;
    }
}



void TwoPlayerGame::MovePlayer(char direction, int playerNumber)
{
    bool gameWon = false;
    switch (direction)
    {
    case 'w':
    case 'a':
    case 's':
    case 'd':
    case 'i':
    case 'j':
    case 'k':
    case 'l':
        // 플레이어의 이동을 처리합니다.
        if (playerNumber == 1)
        {
            gameWon = maze1.MovePlayer(direction, 1); // 플레이어 1의 이동
        }
        else if (playerNumber == 2)
        {
            gameWon = maze2.MovePlayer(direction, 2); // 플레이어 2의 이동
        }
        break;
    }

    // 게임 종료 처리
    if (gameWon)
    {
        std::wcout << std::endl << std::endl << L"                                          Player " << playerNumber << L" wins!" << std::endl;
        std::wcout << L"                                        게임이 끝났습니다!" << std::endl;
        std::wcout << std::endl << L"                                        Enter를 눌러 종료..." << std::endl;
        std::cin.get(); // 화면 유지
    }
}



bool TwoPlayerGame::IsGameOver() const
{
    return maze1.GetMaze()[player1Y][player1X] == L'★' || maze2.GetMaze()[player2Y][player2X] == L'★';
}

#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <locale>
#include <string>

class Maze
{
public:
    const std::vector<std::vector<wchar_t>>& GetMaze() const;
    int GetWidth() const;
    int GetHeight() const;
    Maze(int width, int height);
    bool MovePlayer(char direction, int playerNumber);

private:
    void GenerateMaze();
    void CarveMaze(int x, int y);
    bool EnsurePath(int x, int y, int goalX, int goalY);
    void PathBetweenStartAndGoal(int startX, int startY, int goalX, int goalY);

    std::vector<std::vector<wchar_t>> maze;
    int width;
    int height;
    int player1X, player1Y;
    int player2X, player2Y;
    int startX;
    int startY;
};

void DisplayGameStartScreen();
void GameLoop();


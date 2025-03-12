#pragma once
#include "maze.h"
#include <iostream>

class TwoPlayerGame
{
public:
    TwoPlayerGame(int width, int height);
    void Display() const;
    void MovePlayer(char direction, int playerNumber);
    bool IsGameOver() const;

private:
    Maze maze1;
    Maze maze2;
    int player1X, player1Y;
    int player2X, player2Y;
    int width;
    int height;

};
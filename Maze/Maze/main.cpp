#include "maze.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void ClearScreen() {
#ifdef _WIN32
    system("chcp 65001");
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    const int width = 15;
    const int height = 15;
    Maze maze(width, height);
    maze.Display();

    std::wcout << std::endl;
    char direction;

    while (true) {
        std::wcout << "Move (w/a/s/d): ";
        std::cin >> direction;
        if (maze.MovePlayer(direction)) 
        {
            break;
        }
        ClearScreen();
        maze.Display();
    }

    return 0;
}

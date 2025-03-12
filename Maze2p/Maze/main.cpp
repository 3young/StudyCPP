#pragma once
#include "TwoPlayerGame.h"
#include <iostream>
#include <conio.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif



int main()
{
    // 게임 시작 화면 표시
    DisplayGameStartScreen();

    // 게임 루프 시작
    GameLoop();

    return 0;
}

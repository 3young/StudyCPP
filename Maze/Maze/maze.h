#pragma once
#include <vector>
#include <string>

class Maze
{
public:
    Maze(int width, int height);
    void Display() const;
    bool MovePlayer(char direction);

private:
    void GenerateMaze();
    void CarveMaze(int x, int y); 
    bool EnsurePath(int x, int y, int goalX, int goalY);  
    void PathBetweenStartAndGoal(int startX, int startY, int goalX, int goalY);  // 출발점과 목표 지점 사이 경로 생성 함수

    std::vector<std::vector<wchar_t>> maze;
    int width;
    int height;
    int playerX;
    int playerY;
    int startX;
    int startY;
};


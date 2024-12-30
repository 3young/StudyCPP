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

	std::vector<std::string> maze; 
	int width; 
	int height; 
	int playerX; 
	int playerY; 
	int startX; 
	int startY;
};
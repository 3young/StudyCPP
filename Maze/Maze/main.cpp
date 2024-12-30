#include "Maze.h" 
#include <iostream> 

int main() 
{ 
	const int width = 11; 
	const int height = 11; 

	Maze maze(width, height); 
	maze.Display(); 

	char direction; 
	while (true) 
	{ 
		std::cout << "Move (w/a/s/d): \n\n"; 
		std::cin >> direction; 
		
		if (maze.MovePlayer(direction)) 
		{
			break; 
		} 

		maze.Display(); 
	}

	return 0; 
}
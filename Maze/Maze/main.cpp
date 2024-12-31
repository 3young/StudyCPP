#include "Maze.h" 
#include <iostream> 

#ifdef _WIN32 
#include <windows.h> 
#else 
#include <unistd.h>
#endif


void ClearScreen() 
{ 
#ifdef _WIN32 
	system("cls"); 
#else 
	system("clear"); 
#endif 
}

int main() 
{ 
	const int width = 15; 
	const int height = 15; 

	Maze maze(width, height); 
	maze.Display(); 
	std::cout << std::endl;


	char direction; 
	while (true) 
	{ 
		std::cout << "Move (w/a/s/d): \n\n"; 
		std::cin >> direction; 
		
		if (maze.MovePlayer(direction)) 
		{
			break; 
		} 

		ClearScreen(); // 화면 지우기 
		maze.Display();	
	}

	return 0; 
}
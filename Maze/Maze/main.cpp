#include "Maze.h" 
#include <iostream> 

// 미로생성알고리즘 사용

// 무조건 길 뚫기
// 시작점-도착점까지 랜덤 경로 만들기 (벽을 일정 길이 이상)

// 추가 시스템 생각해보기
// 특수문자로 맵 변경
// 타임어택
// 타이틀

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
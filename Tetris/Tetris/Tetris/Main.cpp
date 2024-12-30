#include <iostream>
#include "GameManager.h"
#include "Test.h"

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

#ifdef _TEST_MODE		// _TEST_MODE이 디파인되어 있으면 컴파일러에서 포함, 되어 있지 않으면 컴파일러에서 포함하지 않음
	Test test;
	test.Test_Output();	
	//test.Test_Input();	// 내부에서 무한 루프를 돌린다.
	test.Test_Logger();
	test.Test_Functional();
	//test.Test_Input_Functional();	// 내부에서 무한 루프 돌린다.	
	test.Test_Tetromino();
#endif // _TEST_MODE

	GameManager& manager = GameManager::Get();
	manager.Initialize();

#ifdef _TEST_MODE		
	// test.Test_Input_System();
	test.Test_Random();
#endif

	while (true)
	{
		manager.Loop();
	}

	manager.Destroy();	

	
	return 0;
}
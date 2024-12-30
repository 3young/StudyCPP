#include "ConsoleDoubleBuffer.h"

void ConsoleDoubleBuffer::Initialize()
{
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);	// 콘솔의 표준 출력용 핸들 가져오기

	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;			// 콘솔의 정보 저장용
	GetConsoleScreenBufferInfo(hStd, &consoleInfo);	// 표준 출력용 핸들에서 콘솔정보 가져오기
	consoleInfo.dwSize.X = BUFFER_WIDTH;			// 크기를 내가 지정해 놓은 크기로 설정
	consoleInfo.dwSize.Y = BUFFER_HEIGHT;

	CONSOLE_CURSOR_INFO consoleCursor{ 1, FALSE };	// 커서 정보 설정(커서 크기는 1이고 가시성은 안보이게 설정)

	hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);	// 새 버퍼 생성
	SetConsoleScreenBufferSize(hBuffer[0], consoleInfo.dwSize);		// 사이즈 설정
	SetConsoleWindowInfo(hBuffer[0], TRUE, &consoleInfo.srWindow);	// 윈도우 정보 설정
	SetConsoleCursorInfo(hBuffer[0], &consoleCursor);				// 커서 설번

	hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);	// 새 버퍼 생성
	SetConsoleScreenBufferSize(hBuffer[1], consoleInfo.dwSize);		// 사이즈 설정
	SetConsoleWindowInfo(hBuffer[1], TRUE, &consoleInfo.srWindow);	// 윈도우 정보 설정
	SetConsoleCursorInfo(hBuffer[1], &consoleCursor);				// 커서 설번

	bufferIndex = 0;					// 시작 버퍼의 인덱스
	hFront = hBuffer[bufferIndex];		// 현재 버퍼 설정
	hBackground = hBuffer[bufferIndex + 1];	// 백그라운드 버퍼 설정
}

void ConsoleDoubleBuffer::Destroy()
{
	for (HANDLE handle : hBuffer)
	{
		CloseHandle(handle);
	}
	hBuffer[0] = nullptr;
	hBuffer[1] = nullptr;

	hFront = nullptr;
	hBackground = nullptr;
}

void ConsoleDoubleBuffer::Render(const char* renderData)
{
	ClearBuffer();	// 백그라운드의 이전 내용 모두 제거

	DWORD written;	// 글자를 쓸 때 몇글자를 실제로 썼는지 받아오는 변수
	WriteFile(hBackground, renderData, (DWORD)strlen(renderData), &written, NULL);	// renderData에 있는 글자를 모두 hBackground에 기록

	BufferFlip();	// 버퍼 변경
}

void ConsoleDoubleBuffer::ClearBuffer() const
{
	COORD pos{ 0, 0 };
	DWORD written = 0;
	unsigned int size = BUFFER_HEIGHT * BUFFER_WIDTH;
	FillConsoleOutputCharacter(hBackground, ' ', size, pos, &written);	// ' '로 현재 버퍼를 채우기
	SetConsoleCursorPosition(hBackground, pos);	// 커서 위치 옮기기
}

void ConsoleDoubleBuffer::BufferFlip()
{
	hBackground = hFront;				// 프론트를 백그라운드로 설정
	bufferIndex = bufferIndex ? 0 : 1;	// ?앞에 조건이 참이면 : 앞에 있는 값, 거짓이면 : 뒤에 있는 값		
	//bufferIndex = ~bufferIndex;
	hFront = hBuffer[bufferIndex];		// 백그라운드를 새 프론트로 설정
	SetConsoleActiveScreenBuffer(hFront);	// 새 프론트를 활성화
}

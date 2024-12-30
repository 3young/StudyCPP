#pragma once
#include <functional>
#include "Logger.h"

#define _TEST_MODE	1	// 테스트 코드 포함/제거용 디파인

// 테트리스에서 사용되는 키 종류(크기는 char)
enum class KeyType : char
{
	Left = 0,	// 왼쪽 이동용 키
	Right,		// 오른쪽 이동용 키
	Spin,		// 회전용 키
	SoftDrop,	// 빠르게 떨어지게 하는 키
	HardDrop,	// 바닥으로 즉시 떨어지게 하는 키
	Esc,		// Esc키
	Test,		// 테스트용
	NUM_OF_KEYTYPE	// 키 종류가 몇개인지
};

using Action = std::function<void()>;

enum class CellType : char
{
	Blank = 0,		// 빈칸
	Border,			// 테두리
	Block,			// 테트로미노 블록(떨어지고 있는 블록)
	Line,			// 바닥에 쌓인 블록
};

struct Position
{
	int x;
	int y;

	// 기본 생성자 만들기(x=0,y=0)
	/*Position()
	{
		this->x = 0;
		this->y = 0;
	}*/
	Position() : x(0), y(0) {};

	// 사용자 정의 생성자 만들기(생성자의 파라메터로 x,y를 받아 적용하기)
	Position(int _x, int _y) : x(_x), y(_y) {};

	// 명령어 오버로딩으로 + 오버로딩하기(x는 x끼리 더하고 y는 y끼리 더한다)
	Position operator+(const Position& other) const
	{
		return Position(x + other.x, y + other.y);
	}
};
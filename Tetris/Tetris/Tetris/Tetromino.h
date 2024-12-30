#pragma once
#include "common.h"

class Tetromino
{
public:
	// 초기화 함수
	void Initialize();

	// 초기화 중에 파생클래스에서 별도로 수행할 코드를 오버라이드 하는 함수
	virtual void OnInitialize() {};

	// 정리용 함수
	void Destroy();

	// 시계방향으로 회전
	void Spin();

	// 반시계방향으로 회전
	void ReverseSpin();

	// 회전 방향 초기화용
	inline void Reset() { spinIndex = 0; }

	//inline const CellType* GetData() const { return data[spinIndex]; }
	inline const Position* GetMinos() const { return &minoPositions[spinIndex][0]; }
	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }

	static constexpr int TetroCount = 4;

protected:
	// 총 회전 방향의 수
	static constexpr int SpinCount = 4;	

	// CellType으로 표현한 테트로미노의 모양(4방향 모두)
	CellType** data = nullptr;

	// 테트로미노를 이루는 블럭들의 위치들(4개) * 4방향
	Position minoPositions[SpinCount][TetroCount];

	int width = 3;		// 기본적인 크기(3*3). 예외는 따로 처리(I,O)
	int height = 3;

private:
	// 지금 몇번 회전된 방향인지(시계방향으로)
	int spinIndex = 0;

	// data를 기반으로 minoPositions를 계산하는 함수
	void CollectPositions();
};

// 테트로미노의 종류
// I
// J
// L
// O
// S
// T
// Z
#pragma once
#include <vector>
#include "Tetromino.h"

class DropBlock
{
public:
	void Initialize();
	void Update(float deltaTime);
	void Destroy();

	// current를 리셋하고 위치를 초기화하는 함수
	void Reset();

	// 키 입력으로 실행시키는 함수들
	void MoveLeft();	// 왼쪽으로 한칸 움직이는 함수
	void MoveRight();	// 오른쪽으로 한칸 움직이는 함수
	void Spin();		// 시계방향으로 회전시키는 함수
	void HardDrop();

	void MoveFast(bool isFast);    // 


	// getter
	inline const Tetromino* GetCurrent() const { return current; }
	inline const Position& GetCurrentPosition() const { return currentPosition; }

	// setter
	inline void SetCurrentPosition(const Position& pos) { currentPosition = pos; }

	// 좌우로 움직였음을 알리는 함수 객체(리턴값이 true면 정상적으로 이동 할 수 있다. false면 이동 불가능한 지역으로 이동했다)
	std::function<bool(const DropBlock&)> onMoveSide = nullptr;	
	std::function<bool(const DropBlock&)> onMoveDown = nullptr;
	std::function<bool(const DropBlock&)> onSpin = nullptr;		// 스핀했음을 알리는 함수 객체	
	std::function<void(const DropBlock&)> onHardDrop = nullptr;	// 하드드랍을 알리는 함수 객체

private:
	enum class MinoType : char
	{
		I = 0,
		J,
		L,
		O,
		S,
		T,
		Z,
		NUM_OF_TYPES
	};

	// tetrominos 중 하나를 랜덤으로 리턴하는 함수(7bag 기능 적용)
	Tetromino* GetRandomTetromino();

	// 한 칸 아래로 내려가는 함수
	void MoveDown();

	// 미리 만들어 놓은 모든 테트로미노
	Tetromino* tetrominos[static_cast<int>(MinoType::NUM_OF_TYPES)];

	// 현재 스테이지에서 보이는 테트로미노
	Tetromino* current = nullptr;

	// current의 현재 위치
	Position currentPosition;

	// 7bag 구현을 위한 벡터
	std::vector<int> bag;

	// 한 칸 아래로 내려가는데 걸리는 시간
	float dropInterval = 1.0f;

	// 한 칸 아래로 내려간 후 지나간 시간
	float elapsedTime = 0.0f;

	// 시간을 누적시키는 정도
	float timeModifier = 1.0f;

	// 소프트드랍용 timeModifier 변경 값
	const float SoftDropSpeed = 5.0f;

	// 일반 timeModifier 변경 값
	float NormalDropSpeed = 1.0f;
};


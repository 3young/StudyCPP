#include "Tetromino.h"
#include "Logger.h"

void Tetromino::Initialize()
{
	data = nullptr;
	OnInitialize();	// data에 데이터 넣기
	CollectPositions();
}

void Tetromino::Destroy()
{
	if (data != nullptr)
	{		
		// data delete하기
		for (int i = 0; i < SpinCount; i++)
		{
			delete[] data[i];		// delete CellType*
			data[i] = nullptr;
		}
		delete[] data;				// delete CellType**
		data = nullptr;		
	}
}

void Tetromino::Spin()
{
	spinIndex++;			// spinIndex 1증가
	spinIndex %= SpinCount;	// spinIndex는 0 ~ 3의 범위를 가진다.
}

void Tetromino::ReverseSpin()
{
	spinIndex = (spinIndex + SpinCount - 1) % SpinCount;	// spinindex 1감소 + spinIndex는 0~3의 범위를 가진다.
}

void Tetromino::CollectPositions()
{
	// data의 내용을 기반으로 minoPositions를 채우기
	// data에서 Block으로 설정된 곳의 좌표 저장
	//	- 왼쪽 위가 원점, 
	//  - 가로가 x, 세로가 y
	//	- x는 왼쪽->오른쪽이 +방향
	//	- y는 위->아래가 +방향

	int index = 0;						// minoPositions의 특정 방향의 몇번째 블럭인지 나타내는 변수
	int size = width * height;			// 테트로미노의 크기(파생클래스 별로 다름)
	for (int i = 0; i < SpinCount; i++)	// 방향별로 처리
	{
		index = 0;						// index 초기화
		for (int j = 0; j < size; j++)
		{
			if (*(data[i] + j) == CellType::Block)	// i방향일때 j번째 칸이 Block인지 확인
			//if( data[i][j] == CellType::Block )
			{
				minoPositions[i][index] = { j % width, j / width };	// 1차원 순서를 2차원 좌표로 바꾸기
				// j는 0~8로 간다고 할 때 x값은 가로 길이로 나눈 나머지, y값은 가로 길이로 나눈 몫
				index++;
			}
		}
	}
}

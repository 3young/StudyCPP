#include "Stage.h"

void Stage::Initialize()
{
	// 출력 텍스트 초기화
	renderText = new char[canvasTextArraySize];
	memset(renderText, 0, canvasTextArraySize);	// canvasText를 0으로 채우기, char 크기는 1

	// 드랍블럭 초기화
	pDropBlock = new DropBlock();
	pDropBlock->Initialize();

	pDropBlock->onMoveSide = std::bind(&Stage::CheckValidPosition, this, std::placeholders::_1);
	pDropBlock->onSpin = std::bind(&Stage::CheckValidPosition, this, std::placeholders::_1);
	pDropBlock->onHardDrop = std::bind(&Stage::HardDropProcess, this, std::placeholders::_1);
}

void Stage::Destroy()
{
	// 드랍블럭 제거
	pDropBlock->Destroy();
	delete pDropBlock;
	pDropBlock = nullptr;

	// 출력 텍스트 제거
	delete renderText;
	renderText = nullptr;	
}

void Stage::Update(float deltaTime)
{
	pDropBlock->Update(deltaTime);

	DataToText();	// 마지막 줄에 있어야 함
}

void Stage::DataToText()
{
	// 기본 구조 : canvas에 CellType을 배치하기 -> canvas의 정보를 바탕으로 text로 변경하기

	// 배경 데이터 넣기
	// StageBackground에 있는 데이터를 canvas로 (sizeof(CellType) * FullWidth * FullHeight)만큼 복사
	memcpy(canvas, StageBackground, sizeof(CellType) * FullWidth * FullHeight);		

	// 라인 데이터 넣기

	// 블록 데이터 넣기
	 const Position* pPositions = pDropBlock->GetCurrent()->GetMinos();
	 const Position position = Origin + pDropBlock->GetCurrentPosition();	// 원점에 드랍블럭의 위치 더하기
	 for (int i = 0; i < Tetromino::TetroCount; i++)
	 {
		 int x = position.x + pPositions[i].x;
		 int y = position.y + pPositions[i].y;
		 canvas[y][x] = CellType::Block;
	 }

	// 텍스트로 변경하기
	memset(renderText, 0, canvasTextArraySize);	// 일단 깨끗하게 정리
	for (int y = 0; y < FullHeight; y++)
	{
		for (int x = 0; x < FullWidth; x++)
		{
			int index = static_cast<int>(canvas[y][x]);
			strcat_s(renderText, canvasTextArraySize, enumToChar[index]);
		}
		strcat_s(renderText, canvasTextArraySize, "\n");
	}
}

bool Stage::CheckValidPosition(const DropBlock& block)
{
	const Position* pTargetPosition = &block.GetCurrentPosition();		// 현재 위치
	const Position* pMinoPositions = block.GetCurrent()->GetMinos();	// 각각의 위치

	bool isSuccess = true;
		
	int size = static_cast<int>(Tetromino::TetroCount);
	for (int i = 0; i < size; i++)
	{
		Position minoPos = *pTargetPosition + *(pMinoPositions + i);	// 현재 위치 + 각각의 위치(i번째)
		if (!(minoPos.x >= 0 && minoPos.x < StageWidth)			// 위치 중 하나가 좌우의 경계랑 겹치거나 나갔다.
			|| !(minoPos.y >= 0 && minoPos.y < LinesHeight)		// 위치 중 하나가 위아래의 경계랑 겹치거나 나갔다.
			/*바닥에 쌓인 블럭과 체크 필요*/)
		{
			isSuccess = false;
			break;
		}
	}

	return isSuccess;
}

void Stage::HardDropProcess(const DropBlock& block)
{
	// block을 바닥까지 내리기
	//		바닥 찾기(stage의 바닥이거나 라인에 처음 닿는 부분)
	// 바닥에 닿은 block을 라인에 추가하기
	//		한줄이 가득 찼는지 확인
	//			해당 줄 삭제
	//			삭제된 줄 윗줄을 모두 아래로 내리기
	//		게임 오버가 되었는지 안되었는지 체크
	// block 리셋
}

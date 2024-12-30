#include "DropBlock.h"
#include "MinoI.h"
#include "MinoJ.h"
#include "MinoL.h"
#include "MinoO.h"
#include "MinoS.h"
#include "MinoT.h"
#include "MinoZ.h"
#include "Stage.h"
#include "Random.h"

void DropBlock::Initialize()
{
	// 테트로미노 새로 할당하기
	tetrominos[static_cast<int>(MinoType::I)] = new MinoI();
	tetrominos[static_cast<int>(MinoType::J)] = new MinoJ();
	tetrominos[static_cast<int>(MinoType::L)] = new MinoL();
	tetrominos[static_cast<int>(MinoType::O)] = new MinoO();
	tetrominos[static_cast<int>(MinoType::S)] = new MinoS();
	tetrominos[static_cast<int>(MinoType::T)] = new MinoT();
	tetrominos[static_cast<int>(MinoType::Z)] = new MinoZ();

	for (Tetromino* mino : tetrominos)
	{
		mino->Initialize();
	}

	bag.reserve(static_cast<int>(MinoType::NUM_OF_TYPES));	// 테트로미노 종류만큼 캐퍼시티 확보

	Reset();
}

void DropBlock::Update(float deltaTime)
{
}

void DropBlock::Destroy()
{
	// 할당한 테트로미노 전부 제거
	const int size = static_cast<int>(MinoType::NUM_OF_TYPES);
	for (int i = 0; i < size; i++)
	{
		tetrominos[i]->Destroy();
		delete tetrominos[i];
		tetrominos[i] = nullptr;
	}
}

void DropBlock::Reset()
{
	if (current != nullptr)
		current->Reset();

	current = GetRandomTetromino();

	currentPosition = { 
		static_cast<int>((Stage::GetStageWidth() - current->GetWidth()) / 2),
		static_cast<int>(Stage::GetSpawnHeight() - current->GetHeight())
	};
}

void DropBlock::MoveLeft()
{
	//Logger::Print("Input Left\n");
	currentPosition.x--;
	if (onMoveSide && !onMoveSide(*this))	
	{
		// onMoveSide에 함수가 들어있고, 함수를 실행시킨 결과가 false가 돌아왔다
		currentPosition.x++;	// 다시 롤백
	}

}

void DropBlock::MoveRight()
{
	//Logger::Print("Input Right\n");
	currentPosition.x++;
	if (onMoveSide && !onMoveSide(*this))
	{
		// onMoveSide에 함수가 들어있고, 함수를 실행시킨 결과가 false가 돌아왔다
		currentPosition.x--;	// 다시 롤백
	}
}

void DropBlock::Spin()
{
	current->Spin();
	if (onSpin && !onSpin(*this) )
	{
		current->ReverseSpin();	// 돌렸을 때 적절하지 않는 위치가 있으면 다시 되돌리기
	}
}

void DropBlock::HardDrop()
{
	if (onHardDrop)
	{
		onHardDrop(*this);		// 등록된 리스너가 있으면 실행
	}
}

Tetromino* DropBlock::GetRandomTetromino()
{
	if (bag.empty())					// 가방이 비었으면
	{
		bag.assign({ 0,1,2,3,4,5,6 });	// 0~6까지 가방에 넣기
		Random::Get().Shuffle(bag);		// 가방 안의 항목들을 섞기
	}
	int index = bag[0];			// 가방의 첫번째 값을 복사하기
	bag.erase(bag.begin());		// 가방의 첫번째 항목을 삭제하기
	
	return tetrominos[index];	// 꺼낸 값을 인덱스로 사용해서 테트로미노 리턴
}

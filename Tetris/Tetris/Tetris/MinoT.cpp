#include "MinoT.h"

void MinoT::OnInitialize()
{
	width = 3;
	height = 3;

	const int size = 9;
	CellType mino[SpinCount][size] = {		// 눈으로 보기 편하기 위해 임시 데이터 만들기
		{
			CellType::Blank, CellType::Block, CellType::Blank,
			CellType::Blank, CellType::Block, CellType::Block,
			CellType::Blank, CellType::Block, CellType::Blank,
		},
		{
			CellType::Blank, CellType::Blank, CellType::Blank,
			CellType::Block, CellType::Block, CellType::Block,
			CellType::Blank, CellType::Block, CellType::Blank,
		},
		{
			CellType::Blank, CellType::Block, CellType::Blank,
			CellType::Block, CellType::Block, CellType::Blank,
			CellType::Blank, CellType::Block, CellType::Blank,
		},
		{
			CellType::Blank, CellType::Block, CellType::Blank,
			CellType::Block, CellType::Block, CellType::Block,
			CellType::Blank, CellType::Blank, CellType::Blank,
		}
	};

	data = new CellType * [SpinCount];
	for (int i = 0; i < SpinCount; i++)
	{
		data[i] = new CellType[size];
		memcpy(data[i], mino[i], sizeof(CellType) * size);	// 임시 데이터를 data에 복사
	}
}
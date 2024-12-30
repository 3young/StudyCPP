#pragma once
#include <Windows.h>
#include "System.h"

class ConsoleDoubleBuffer : public System
{
public:
	// 초기화용 함수(버퍼 생성)
	virtual void Initialize() override;

	// 정리용 함수(버퍼 삭제)
	virtual void Destroy() override;

	/// <summary>
	/// 텍스트를 랜더링(그리기)하는 함수
	/// </summary>
	/// <param name="renderData">출력될 텍스트</param>
	void Render(const char* renderData);

private:
	// 현재 앞에서 보여질 콘솔의 핸들(더블 버퍼링용 버퍼 중 어떤 것이 보이고 있는지)
	HANDLE hFront = nullptr;

	// 뒤에서 그려지는 콘솔의 핸들
	HANDLE hBackground = nullptr;

	// 더블 버퍼링용 콘솔 버퍼
	HANDLE hBuffer[2] = { nullptr, };

	// 현재 콘솔의 인덱스(플립용)
	int bufferIndex = 0;

	// 버퍼의 가로 크기
	const int BUFFER_WIDTH = 40;

	// 버퍼의 세로 크기
	const int BUFFER_HEIGHT = 30;

	// 백그라운드 버퍼를 빈칸으로 채우는 함수
	void ClearBuffer() const;

	// 버퍼 플립 함수
	void BufferFlip();
};


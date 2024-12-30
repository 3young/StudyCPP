#pragma once
#include <ctime>
#include "Singleton.h"
#include "System.h"
#include "ConsoleDoubleBuffer.h"
#include "Input.h"
#include "Stage.h"

class GameManager : public Singleton<GameManager>
{
public:
	void Initialize();
	bool Loop();
	void Destroy();

	inline float GetDeltaTime() const { return deltaTime; }	// inline 함수 : 컴파일 타임에 코드 교체가 일어남

	// 입력 시스템 함수 래핑
	inline void BindPressInput(KeyType type, Action func) {
		pInput->BindPress(type, func);
	}
	inline void BindReleaseInput(KeyType type, Action func) {
		pInput->BindRelease(type, func);
	}
	template <typename T>
	inline void BindPressInput(KeyType type, void (T::* func)(), T* obj)
	{
		pInput->BindPress(type, func, obj);
	}
	template <typename T>
	inline void BindReleaseInput(KeyType type, void (T::* func)(), T* obj)
	{
		pInput->BindRelease(type, func, obj);
	}

#ifdef _TEST_MODE
	inline void Test_Stage_7Bag() { pStage->Test_7Bag(); }
#endif

private:
	GameManager() = default;

	// 이전 프레임에서 지금 프레임 간의 시간 간격(초 단위)
	float deltaTime = 0.0f;	

	std::vector<System*> systems;
	ConsoleDoubleBuffer* pRenderer = nullptr;
	Input* pInput = nullptr;
	Stage* pStage = nullptr;

	clock_t lastTime = -1;


	void SetConsoleFont(const wchar_t* fontName, SHORT sizeX, SHORT sizeY);


	friend class Singleton;		// Singleton 클래스는 private맴버나 protected 맴버에 접근 가능
};


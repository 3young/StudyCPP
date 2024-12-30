#pragma once
#include <Windows.h>
#include <vector>
#include "System.h"
#include "common.h"

class Input : public System
{
public:
	virtual void Initialize() override;
	virtual void Update(float deltaTime) override;

	// 키를 눌렀을 때 실행될 함수 바인딩
	inline void BindPress(KeyType type, Action func) {
		pressActions[static_cast<int>(type)].push_back(func);
	}

	// 키를 땠을 때 실행될 함수 바인딩
	inline void BindRelease(KeyType type, Action func) {
		releaseActions[static_cast<int>(type)].push_back(func);
	}
	
	// 키를 눌렀을 때 실행될 맴버함수 바인딩
	template <typename T>
	inline void BindPress(KeyType type, void (T::* func)(), T* obj)
	{
		pressActions[static_cast<int>(type)].push_back(std::bind(func, obj));
	}

	// 키를 땠을 때 실행될 맴버함수 바인딩
	template <typename T>
	inline void BindRelease(KeyType type, void (T::* func)(), T* obj)
	{
		releaseActions[static_cast<int>(type)].push_back(std::bind(func, obj));
	}

	// void (T::* func)()
	// void			: 리턴타입은 void.
	// (T::* func)	: func는 T타입의 맴버 함수이다.
	// ()			: 파라메터는 없다.

private:
	// 가상키의 종류
	const int virtualKeys[static_cast<int>(KeyType::NUM_OF_KEYTYPE)]{ VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN, VK_SPACE, VK_ESCAPE, VK_NUMPAD0 };

	// 특정키가 눌려있는지 표시
	bool keyPressed[static_cast<int>(KeyType::NUM_OF_KEYTYPE)];

	// 눌렀을 때 실행될 함수들
	std::vector<Action> pressActions[static_cast<int>(KeyType::NUM_OF_KEYTYPE)];

	// 떨어졌을 때 실행될 함수들
	std::vector<Action> releaseActions[static_cast<int>(KeyType::NUM_OF_KEYTYPE)];
};


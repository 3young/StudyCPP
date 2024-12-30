#include "Input.h"

void Input::Initialize()
{
	for (auto type : pressActions)
	{
		type.clear();
	}
	for (auto type : releaseActions)
	{
		type.clear();
	}
	memset(keyPressed, 0, sizeof(bool) * static_cast<int>(KeyType::NUM_OF_KEYTYPE));
}

void Input::Update(float deltaTime)
{
	int count = static_cast<int>(KeyType::NUM_OF_KEYTYPE);
	for (int i = 0; i < count; i++)
	{
		if (GetAsyncKeyState(virtualKeys[i]) & 0x8000)	//UP키가 눌려져 있으면 true, 아니면 false
		{
			if (!keyPressed[i])		// keyPressed[i] == false
			{
				// 안눌려져 있다가 이제 눌려졌다.
				keyPressed[i] = true;
				
				for (auto& func : pressActions[i])	//for (std::vector<Action>::iterator::value_type& func : pressActions[i])
				{
					func();			// 눌린 직후에만 저장된 모든 함수 실행
				}
			}
		}
		else
		{
			if (keyPressed[i])		// keyPressed[i] == true
			{
				// 눌려져 있다가 이제 떨어졌다.
				keyPressed[i] = false;
				for (auto& func : releaseActions[i])	//for (std::vector<Action>::iterator::value_type& func : releaseActions[i])
				{
					func();			// 눌린 직후에만 저장된 모든 함수 실행
				}
			}
		}
	}
}

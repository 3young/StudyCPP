#pragma once

class System
{
public:
	virtual void Initialize() {};				// 초기화
	virtual void Update(float deletaTime) {};	// 업데이트
	virtual void Destroy() {};					// 정리

	virtual ~System() = default;	// 가상 소멸자를 포함하여 파생 클래스에서 소멸자가 올바르게 호출되도록 함
};
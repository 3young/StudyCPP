#pragma once
class MyClass
{
public:
	float height;
private:
	int age;
public:
	char* name;
};

// 클래스의 접근제한자는 기본적으로 private

// 접근제한자
//	public : 모두에게 접근 허가
//	protected : 자신과 자신을 상속받은 자식에게만 접근 허가
//	private : 자신만 접근 허가

// 객체지향
//  - 추상화 : 주요한 개념과 기능만을 묶는 것
//	- 캡슐화 : 접근제한자를 통한 데이터의 접근제어(몰라도되는 것은 안보여야 한다)
//	- 상속 : 부모클래스의 데이터와 기능을 물려받는 것
//	- 다형성 : 동일한 인터페이스를 통해 다양한 처리를 하는 것(가상함수의 오버라이드를 통해 처리)

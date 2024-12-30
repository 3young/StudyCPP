#pragma once
#include <string>
using namespace std;

class Animal
{
public:
	virtual void Cry();

	const int Test1();	// 리턴타입이 const int => 리턴값은 한번 초기화되면 수정이 불가능하다
	int Test2(const int data);	// 파라메터가 const => 함수 내부에서 파라메터의 수정이 불가능하다.
	int Test3() const;	// 바디 앞에 const => 함수 내부에서 맴버 변수의 수정이 불가능하다.

	std::string name;
protected:
	int age = 0;

private:
	int address = 0;
};

class Dog : public Animal
{
public:
	virtual void Cry() override;
};

class Cat : public Animal
{
public:
	virtual void Cry() override;
};
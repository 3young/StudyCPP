#include "Animal.h"

void Animal::Cry()
{
	printf("Cry\n");
	int a = Test1();	// const int가 int로 암시적 변환이 일어남
	a = 20;
	const int b = Test1();
	//b = 20;
}

const int Animal::Test1()
{
	age = 10;
	return 0;
}

int Animal::Test2(const int data)
{
	//data = 20;	// data가 const니 수정불가능
	age = data;		// 읽는 것은 가능
	return 0;
}

int Animal::Test3() const
{
	// age = 20;	// 함수 바디 앞에 const가 있기 때문에 맴버 변수의 수정 불가능
	return 0;
}

void Dog::Cry()
{
	printf("Dog : Bark! Bark!\n");
}

void Cat::Cry()
{
	Animal::Cry();
	printf("Cat : Mew! Mew!\n");
}

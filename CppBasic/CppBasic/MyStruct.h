#pragma once

// 구조체
//	데이터 집합을 표현하는데 사용한다.
//	접근제한자가 기본적으로 public이다.
struct MyStruct
{
	int x;
	float y;
	int height;
	float damage;

	// 생성자
	MyStruct()
	{
		x = 0;
		y = 0;
		height = 0;
		damage = 0;
	}
	MyStruct(int val)
	{
		x = val;
		y = val;
		height = val;
		damage = val;
	}
	MyStruct(int x, float _y, int _height, int _damage)
	{		
		//x = x;
		this->x = x;
		y = _y;
		height = _height;
		damage = _damage;
	}
};

struct Vector2D
{
	float x;
	float y;

	Vector2D operator+(const Vector2D& other) const
	{
		return { this->x + other.x, this->y + other.y };
	}

	Vector2D operator-(const Vector2D& other) const
	{
		// 빼기 : x는 x끼리 빼고 y는 y끼리 뺀다
		return { this->x - other.x, this->y - other.y };
	}

	Vector2D operator*(const float& other) const
	{
		// Vector2D * float : x,y를 float 값으로 곱한다.
		return { x * other, y * other };
	}

	Vector2D operator/(const float& other) const
	{
		// Vector2D / float : x,y를 float 값으로 나눈다.
		return { x / other, y / other };
	}
};

// Access Modifier (접근제한자, 엑세스 한정자)
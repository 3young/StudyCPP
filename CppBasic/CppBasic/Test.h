// 선언부
#include <vector>
#include <list>
#include <map>
#include "MyStruct.h"
#include "MyClass.h"
#include "enums.h"
#include "LinkedList.h"
#include "BinarySearchTree.h"

#define PI 3.141592		// 매크로 : 컴파일 할 때 PI라는 글자가 3.141592로 자동 변경된다.

class Test
{
public:
	int data = 0;

	void Run();
	void Run2();

	void Test_1219_InputOutput();
	void Test_1219_DataType();
	void Test_1219_ArithmeticOperator();
	void Test_1220_Assignment();
	void Test_1220_Comparison();
	void Test_1220_Logical();
	void Test_1220_Bitwise();
	void Test_1220_ControlStatement();
	void Test_1220_SlotMachine();
	void Test_1220_RPS();
	void Test_1220_Template();
	void Test_1220_Array();
	void Test_1223_Pointer();
	void Test_1223_Reference();
	void Test_1223_String();
	void Test_1223_StringPractice();
	void Test_1223_Structure();
	void Test_1224_Class();
	void Test_1224_Enum();
	void Test_1224_List();
	void Test_1224_BST();
	void Test_1224_STL();
};

void TestFunction(int, float);	// 함수의 선언 : 리턴값의 타입, 함수 이름, 파라메터들(0개 이상 가능)
int TestFunction2(int, float);
void TestFuction3(int* data, int size);
void TestFuction4(int& data);

int MyStrLen(char* str);
int MyStrCmp(char* str1, char* str2);
void MyParser(char* source, int* out, int count = 5);
int MyAtoI(char* str);
int MyPow(int base, int exponent);

float TestStruct1(MyStruct st);
float TestStruct2(MyStruct* st);
float TestStruct3(MyStruct& st);

int Add(int num1, int num2);
float Add(float num1, float num2);

template <typename T>
T TemplateAdd(T num1, T num2);

template <typename T>
T Clamp(T value, T min, T max);

template<typename T>
inline T TemplateAdd(T num1, T num2)
{
	return num1 + num2;
}

template<typename T>
inline T Clamp(T value, T min, T max)
{
	T result = value;
	if (value < min)
	{
		result = min;
	}
	if (value > max)
	{
		result = max;
	}

	return result;
}


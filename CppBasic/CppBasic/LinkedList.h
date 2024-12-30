#pragma once

struct ListNode
{
public:
	int data = 0;
	ListNode* next = nullptr;

	ListNode(int data)
	{
		this->data = data;
		next = nullptr;
	}
};

class LinkedList
{
public:
	// 동작

	// 마지막에 데이터를 추가하는 함수
	void Add(int data);						
	
	// Data를 position번째에 추가(position이 전체길이를 벗어나면 마지막에 추가)
	void Insert(int data, int position);	

	// 리스트에서 data를 삭제
	void Remove(int data);					

	// 리스트에서 position번째의 노드를 제거(position이 전체길이를 벗어나면 처리안함)
	void RemoveAt(int position);			

	// 리스트의 모든 노드를 삭제
	void Clear();							

	// 리스트를 처음부터 끝까지 출력하는 함수
	void Print();							

private:
	// 데이터

	// 첫번째 노드의 위치
	ListNode* head = nullptr;
};


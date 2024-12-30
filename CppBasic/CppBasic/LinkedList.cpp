#include <stdio.h>
#include "LinkedList.h"

void LinkedList::Add(int data)
{
	ListNode* node = new ListNode(data);

	if (head == nullptr)
	{
		head = node;	// 해드가 비어있으면 새로 만든 노드가 새 해드가 된다.
	}
	else
	{
		ListNode* tail = head;
		while (tail->next != nullptr)	// tail이 마지막 노드가 될때까지 이동
		{
			tail = tail->next;
		}
		tail->next = node;				// 마지막 노드의 next로 새로 만든 노드를 지정
	}
}

void LinkedList::Insert(int data, int position)
{
	ListNode* node = new ListNode(data);
	ListNode* target = head;		// position위치에 있는 노드
	ListNode* prev = nullptr;		// target 앞에 있는 노드

	// target이 적절한 위치로 갈때까지 이동시키기
	int count = 0;
	while (count < position && target != nullptr)
	{
		count++;
		prev = target;
		target = target->next;	
	}

	node->next = target;	// 새 노드의 다음 노드로 target을 설정
	if (prev == nullptr)
	{
		head = node;		// 맨 앞에 있는 노드인 경우 head로 설정
	}
	else
	{
		prev->next = node;	// 이전노드의 다음노드를 새 노드로 설정
	}
}

void LinkedList::Remove(int data)
{
	ListNode* target = head;
	ListNode* prev = nullptr;

	while (target != nullptr)	// 마지막 노드까지 반복
	{
		if (target->data == data)	// 삭제할 대상을 찾으면
		{
			if (prev != nullptr)
			{
				// 이전 노드가 있다.
				prev->next = target->next;		// 링크 조정하기
			}
			else
			{
				// 이전 노드가 없다(첫번째 노드다)
				head = target->next;			// 해드 설정
			}
			delete target;		// 노드 삭제
			target = nullptr;
			break;
		}

		prev = target;			// prev에 target 저장하고
		target = target->next;	// 다음 노드로 이동
	}
}

void LinkedList::RemoveAt(int position)
{
	ListNode* target = head;
	ListNode* prev = nullptr;
	int count = 0;

	while (count < position && target != nullptr)	// target이 적절해질때까지 진행
	{
		count++;
		prev = target;
		target = target->next;
	}

	if (target != nullptr)
	{
		if (prev != nullptr)
		{
			// 이전 노드가 있다.
			prev->next = target->next;		// 링크 조정하기
		}
		else
		{
			// 이전 노드가 없다(첫번째 노드다)
			head = target->next;			// 해드 설정
		}
		delete target;		// 노드 삭제
		target = nullptr;
	}
}

void LinkedList::Clear()
{
	while (head != nullptr)
	{
		RemoveAt(0);
	}
}

void LinkedList::Print()
{
	printf("List : ");
	ListNode* node = head;
	while (node != nullptr)
	{
		printf("%d -> ", node->data);	// 마지막 노드까지 하나씩 찍기
		node = node->next;
	}
	printf("End\n");
}

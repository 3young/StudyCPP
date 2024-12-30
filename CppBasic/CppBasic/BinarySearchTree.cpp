#include "BinarySearchTree.h"
#include <stdio.h>

void BinarySearchTree::Insert(int key, int data)
{
	root = InsertRecursive(root, key, data);
}

void BinarySearchTree::Delete(int key)
{
	root = DeleteRecursive(root, key);
}

TreeNode* BinarySearchTree::Search(int key)
{
	TreeNode* target = root;
	while (target != nullptr)
	{
		if (target->key < key)
		{
			target = target->rightChild;
		}
		else if (target->key > key)
		{
			target = target->leftChild;
		}
		else
		{
			break;
		}
	}

	return target;
}

void BinarySearchTree::Clear()
{
}

void BinarySearchTree::PrintInOrder()
{
	// 트리 순회 : 정해진 규칙대로 트리의 모든 노드를 한번씩 방문하는 것
	// pre order(전위순회)	: 루트 -> 왼쪽 -> 오른쪽
	// in order(중위순회)	: 왼쪽 -> 루트 -> 오른쪽
	// post order(후위순회)	: 왼쪽 -> 오른쪽 -> 루트
	printf("Tree (In order) : ");
	InOrderRecursive(root);
	printf("\n");
}

TreeNode* BinarySearchTree::InsertRecursive(TreeNode* currentRoot, int key, int data)
{
	if (currentRoot == nullptr)
	{
		return new TreeNode(key, data);	// 비어 있으니까 새 노드 만들어서 연결
	}

	if (key < (currentRoot->key))
	{
		// key가 root의 키보다 작으면 왼쪽으로 보내기(root의 왼쪽 자식이 비었으면 새로 노드가 만들어져서 리턴됨)
		currentRoot->leftChild = InsertRecursive(currentRoot->leftChild, key, data);	
	}
	else if (key > (currentRoot->key))
	{
		currentRoot->rightChild = InsertRecursive(currentRoot->rightChild, key, data);
	}

	return currentRoot;
}

TreeNode* BinarySearchTree::DeleteRecursive(TreeNode* currentRoot, int key)
{
	if (currentRoot == nullptr)
	{
		return currentRoot;
	}

	if (key < currentRoot->key)
	{
		currentRoot->leftChild = DeleteRecursive(currentRoot->leftChild, key);
	}
	else if (key > currentRoot->key)
	{
		currentRoot->rightChild = DeleteRecursive(currentRoot->rightChild, key);
	}
	else
	{
		// 찾았다.

		// 자식이 없다 or 자식이 하나만 있다.
		if (currentRoot->leftChild == nullptr)
		{
			TreeNode* temp = currentRoot->rightChild;
			delete currentRoot;
			return temp;
		}
		else if (currentRoot->rightChild == nullptr)
		{
			TreeNode* temp = currentRoot->leftChild;
			delete currentRoot;
			return temp;
		}

		// 자식이 둘 다 있는 경우
		TreeNode* minNode = FindMinNode(currentRoot->rightChild);	// 오른쪽에서 가장 키값이 가장 작은 노드를 찾기
		currentRoot->key = minNode->key;		// 루트의 키값과 데이터를 가장 작은 노드의 값으로 대체
		currentRoot->data = minNode->data;
		currentRoot->rightChild = DeleteRecursive(currentRoot->rightChild, minNode->key);	// 가장 작은 노드를 삭제 + 오른쪽 서브트리도 갱신
	}

	return currentRoot;
}

void BinarySearchTree::InOrderRecursive(TreeNode* currentRoot) const
{
	if (currentRoot != nullptr)
	{
		InOrderRecursive(currentRoot->leftChild);
		printf("%d ", currentRoot->key);
		InOrderRecursive(currentRoot->rightChild);
	}
}

void BinarySearchTree::ClearRecursive(TreeNode* currentRoot)
{
	if (currentRoot != nullptr)
	{
		ClearRecursive(currentRoot->leftChild);
		ClearRecursive(currentRoot->rightChild);
		delete currentRoot;
	}
}

TreeNode* BinarySearchTree::FindMinNode(TreeNode* currentRoot)
{
	while (currentRoot != nullptr && currentRoot->leftChild != nullptr)
	{
		currentRoot = currentRoot->leftChild;	// 왼쪽 끝까지 이동하기
	}

	return currentRoot;
}

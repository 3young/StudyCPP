#pragma once
struct TreeNode
{
	TreeNode(int key, int data = -1)
	{
		this->key = key;
		if (data == -1)
		{
			this->data = key * 10;	// 입력받은 데이터가 -1이면 key값의 10배
		}
		else
		{
			this->data = data;		// 그 외에는 입력받은대로 처리
		}
	}
	int key = 0;	// 순서가 있는 키 값
	int data = 0;	// 이 노드가 가지는 데이터

	TreeNode* leftChild = nullptr;	// 이 노드의 왼쪽 자식
	TreeNode* rightChild = nullptr;	// 이 노드의 오른쪽 자식
};

class BinarySearchTree
{
public:
	void Insert(int key, int data);
	void Delete(int key);
	TreeNode* Search(int key);
	
	void Clear();
	void PrintInOrder();


private:
	TreeNode* root = nullptr;

	TreeNode* InsertRecursive(TreeNode* currentRoot, int key, int data);
	TreeNode* DeleteRecursive(TreeNode* currentRoot, int key);
	void InOrderRecursive(TreeNode* currentRoot) const;

	void ClearRecursive(TreeNode* currentRoot);

	TreeNode* FindMinNode(TreeNode* currentRoot);
};


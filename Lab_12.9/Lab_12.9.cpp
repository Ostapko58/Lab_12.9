#include<iostream>
#include<windows.h>
using namespace std;

struct Node{
	Node* left,
		* right;
	int info;
};


Node* CreateTree(int nodeCount)
{
	if (nodeCount == 0)
		return NULL;
	else
	{
		Node* newNode = new Node;
		cout << " Enter node value: ";
		cin >> newNode->info;
		int leftCount = nodeCount / 2;
		int rightCount = nodeCount - leftCount - 1;
		newNode->left = CreateTree(leftCount);
		newNode->right = CreateTree(rightCount);
		return newNode;
	}
}

Node* BinarySearchInsert(Node*& root, int value, bool& found)
{
	if (root == NULL)
	{
		root = new Node;
		root->info = value;
		root->left = NULL;
		root->right = NULL;
		found = false;
		return root;
	}
	else
		if (value == root->info)
		{
			found = true;
			return root;
		}
		else
			if (value < root->info)
				return BinarySearchInsert(root->left, value, found);
			else
				return BinarySearchInsert(root->right, value, found);
}

void PrintTree(Node* root, int level)
{
	if (root != NULL)
	{
		PrintTree(root->right, level + 1);
		for (int i = 1; i <= level; i++)
			cout << " ";
		cout << root->info << endl;
		PrintTree(root->left, level + 1);
	}
}

void RightRotation(Node*& root)
{
	Node* tmp1 = root->left;
	Node* tmp2 = tmp1->right;
	tmp1->right = root; //1
	root->left = tmp2; //2
	root = tmp1; //3
}
void LeftRotation(Node*& root)
{
	Node* tmp1 = root->right;
	Node* tmp2 = tmp1->left;
	tmp1->left = root; //1
	root->right = tmp2; //2
	root = tmp1; //3
}
Node* FindMax(Node* root) {
	if (root->right != NULL)
		return FindMax(root->right);
	else
		return root;
}

Node* BinarySearchDelete(Node* root, int value)
{
	if (NULL == root) return NULL;
	if (root->info == value)
	{
		if (NULL == root->left && NULL == root->right)
		{
			delete root;
			return NULL;
		}
		if (NULL == root->right && root->left != NULL)
		{
			Node* temp = root->left;
			delete root;
			return temp;
		}
		if (NULL == root->left && root->right != NULL)
		{
			Node* temp = root->right;
			delete root;
			return temp;
		}
		root->info = FindMax(root->left)->info;
		root->left = BinarySearchDelete(root->left, root->info);
		return root;
	}
	if (value < root->info)
	{
		root->left = BinarySearchDelete(root->left, value);
		return root;
	}
	if (value > root->info)
	{
		root->right = BinarySearchDelete(root->right, value);
		return root;
	}
	return root;
}

Node* Find(Node* root, int value)
{
	if (root == NULL || value == root->info)
		return root;
	if (value < root->info)
		return Find(root->left, value);
	else
		return Find(root->right, value);
}

void DeleteTree(Node*& root, Node* node)
{
	if (node != NULL)
	{
		DeleteTree(root, node->left);
		DeleteTree(root, node->right);
		root = BinarySearchDelete(root, node->info);
	}
}

int Height(Node* root)
{
	if (root == NULL)
		return 0;
	int hL = Height(root->left);
	int hR = Height(root->right);
	return (hL > hR ? hL : hR) + 1;
}

int BFactor(Node* root)
{
	return Height(root->right) - Height(root->left);
}

void BalanceHeight(Node*& root)
{
	if (root != NULL)
	{
		while (BFactor(root) >= 2)
		{
			if (BFactor(root->right) < 0)
				RightRotation(root->right);
			LeftRotation(root);
		}
		while (BFactor(root) <= -2)
		{
			if (BFactor(root->left) > 0)
				LeftRotation(root->left);
			RightRotation(root);
		}
		BalanceHeight(root->left);
		BalanceHeight(root->right);
	}
}
void InfixOrderSum(Node* root,int k, int& S)
{
	if (root != NULL)
	{
		InfixOrderSum(root->left,k,S);
		if (root->info%k==0)
		{
			S += root->info;
		}
		InfixOrderSum(root->right,k,S);
	}
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Node* root = NULL,
		* root2 = NULL;
	int N, value, S = 0, k = 3, menu;
	bool found = false;
	cout << "Enter nodes count: "; cin >> N;
	root = CreateTree(N);
	for (int i = 0; i < N; i++)
	{
		found = false;
		cout << "value: "; cin >> value;
		BinarySearchInsert(root2, value, found);
	}
	cout << endl;
	PrintTree(root, 0);
	cout << endl;
	PrintTree(root2, 0);
	cout << endl;
	cout << endl;
	BalanceHeight(root2);
	cout << endl;
	PrintTree(root2, 0);
	cout << endl;
	do
	{
		cout << "1 - додати елемент" << endl;
		cout << "2 - видалити елемент" << endl;
		cout << "3 - видалити гілку" << endl;
		cout << "4 - вивести на екран" << endl;
		cout << "0 - вийти" << endl;
		cin >> menu;
		switch (menu)
		{
		case 1:
			cout << "value: "; cin >> value;
			BinarySearchInsert(root2, value, found);
			break;
		case 2:
			cout << "delete value: "; cin >> value;
			root2 = BinarySearchDelete(root2, value);
			break;
		case 3:
			cout << "delete tree value: "; cin >> value;
			DeleteTree(root2, Find(root2, value));
			break;
		case 4:
			cout << endl;
			PrintTree(root2, 0);
			cout << endl;
			break;
		default:
			break;
		}
	} while (menu!=0);
	cout << endl;
	InfixOrderSum(root2, k, S);
	cout << "S = " << S << endl;
	//cout << "delete value: "; cin >> value;
	//root2 = BinarySearchDelete(root2, value);
	/*cout << "delete tree value: "; cin >> value;
	DeleteTree(root2, Find(root2, value));

	BalanceHeight(root2);

	cout << endl;
	PrintTree(root2, 0);
	cout << endl;*/
	//BinarySearchInsert(root2, 3, found);
	//root = CreateTree(N);
	//PrintTree(root2, 0);
	return 0;
}
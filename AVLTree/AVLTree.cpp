#include <iostream>
#include <ctime>

class Node 
{
public:
	int Key;
	Node* Left;
	Node* Right;
	int Height;
};

int Max(int LeftUnderTree, int RightUnderTree);

int Height(Node* NewHeight) 
{
	if (NewHeight == nullptr)
	{
		return 0;
	}
	return NewHeight->Height;
}

int Max(int LeftUnderTree, int RightUnderTree) 
{
	if (LeftUnderTree > RightUnderTree)
	{
		return LeftUnderTree;
	}
	else
	{
		return RightUnderTree;
	}
}

Node* NewNode(int Key) 
{
	Node* Nodes = new Node();
	Nodes->Key = Key;
	Nodes->Left = nullptr;
	Nodes->Right = nullptr;
	Nodes->Height = 1;
	return (Nodes);
}

Node* RightRotate(Node* NewRight) 
{
	Node* NewLeft = NewRight->Left;
	Node* Revert = NewLeft->Right;
	NewLeft->Right = NewRight;
	NewRight->Left = Revert;
	NewRight->Height = Max(Height(NewRight->Left), Height(NewRight->Right)) + 1;
	NewLeft->Height = Max(Height(NewLeft->Left), Height(NewLeft->Right)) + 1;
	return NewLeft;
}

Node* LeftRotate(Node* NewLeft) 
{
	Node* NewRight = NewLeft->Right;
	Node* Revert = NewRight->Left;
	NewRight->Left = NewLeft;
	NewLeft->Right = Revert;
	NewLeft->Height = Max(Height(NewLeft->Left), Height(NewLeft->Right)) + 1;
	NewRight->Height = Max(Height(NewRight->Left), Height(NewRight->Right)) + 1;
	return NewRight;
}

int GetBalanceFactor(Node* AddNode) 
{
	if (AddNode == nullptr)
	{
		return 0;
	}
	return Height(AddNode->Left) - Height(AddNode->Right);
}

Node* InsertNode(Node* AddNode, int Key) 
{
	if (AddNode == nullptr)
	{
		return (NewNode(Key));
	}
	if (Key < AddNode->Key)
	{
		AddNode->Left = InsertNode(AddNode->Left, Key);
	}
	else if (Key > AddNode->Key)
	{
		AddNode->Right = InsertNode(AddNode->Right, Key);
	}
	else
	{
		return AddNode;
	}
	AddNode->Height = 1 + Max(Height(AddNode->Left), Height(AddNode->Right));
	int BalanceFactor = GetBalanceFactor(AddNode);
	if (BalanceFactor > 1) 
	{
		if (Key < AddNode->Left->Key) 
		{
			return RightRotate(AddNode);
		}
		else if (Key > AddNode->Left->Key) 
		{
			AddNode->Left = LeftRotate(AddNode->Left);
			return RightRotate(AddNode);
		}
	}
	if (BalanceFactor < -1) 
	{
		if (Key > AddNode->Right->Key) 
		{
			return LeftRotate(AddNode);
		}
		else if (Key < AddNode->Right->Key) 
		{
			AddNode->Right = RightRotate(AddNode->Right);
			return LeftRotate(AddNode);
		}
	}
	return AddNode;
}

Node* NodeWithMimumValue(Node* AddNode) 
{
	Node* Current = AddNode;
	while (Current->Left != nullptr)
		Current = Current->Left;
	return Current;
}

Node* DeleteNode(Node* Root, int Key) 
{
	if (Root == nullptr)
	{
		return Root;
	}
	if (Key < Root->Key)
	{
		Root->Left = DeleteNode(Root->Left, Key);
	}
	else if (Key > Root->Key)
	{
		Root->Right = DeleteNode(Root->Right, Key);
	}
	else 
	{
		if ((Root->Left == nullptr) || (Root->Right == nullptr)) 
		{
			Node* Temp = Root->Left ? Root->Left : Root->Right;
			if (Temp == nullptr) 
			{
				Temp = Root;
				Root = nullptr;
			}
			else
			{
				*Root = *Temp;
			}
			delete(Temp);
		}
		else 
		{
			Node* Temp = NodeWithMimumValue(Root->Right);
			Root->Key = Temp->Key;
			Root->Right = DeleteNode(Root->Right, Temp->Key);
		}
	}
	if (Root == nullptr)
	{
		return Root;
	}
	Root->Height = 1 + Max(Height(Root->Left), Height(Root->Right));
	int BalanceFactor = GetBalanceFactor(Root);
	if (BalanceFactor > 1) 
	{
		if (GetBalanceFactor(Root->Left) >= 0) 
		{
			return RightRotate(Root);
		}
		else 
		{
			Root->Left = LeftRotate(Root->Left);
			return RightRotate(Root);
		}
	}
	if (BalanceFactor < -1) 
	{
		if (GetBalanceFactor(Root->Right) <= 0) 
		{
			return LeftRotate(Root);
		}
		else 
		{
			Root->Right = RightRotate(Root->Right);
			return LeftRotate(Root);
		}
	}
	return Root;
}

void PrintTree(Node* Root, std::string Indent, bool Last) 
{
	if (Root != nullptr) 
	{
		std::cout << Indent;
		if (Last) 
		{
			std::cout << "R----";
			Indent = Indent + "   ";
		}
		else 
		{
			std::cout << "L----";
			Indent = Indent + "|  ";
		}
		std::cout << Root->Key << std::endl;
		PrintTree(Root->Left, Indent, false);
		PrintTree(Root->Right, Indent, true);
	}
}

void TestAddValueAndTime(Node* Root)
{
	srand(time(nullptr));
	int RandomNum = rand() % 100;
	while (RandomNum != 0)
	{
		Root = InsertNode(Root, rand() % 100);
		RandomNum = rand() % 100;
	}
	PrintTree(Root, "", true);
	std::cout<<std::endl << "Runtime= " << clock() / 1000.0 <<" ms" << std::endl;
}

int main() 
{
	Node* Root = nullptr;
	TestAddValueAndTime(Root);
	//std::cout << "After deleting " << std::endl;
	//PrintTree(Root, "", true);
}
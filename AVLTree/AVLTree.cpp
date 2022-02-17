#include <iostream>
#include "AVLTree.h"
#include <ctime>


UAVLTree::UAVLTree()
{
	Root = nullptr;
}

UAVLTree::~UAVLTree()
{
	DeleteNode(Root, 0);
}

int UAVLTree::Height(FNode* NewHeight)
{
	if (NewHeight == nullptr)
	{
		return 0;
	}
	return NewHeight->Height;
}

int UAVLTree::Max(int LeftUnderTree, int RightUnderTree)
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

FNode* UAVLTree::NewNode(int Key)
{
	FNode* Nodes = new FNode();
	Nodes->Key = Key;
	Nodes->Left = nullptr;
	Nodes->Right = nullptr;
	Nodes->Height = 1;
	return (Nodes);
}

FNode* UAVLTree::RightRotate(FNode* NewRight)
{
	FNode* NewLeft = NewRight->Left;
	FNode* Revert = NewLeft->Right;
	NewLeft->Right = NewRight;
	NewRight->Left = Revert;
	NewRight->Height = Max(Height(NewRight->Left), Height(NewRight->Right)) + 1;
	NewLeft->Height = Max(Height(NewLeft->Left), Height(NewLeft->Right)) + 1;
	return NewLeft;
}

FNode* UAVLTree::LeftRotate(FNode* NewLeft)
{
	FNode* NewRight = NewLeft->Right;
	FNode* Revert = NewRight->Left;
	NewRight->Left = NewLeft;
	NewLeft->Right = Revert;
	NewLeft->Height = Max(Height(NewLeft->Left), Height(NewLeft->Right)) + 1;
	NewRight->Height = Max(Height(NewRight->Left), Height(NewRight->Right)) + 1;
	return NewRight;
}

int UAVLTree::GetBalanceFactor(FNode* AddNode)
{
	if (AddNode == nullptr)
	{
		return 0;
	}
	return Height(AddNode->Left) - Height(AddNode->Right);
}

FNode* UAVLTree::InsertNode(FNode* AddNode, int Key)
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

FNode* UAVLTree::NodeWithMimumValue(FNode* AddNode)
{
	FNode* Current = AddNode;
	while (Current->Left != nullptr)
		Current = Current->Left;
	return Current;
}

FNode* UAVLTree::DeleteNode(FNode* Root, int Key)
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
			FNode* Temp = Root->Left ? Root->Left : Root->Right;
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
			FNode* Temp = NodeWithMimumValue(Root->Right);
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

void UAVLTree::PrintTree(FNode* Root, std::string Indent, bool Last)
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

void UAVLTree::TestAddValueAndTime(FNode* Root)
{
	srand(time(nullptr));
	int RandomNum = 1100;
	for (int i = 0; i < RandomNum; i++)
	{
		Root = InsertNode(Root, rand() % RandomNum);
	}
	PrintTree(Root, "", true);
	std::cout<<std::endl << "Runtime= " << clock() / 1000.0 <<" ms" << std::endl;
	InsertNode(Root, 1000);
	PrintTree(Root, "", true);
	std::cout << std::endl << "Runtime= " << clock() / 1000.0 << " ms" << std::endl;
	DeleteNode(Root, 1000);
	PrintTree(Root, "", true);
	std::cout << std::endl << "Runtime= " << clock() / 1000.0 << " ms" << std::endl;
}

int main() 
{
	UAVLTree* Tree = new UAVLTree();
	FNode* Root = nullptr;
	Tree->TestAddValueAndTime(Root);
}
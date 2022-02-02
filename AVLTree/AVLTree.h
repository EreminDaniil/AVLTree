#pragma once
#include <iostream>

struct FNode
{
	int Key;
	int Height;
	FNode* Left;
	FNode* Right;
};

class UAVLTree
{
public:
	UAVLTree();
	~UAVLTree();
	FNode* NewNode(int Key);
	FNode* RightRotate(FNode* NewRight);
	FNode* LeftRotate(FNode* NewLeft);
	FNode* InsertNode(FNode* AddNode, int Key);
	FNode* NodeWithMimumValue(FNode* AddNode);
	FNode* DeleteNode(FNode* Root, int Key);
	int Max(int LeftUnderTree, int RightUnderTree);
	int Height(FNode* NewHeight);
	int GetBalanceFactor(FNode* AddNode);
	void PrintTree(FNode* Root, std::string Indent, bool Last);
	void TestAddValueAndTime(FNode* Root);
private:
	FNode* Root;
};
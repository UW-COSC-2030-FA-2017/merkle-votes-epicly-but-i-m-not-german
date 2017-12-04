//Schuyler Vercauteren
//COSCI data structures Homework
//bTree.cpp
//11/23/17
#include "bTREE.h"
#include<stdio.h>
#include<iostream>
#include<queue>
using namespace::std;
using std::queue;

//struct node constructor
bTREE::treeNode::treeNode() { time = 0; data = ""; isLeaf = false; }
bTREE::treeNode::~treeNode()
{
	if (left != 0 && right != 0)
	{
		delete left;
		delete right;
	}
}
void bTREE::treeNode::print() {
	cout << "--- " << "Data: " << this->data << " ---" << endl;
	cout << "Time: " << this->time << " ---" << endl;
	if (this->isLeaf == true) { cout << "Node IS a leaf node ---" << endl; }
	else { cout << "Node is NOT a leaf node ---" << endl; }

}
//look at descriptions in pMT.h for guidance on what you might need for these function to actually do
bTREE::bTREE()
{
	tree;
	opening = false;
}
bTREE::~bTREE() {}

//newMethod: pseudo copy constructor by replacing the trunk with a new trunk.
void bTREE::setTrunk(treeNode* sappling)
{
	trunk = sappling;
	inTraversal(trunk);
}

//new mwthods: returns data from referenced node.
string bTREE::getDat(treeNode * node)
{
	string hold = node->data;
	return hold;
}

//New Method: returns amount of leaf nodes.
int bTREE::getLeaves()
{
	totalNodes = 0;
	leafNodes = 0;
	dataNodes = 0;
	inTraversal(trunk);
	return leafNodes;
}
//New Method get Trunk returns trunk.
bTREE::treeNode* bTREE::getTrunk()
{
	return trunk;
}
//new Method: padding helper function for print tree. followed by print function.
void bTREE::padding(char c, int n)
{
	for (int i = 0; i < n; i++)
	{
		putchar(c);
	}
}
void bTREE::print(treeNode* root, int pos)
{
	if (root == NULL)
	{
		padding('\t', pos); 
		puts("~|");
	}
	else
	{
		print(root->right, pos + 1);
		padding('\t', pos);
		printf("%d \n", root->data);
		print(root->left, pos + 1);
	}
}
//new Method: populate creates and returns an empty tree of a given size.
bTREE::treeNode bTREE::populate(int height, treeNode front)
{
	opCount++;
	treeNode* top = &front;
	top->left = new treeNode();
	top->right = new treeNode();
	int i = 2;
	if( i <height)
	{
		front = populate(height-1, *top->left);
		front = populate(height-1, *top->right);
	}
	front = *top;
	return front;
}
//new Method: inTraversal counts various types of nodes and sets leaf boolean value.
void bTREE::inTraversal(treeNode *root)
{
	opCount++;
	if (root == 0) { return; }
	if (tree.size() == 0)
	{
		totalNodes = 0;
		leafNodes = 0;
		dataNodes = 0;
		cout << endl << "The Tree Is Empty. " << endl;
	}
	else {
		if (root->left == nullptr && root->right == nullptr)
		{
			root->isLeaf = true;
			totalNodes++;
			leafNodes++;
			if (root->data.size() != 0)
			{
				dataNodes++;
			}
		}
		else
		{
			root->isLeaf = false;
			totalNodes++;
			if (root->data.size() != 0)
			{
				dataNodes++;
			}
			if (root->left != nullptr) { inTraversal(root->left); }
			if (root->right != nullptr) { inTraversal(root->right); }
		}
	}
}
//New method: newRow will copy the current tree into a new tree with twice the amount of AVAILABLE SLOTS for leaf nodes.
void bTREE::newRow(treeNode* tooSmall)
{
	opCount++;
	totalNodes = 0;
	leafNodes = 0;
	dataNodes = 0;
	inTraversal(tooSmall);
	int height = 0;
	treeNode* temp = tooSmall;
	while (temp->isLeaf == false)
	{
		height++;
		temp = temp->right;
	}
	temp = tooSmall;
	treeNode* top = new treeNode();
	top->left = temp;
	treeNode* hold = new treeNode();
	if (height > 1) 
	{
		top->right = &populate(height, *hold);
	}
	else
	{
		top->right = hold;
	}
	trunk = top;
	totalNodes = 0;
	leafNodes = 0;
	dataNodes = 0;
	inTraversal(trunk);
}
//New method: findParent will return a pointer to the root node of the next incpomplete subtree, OR nullptr if all nodes on last layer are leaf nodes.
bTREE::treeNode * bTREE::findParent(treeNode * root)
{
	opCount++;
	totalNodes = 0;
	leafNodes = 0;
	dataNodes = 0;
	inTraversal(root);
	treeNode * hold = 0;
	if(root->left && root->isLeaf == false)
	{
		if (root->left != 0 && root->right == 0)
		{
			opening = true;
			hold = root;
			return hold;
		}
		else {
			hold = findParent(root->left); 
			if (opening == false) { hold = findParent(root->right); }
		}
	}
	else { return root; }
	return hold;
}
int bTREE::dataInserted()
{
	totalNodes = 0;
	leafNodes = 0;
	dataNodes = 0;
	inTraversal(trunk);
	return dataNodes;
}

int bTREE::numberOfNodes()
{
	totalNodes = 0;
	leafNodes = 0;
	dataNodes = 0;
	inTraversal(trunk);
	return totalNodes;
}

int bTREE::insert(string data, int time)
{
	opCount++;
	treeNode* node = new treeNode();
	node->data = data;
	node->time = time;
	if (tree.size() == 0)
	{
		treeNode* empty = new treeNode();
		tree.push_front(*empty);
		trunk = empty;
		trunk->left = node;
		node->parent = trunk;
		totalNodes = 0;
		leafNodes = 0;
		dataNodes = 0;
		inTraversal(trunk);
		return 1;
	}
	else {
		treeNode * found = findParent(trunk);
		if (found->isLeaf == false)
		{
			node->parent = found;
			found->right = node;
			totalNodes = 0;
			leafNodes = 0;
			dataNodes = 0;
			inTraversal(trunk);
			return 1;
		}
		else
		{
			newRow(trunk);
			treeNode* leaf = trunk;
			leaf = leaf->right;
			while (leaf->isLeaf == false)
			{
				leaf = leaf->left;
			}
			node->parent = leaf;
			leaf->left = node;
			totalNodes = 0;
			leafNodes = 0;
			dataNodes = 0;
			inTraversal(trunk);
			return 1;
		}
	}
}
int bTREE::findT(int me, treeNode start)
{
	opCount++;
	int found = 0;
	treeNode hold = start;
	if (hold.time == me) { found = 1; return found; }
	if (hold.time != me && hold.left != nullptr)
	{
		map.push('L');
		found = findT(me, *hold.left);
	}
	if (hold.time != me && hold.right != nullptr && found == 0)
	{
		map.push('R');
		found = findT(me, *hold.right);
	}
	if (found == 0) { map.pop(); }
	return found;
}
int bTREE::find(string me, treeNode start)
{
	opCount++;
	int found = 0;
	treeNode hold = start;
	if (hold.data == me) { found = 1; return found; }
	if (hold.data != me && hold.left != nullptr)
	{
		map.push('L');
		found = find(me, *hold.left);
	}
	if (hold.data != me && hold.right != nullptr && found==0) 
	{
		map.push('R');
		found = find(me, *hold.right);
	}
	if (found == 0) { map.pop(); }
	return found;
}
string bTREE::locateT(int me)
{
	opCount++;
	queue<char> temp;
	map.swap(temp);
	findT(me, *trunk);
	string word;
	while (map.size() != 0)
	{
		word += map.front();
		map.pop();
	}
	return word;
}
string bTREE::locate(string me)
{
	opCount++;
	queue<char> temp;
	map.swap(temp);
	find(me, *trunk);
	string word;
	while (map.size() != 0)
	{
		word += map.front();
		map.pop();
	}
	return word;
}

 bool operator ==(const bTREE& lhs, const bTREE& rhs)
{
	 bTREE::treeNode startL = *lhs.trunk;
	 bTREE::treeNode startR = *rhs.trunk;
	 int i = 0;
	 if (startL.data == startR.data) { i++; }
	 if (startL.left->data == startR.left->data) { i++; }
	 if (startL.right->data == startR.right->data) { i++; }
	 if (lhs.leafNodes == rhs.leafNodes) { i++; }
	 if (lhs.dataNodes == rhs.dataNodes) { i++; }
	 if (lhs.totalNodes == rhs.totalNodes) { i++; }
	 if (i == 6) { return true; }
	 else { return false; }
}

 bool operator !=(const bTREE& lhs, const bTREE& rhs)
{
	 bTREE::treeNode startL = *lhs.trunk;
	 bTREE::treeNode startR = *rhs.trunk;
	 int i = 0;
	 if (startL.data == startR.data) { i++; }
	 if (startL.left->data == startR.left->data) { i++; }
	 if (startL.right->data == startR.right->data) { i++; }
	 if (lhs.leafNodes == rhs.leafNodes) { i++; }
	 if (lhs.dataNodes == rhs.dataNodes) { i++; }
	 if (lhs.totalNodes == rhs.totalNodes) { i++; }
	 if (i != 6) { return true; }
	 else { return false; }
}

 std::ostream& operator <<(std::ostream& out,const bTREE& p)
{
	 bTREE hold = p;
	 bTREE::treeNode* temp = hold.trunk;
	 hold.print(temp, 0);
	 return out;
}
 bTREE * operator ^(const bTREE& lhs, const bTREE& rhs)
 {
	 int check = 0;
	 bTREE left = lhs;
	 bTREE right = rhs;
	 bTREE * resultL = NULL;
	 bTREE * resultR = NULL;
	 if (!left.trunk->left->isLeaf && !right.trunk->left->isLeaf)
	 {
		 left.setTrunk(left.trunk->left);
		 right.setTrunk(right.trunk->left);
		  resultL = left ^ right;
	 }
	 if (!left.trunk->right->isLeaf && !right.trunk->right->isLeaf)
	 {
		 left = lhs;
		 right = rhs;
		 left.setTrunk(left.trunk->right);
		 right.setTrunk(right.trunk->right);
		  resultR = left ^ right;
	 }
	 if (left == right)
	 {
			 return &left;
	 }
	 else if (resultL != NULL)
	 {
		 return resultL;
	 }
	 else if (resultR != NULL)
	 {
		 return resultR;
	 }
	 return NULL;
 }

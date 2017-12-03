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
bTREE::treeNode::treeNode() {}
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

//newMethods return a pointer to the next empty node on the left or right.
template <typename T>
string  bTREE::treeNode::getHash(T mrkl, int type)
{
	if (left != 0 && right != 0 && !left->isLeaf && !right->isLeaf)
	{
		string lval = left->getHash(mrkl, type);
		string rval = right->getHash(mrkl, type);
		if (type == 1)
		{
			string values = lval + rval;
			data = mrkl->hash_1(values);
			return data;
		}
	}
	else if (left != 0 && right == 0 && !left->isLeaf)
	{
		string lval = left->getHash(mrkl, type);
		if (type == 1)
		{
			data = mrkl->hash_1(lval);
			return data;
		}
	}
	else if (left == 0 && right != 0 && !right->isLeaf)
	{
		string rval = right->getHash(mrkl, type);
		if (type == 1)
		{
			data = mrkl->hash_1(rval);
			return data;
		}
	}
	else if (left != 0 && right != 0 && left->isLeaf == true && right->isLeaf == true)
	{
		string lval = left->data;
		string rval = right->data;
		string values = lval + rval;
		if (type == 1)
		{
			data = mrkl->hash_1(values);
			return data;
		}
	}
	else if (left != 0 && right == 0 && left->isLeaf)
	{
		string lval = left->data;
		if (type == 1)
		{
			data = mrkl->hash_1(lval);
			return data;
		}
	}
	else if (left == 0 && right != 0 && right->isLeaf)
	{
		string rval = right->data;
		if (type == 1)
		{
			data = mrkl->hash_1(rval);
			return data;
		}
	}
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
		printf("%d\n", root->data);
		print(root->left, pos + 1);
	}
}
//new Method: populate creates and returns an empty tree of a given size.
bTREE::treeNode bTREE::populate(int height, treeNode front)
{
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
	totalNodes = 0;
	leafNodes = 0;
	dataNodes = 0;
	inTraversal(root);
	treeNode * hold = 0;
	if(root->isLeaf == false)
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
	treeNode* node = new treeNode();
	node->data = data;
	node->time = time;
	if (tree.size() == 0)
	{
		treeNode* empty = new treeNode();
		tree.push_front(*empty);
		trunk = empty;
		trunk->left = node;
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
	 if (lhs.leafNodes == rhs.leafNodes) { i++; }
	 if (lhs.dataNodes == rhs.dataNodes) { i++; }
	 if (lhs.totalNodes == rhs.totalNodes) { i++; }
	 if (i == 4) { return true; }
	 else { return false; }
}

 bool operator !=(const bTREE& lhs, const bTREE& rhs)
{
	 bTREE::treeNode startL = *lhs.trunk;
	 bTREE::treeNode startR = *rhs.trunk;
	 int i = 0;
	 if (startL.data == startR.data) { i++; }
	 if (lhs.leafNodes == rhs.leafNodes) { i++; }
	 if (lhs.dataNodes == rhs.dataNodes) { i++; }
	 if (lhs.totalNodes == rhs.totalNodes) { i++; }
	 if (i != 4) { return true; }
	 else { return false; }
}

 std::ostream& operator <<(std::ostream& out,const bTREE& p)
{
	 bTREE hold = p;
	 bTREE::treeNode* temp = hold.trunk;
	 hold.print(temp, 0);
	 return out;
}


//Schuyler Vercauteren
//COSCI data structures Homework
//bTree.cpp
//11/23/17
#include "bTREE.h"
#include<iostream>
#include<queue>
using namespace::std;
using std::queue;

//struct node constructor
bTREE::treeNode::treeNode(){}
//look at descriptions in pMT.h for guidance on what you might need for these function to actually do
bTREE::bTREE()
{
	tree;
}
bTREE::~bTREE(){}

//new Method:: populate creates and returns an empty tree of a given size.
bTREE::treeNode bTREE::populate(int height, treeNode front)
{
	treeNode top = front;
	top.left = &treeNode();
	top.right = &treeNode();
	int i = 2;
	if( i <height)
	{
		front = populate(height-1, *top.left);
		front = populate(height-1, *top.right);
	}
	front = top;
	return front;
}
//new Method: inTraversal counts various types of nodes and sets leaf boolean value.
void bTREE::inTraversal(treeNode * root)
{
	if (tree.size == 0)
	{
		totalNodes = 0;
		leafNodes = 0;
		dataNodes = 0;
		cout << endl << "The Tree Is Empty. " << endl;
	}
	else {
		totalNodes = 0;
		leafNodes = 0;
		dataNodes = 0;
		if (&root->left == nullptr && &root->right == nullptr)
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
void bTREE::newRow(list<treeNode> tooSmall)
{
	inTraversal(tooSmall.begin);
	int height = 0;
	treeNode temp = tooSmall.begin;
	while (temp.isLeaf == false)
	{
		height++;
		temp = *temp.right;
	}
	treeNode top = treeNode();
	top.left = tooSmall.begin;
	top.right = &treeNode();
	*top.right = populate(height, *top.right);
	tree.begin = top;
}
//New method: findParent will return a pointer to the root node of the next incpomplete subtree, OR nullptr if all nodes on last layer are leaf nodes.
bTREE::treeNode * bTREE::findParent(treeNode * root)
{
	inTraversal(root);
	treeNode * hold = nullptr;
	if(root->isLeaf == false)
	{
		if (&root->left != nullptr && &root->right == nullptr)
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
	inTraversal(tree.begin);
	return dataNodes;
}

int bTREE::numberOfNodes()
{
	inTraversal(tree.begin);
	return totalNodes;
}

int bTREE::insert(string data, int time)
{
	treeNode node = treeNode();
	node.data = data;
	node.time = time;
	if (tree.size == 0)
	{
		treeNode empty = treeNode();
		tree.push_front(empty);
		empty.left = &node;
		return 1;
	}
	else {
		treeNode * found = findParent(tree.begin);
		if (found->isLeaf == false)
		{
			*found->right = node;
			return 1;
		}
		else
		{
			newRow(tree);
			treeNode * leaf = tree.begin;
			leaf = leaf->right;
			inTraversal(leaf);
			while (leaf->isLeaf == false)
			{
				leaf = leaf->left;
			}
			leaf->left = &node;
			return 1;
		}
	}
}

int bTREE::find(string me, treeNode start)
{
	int found = 0;
	treeNode hold = start;
	if (hold.data != me) {
		if (hold.left != nullptr) {found = find(me, *hold.left); }
		if (hold.right != nullptr && found ==0) {found = find(me, *hold.right);}
	}
	else { found = 1; }
	return found;
}

string bTREE::locate(string me, treeNode start)
{
	treeNode hold = start;
	int found = 0;
	if (hold.data != me) {
		if (hold.left != nullptr)
		{ 
			map.push('L');
			found = find(me, *hold.left);
		}
		if (hold.right != nullptr && found == 0)
		{
			map.push('R');
			found = find(me, *hold.right);  
		}
		char h = map.pop();
	}
	else { found = 1; }
	return map;
}

friend bool bTREE::operator ==(const bTREE& lhs, const bTREE& rhs)
{
}

friend bool bTREE::operator !=(const bTREE& lhs, const bTREE& rhs)
{
}

friend std::ostream& bTREE::operator <<(std::ostream& out, const bTREE& p)
{
}

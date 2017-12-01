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
void bTREE::treeNode::print() {
	cout << "---" << endl << "Data: " << this->data << endl << "---" << endl;
	cout << "Time: " << this->time << endl << "---" << endl;
	if (this->isLeaf == true) { cout << "Node IS a leaf node" << endl << "---" << endl; } 
	else{ cout << "Node is NOT a leaf node" << endl << "---" << endl; }

}
//look at descriptions in pMT.h for guidance on what you might need for these function to actually do
bTREE::bTREE()
{
	tree;
	opening = false;
}
bTREE::~bTREE(){}

//new Method: print tree.
void bTREE::print(treeNode* root, int pos)
{
	if (!root) { return; }
	print(root->left, pos);
	pos++;
	cout <<"---"<< pos <<"---"<< "     ";
	root->print();
	print(root->right, pos);
}
//new Method: populate creates and returns an empty tree of a given size.
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
void bTREE::inTraversal(treeNode root)
{
	if (tree.size() == 0)
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
		if (root.left == nullptr && root.right == nullptr)
		{
			root.isLeaf = true;
			totalNodes++;
			leafNodes++;
			if (root.data.size() != 0)
			{
				dataNodes++;
			}
		}
		else
		{
			root.isLeaf = false;
			totalNodes++;
			if (root.data.size() != 0)
			{
				dataNodes++;
			}
			if (root.left != nullptr) { inTraversal(*root.left); }
			if (root.right != nullptr) { inTraversal(*root.right); }
		}
	}
}
//New method: newRow will copy the current tree into a new tree with twice the amount of AVAILABLE SLOTS for leaf nodes.
void bTREE::newRow(list<treeNode> tooSmall)
{
	inTraversal(*tooSmall.begin());
	int height = 0;
	treeNode temp = *tooSmall.begin();
	while (temp.isLeaf == false)
	{
		height++;
		temp = *temp.right;
	}
	temp = *tooSmall.begin();
	treeNode top = treeNode();
	top.left = &temp;
	top.right = &treeNode();
	*top.right = populate(height, *top.right);
	*tree.begin() = top;
}
//New method: findParent will return a pointer to the root node of the next incpomplete subtree, OR nullptr if all nodes on last layer are leaf nodes.
bTREE::treeNode * bTREE::findParent(treeNode * root)
{
	inTraversal(*root);
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
	inTraversal(*tree.begin());
	return dataNodes;
}

int bTREE::numberOfNodes()
{
	inTraversal(*tree.begin());
	return totalNodes;
}

int bTREE::insert(string data, int time)
{
	treeNode node = treeNode();
	node.data = data;
	node.time = time;
	if (tree.size() == 0)
	{
		treeNode empty = treeNode();
		tree.push_front(empty);
		empty.left = &node;
		return 1;
	}
	else {
		treeNode start = *tree.begin();
		treeNode * found = findParent(&start);
		if (found->isLeaf == false)
		{
			*found->right = node;
			return 1;
		}
		else
		{
			newRow(tree);
			treeNode leaf = *tree.begin();
			leaf = *leaf.right;
			inTraversal(leaf);
			while (leaf.isLeaf == false)
			{
				leaf = *leaf.left;
			}
			leaf.left = &node;
			return 1;
		}
	}
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

string bTREE::locate(string me)
{
	queue<char> temp;
	map.swap(temp);
	find(me, *tree.begin());
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
	 bTREE::treeNode startL = *lhs.tree.begin();
	 bTREE::treeNode startR = *rhs.tree.begin();
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
	 bTREE::treeNode startL = *lhs.tree.begin();
	 bTREE::treeNode startR = *rhs.tree.begin();
	 int i = 0;
	 if (startL.data == startR.data) { i++; }
	 if (lhs.leafNodes == rhs.leafNodes) { i++; }
	 if (lhs.dataNodes == rhs.dataNodes) { i++; }
	 if (lhs.totalNodes == rhs.totalNodes) { i++; }
	 if (i != 4) { return true; }
}

 std::ostream& operator <<(std::ostream& out,const bTREE& p)
{
	 bTREE hold = p;
	 bTREE::treeNode temp = *hold.tree.begin();
	 hold.print(&temp, 0);
	 return out;
}


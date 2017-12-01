//Schuyler Vercauteren
//COSCI data structures Homework
//bTree.h
//11/23/17
#pragma once
#include<list>
#include <string>
#include<queue>
using namespace std;
using std::string;
using std::list;
using std::queue;

class bTREE
{
    struct treeNode{
        string data;
        int time;
		bool isLeaf;
		treeNode * left;
		treeNode * right;
		treeNode();
		void print();
    };
    
private:
    //some data structure to hold your treeNodes together ...
    //DATASTUCTURE treeNodes tree;
    //any helper private variables you need
	list<treeNode> tree;
	int totalNodes;
	int leafNodes;
	int dataNodes;
	bool opening;
	queue<char> map;
public:
    bTREE();
    ~bTREE();
    
	void print(treeNode* root, int position);
	treeNode populate(int height, treeNode front);
	void newRow(list<treeNode> tooSmall);
	void inTraversal(treeNode root);
	treeNode * findParent(treeNode * root);
	int dataInserted();
    int numberOfNodes();
    
    int insert(string data, int time);
    
   int find(string me, treeNode start);
    
    string locate(string me);
    
    
    friend bool operator==(const bTREE& lhs, const bTREE& rhs);
    friend bool operator!=(const bTREE& lhs, const bTREE& rhs);

    friend std::ostream& operator<<(std::ostream& out, const bTREE& p);
    
};


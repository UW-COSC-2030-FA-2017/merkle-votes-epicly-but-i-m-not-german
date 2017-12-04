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
		treeNode* parent = 0;
		treeNode * left = 0;
		treeNode * right = 0;
		treeNode();
		~treeNode();
		void print();
    };
    
private:
    //some data structure to hold your treeNodes together ...
    //DATASTUCTURE treeNodes tree;
    //any helper private variables you need


	list<treeNode> tree;
	treeNode* trunk;
	int totalNodes;
	int leafNodes;
	int dataNodes;
	bool opening;
	queue<char> map;
	
public:
	treeNode*it;
	int opCount;

    bTREE();
    ~bTREE();

    //New Methods
	int getLeaves();
	void setTrunk(treeNode* newTrunk);
	treeNode* getTrunk();
	void padding(char c, int n);
	void print(treeNode* root, int position);
	treeNode populate(int height, treeNode front);
	void newRow(treeNode* tooSmall);
	void inTraversal(treeNode* root);
	treeNode * findParent(treeNode * root);
	int findT(int time, treeNode start);
	string locateT(int time);
	//Required Methods
	int dataInserted();
    int numberOfNodes();
    
    int insert(string data, int time);
    
   int find(string me, treeNode start);
    
    string locate(string me);
    
	friend bTREE * operator ^(const bTREE& lhs, const bTREE& rhs);
    friend bool operator==(const bTREE& lhs, const bTREE& rhs);
    friend bool operator!=(const bTREE& lhs, const bTREE& rhs);

    friend std::ostream& operator<<(std::ostream& out, const bTREE& p);
    
};


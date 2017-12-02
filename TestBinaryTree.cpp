//Schuyler Vercauteren
//12/1/17
//Test Binary tree.

#include<iostream>
#include"bTREE.h"
using namespace::std;

int main()
{
	//Create a tree.
	bTREE* myTree = new bTREE();
	//Add a node.
	myTree->insert("BlahBlahblah", 22);
	//Test Find.
	if (myTree->find("BlahBlahblah", *myTree->getTrunk())==1)
	{
		cout << "Found!" << endl;
	}
	else { cout << "Data not found" << endl; }
	//Test failure of find.
	if (myTree->find("Blah", *myTree->getTrunk()) == 1)
	{
		cout << "Found!" << endl;
	}
	else { cout << "Data not found" << endl; }
	//Test locate.
	cout << "The 'map' to the found node is: " << myTree->locate("BlahBlahblah") << endl;
	//Test populate(), findParent() and newRow() by forcing insert to make more space.
	myTree->insert("foo", 30);
	myTree->insert("overflow", 99);
	//Count nodes.
	cout << "The number of data nodes is: " << myTree->dataInserted() << endl;
	cout << "the total number of nodes is: " << myTree->numberOfNodes() << endl;
	//Test Operators
	bTREE* compare = new bTREE();
	compare->insert("not_the_same_node", 66);
	if (*myTree != *compare)
	{
		cout << "Hooray! The tree's did not match!" << endl;
	}
	else { cout << "If your reading this there is a problem with the code.. " << endl; }
	bTREE* same = new bTREE();
	same->insert("not_the_same_node", 66);
	if (*compare == *same)
	{
		cout << "Hooray! The Tree's Matched!" << endl;
	}else{cout<< "If your reading this there is a problem with the code.. " << endl;}
	//Test << overload
	bTREE* printMe = new bTREE();
	printMe->insert("BlahBlahblah", 22);
	printMe->insert("foo", 30);
	printMe->insert("overflow", 99);
	cout << *printMe << endl;
	return 0;
}
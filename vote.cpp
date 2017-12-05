//Schuyler Vercauteren
//COSCI data structures Homework
//12/2/17

#include <stdio.h>
#include<iostream>
#include<fstream>
#include "pMT.h"
using namespace std;

int main()
{
	int sel;
	string hold;
	int time;
	pMT* firstTree = new pMT(1);
	pMT* secondTree = new pMT(2);
	pMT* thirdTree = new pMT(2);
	sel = 1;
	if (sel == 1) {
		// Read in a single file and store it in Merkle Tree
		ifstream List("mv_test.txt");
		if (List.is_open())
		{
			cout << "Reading File. . ." << endl;
			while (!List.eof())
			{
				List >> hold;
				List >> time;
				firstTree->insert(hold, time);
			}
			List.close();
		}
		else { cout << endl << "could not open file" << endl; List.close(); }
		cout << "The Root Node is: " << endl;
		firstTree->printRoot();
		cout << endl;
		sel++;
	}
		//Read in two files and validate if they are the same.
		ifstream one("mv_test1.txt");
		if (one.is_open())
		{
			cout << "Reading 1st File. . ." << endl;
			while (!one.eof())
			{
				one >> hold;
				one >> time;
				secondTree->insert(hold, time);
			}
			one.close();
		}
		else { cout << endl << "could not open 1/2 files" << endl; one.close(); }
			ifstream two("mv_test2.txt");
			if (two.is_open())
			{
				cout << "Reading 2nd File. . ." << endl;
				while (!two.eof())
				{
					two >> hold;
					two >> time;
					thirdTree->insert(hold, time);
				}
				two.close();
			}
			else { cout << endl << "could not open 2/2 file" << endl; two.close(); }
//begin comparison.
			bTREE Btree = secondTree->getTree();
			bTREE Ctree = thirdTree->getTree();
		if (Btree == Ctree)
		{
			cout << endl << "Validated!" << endl;
		}
		else
		{
			bTREE* ven = Btree ^ Ctree;
			Btree.it = ven->getTrunk();
			Ctree.it = ven->getTrunk();
			string venHash = Btree.it->data;
			string BS = Btree.locate(venHash);
			string CS = Ctree.locate(venHash);
			const char * avoid = BS.c_str();
			const char * dodge = CS.c_str();
			Btree.it = Btree.getTrunk();
			Ctree.it = Ctree.getTrunk();
			cout << "The subtrees that differ in the first tree are: " << endl;
			for (int i = 0; i < BS.size(); i++)
			{
				if (avoid[i] == 'L')
				{
					cout << "-------------------------" << endl;
					Btree.print(Btree.it->right, 0);
					Btree.it = Btree.it->left;
					cout << "-------------------------" << endl;
				}
				else
				{
					cout << "-------------------------" << endl;
					Btree.print(Btree.it->left, 0);
					Btree.it = Btree.it->right;
					cout << "-------------------------" << endl;
				}
			}
			cout << "The subtrees that differ in the first tree are: " << endl;
			for (int i = 0; i < CS.size(); i++)
			{
				if (dodge[i] == 'L')
				{
					cout << "-------------------------" << endl;
					Ctree.print(Ctree.it->right, 0);
					Ctree.it = Ctree.it->left;
					cout << "-------------------------" << endl;
				}
				else
				{
					cout << "-------------------------" << endl;
					Ctree.print(Ctree.it->left, 0);
					Ctree.it = Ctree.it->right;
					cout << "-------------------------" << endl;
				}

			}
		}
	return 0;
}

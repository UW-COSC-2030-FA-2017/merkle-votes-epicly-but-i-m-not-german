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
	string hold;
	int time;
	pMT* firstTree = new pMT(2);
	pMT* secondTree = new pMT(3);
	pMT* thirdTree = new pMT(3);
	pMT* fourthTree = new pMT(1);
	// Read in a single file and store it in Merkle Tree
	ifstream List("mv_test.txt");
	if (List.is_open())
	{

		//Execute code.
		List.close();
	}
	else { cout << endl << "could not open file" << endl; List.close(); }

	//Read in two files and validate if they are the same.
	ifstream one ("mv_test.txt");
	if (one.is_open())
	{
		//Execute code.
		one.close();
	}
	else { cout << endl << "could not open file" << endl; one.close(); }
	ifstream two("mv_test.txt");
	if (two.is_open())
	{
		//Execute code.
		two.close();
	}
	else { cout << endl << "could not open file" << endl; two.close(); }
	return 0;
}

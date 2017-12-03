//Schuyler Vercauteren
//12/1/2017
#pragma once

#include "bTREE.h"
#include <iostream>
#include <string>
using namespace std;
class pMT
{
private:
    int selectedHash;
    bTREE myMerkle;
    
    string hash_1(string);
    string hash_2(string);
    string hash_3(string);
    
public:
    pMT(int hashSelect);
    ~pMT();
    
	void hashBranches();
    int insert(string vote, int time);
    
    int find(string data, int time, int hashSelect);
    int findHash(string mhash);
    
    string locateData(string vote);
	string locateHash(string mHash);
    
    friend bool operator==(const pMT& lhs, const pMT& rhs);
    
    friend bool operator!=(const pMT& lhs, const pMT& rhs);
    
    friend pMT operator^(const pMT& lhs, const pMT& rhs);
    friend std::ostream& operator<<(std::ostream& out, const pMT& p);
    
};


#include"pMT.h"
#include<vector>
using std::vector;
pMT::pMT(int hashSelect)
/**
 * @brief
 * @param hashSelect a number corresponding to the hashfunction to use for this pMT
 * @return
 */
{
	selectedHash = hashSelect;
}

pMT::pMT(int sel, bTREE tree)
{
	selectedHash = sel;
	myMerkle.setTrunk(tree.getTrunk());
}

pMT::~pMT()
/**
 * @brief destructor
 * @return nada
 */
{}

//New Method: hash branches will travers the merkle tree and set the hashes.
void pMT::hashBranches(int select)
{
	vector<int> map;
	int leftToHash = myMerkle.numberOfNodes() - myMerkle.getLeaves();
	int level = 0;
	int j = 2;
	//calculating map.
	myMerkle.it = myMerkle.getTrunk();
	while (myMerkle.it->left->isLeaf == false)
	{
		myMerkle.it = myMerkle.it->left;
		level++;
	}
	while (j <= level)
	{
		map.push_back(1);
		map.push_back(j);
		j++;
	}
	map.push_back(1);
	while (j > 1)
	{
		j--;
		map.push_back(j);
		map.push_back(1);
	}
	map.push_back(level);
	j = 0;
	//begin hashing.
	myMerkle.it = myMerkle.getTrunk();
	while (leftToHash > 0)
	{
		string lval = "";
		string rval = "";
		string hash = "";
		while (myMerkle.it->left &&	myMerkle.it->left->isLeaf == false)
		{
			myMerkle.it = myMerkle.it->left;
		}
		if (myMerkle.it->left) {
			lval = myMerkle.getDat(myMerkle.it->left);
		}
		if (myMerkle.it->right) {
			rval = myMerkle.getDat(myMerkle.it->right);
		}
		if (select == 1)
		{
			hash = hash_1(lval + rval);
		}
		if (select == 2)
		{
			hash = hash_2(lval + rval);
		}
		if (select == 3)
		{
			hash = hash_3(lval + rval);
		}
		myMerkle.it->data = hash;
		leftToHash--;
		if (myMerkle.it->parent) {
			for (int i = 0; i < map[j]; i++)
			{
				myMerkle.it = myMerkle.it->parent;
				if (myMerkle.it->left) {
					lval = myMerkle.getDat(myMerkle.it->left);
				}
				else { lval = ""; }
				if (myMerkle.it->right) {
					rval = myMerkle.getDat(myMerkle.it->right);
				}
				else { rval = ""; }
				if (select == 1)
				{
					hash = hash_1(lval + rval);
				}
				if (select == 2)
				{
					hash = hash_2(lval + rval);
				}
				if (select == 3)
				{
					hash = hash_3(lval + rval);
				}
			}
			myMerkle.it = myMerkle.it->right;
		}
	}
	if (myMerkle.it->parent) {
		myMerkle.it = myMerkle.it->parent;
	}
	myMerkle.setTrunk(myMerkle.it);
}

//New Method: print root node.
void pMT::printRoot()
{
	string Dat = myMerkle.getDat(myMerkle.getTrunk());
	const char * D = Dat.c_str();
	for (int i = 0; i < Dat.length(); i++)
	{
		printf("%02x", D[i]);
	}
}

//get method for binary tree.
bTREE pMT::getTree()
{
	return myMerkle;
}

//get method for selected hash
int pMT::getSelhash()
{
	return selectedHash;
}

int pMT::insert(string vote, int time)
/**
 * @brief insert a vote and time into a leaf node of tree
 * @param vote - a string
 * @param time - an int representing the time
 * @return the number of operations needed to do the insert, -1 if out of memory
 */

{
	myMerkle.opCount = 0;
	myMerkle.insert(vote, time);
	hashBranches(selectedHash);
	return myMerkle.opCount;
}

int pMT::find(string vote, int time, int hashSelect)
/**
 * @brief given a vote, timestamp, and hash function, does this vote exist in the tree?
 * @param vote, a string
 * @param time, an int
 * @param hashSelect, an int corresponding to the hash functions _1, _2, and _3
 * @return 0 if not found, else number of opperations required to find the matching vote
 */
{
	myMerkle.opCount = 0;
	if (selectedHash == hashSelect)
	{
		string found = myMerkle.locate(vote);
		string located = myMerkle.locateT(time);
		if (found.size() != 0 && located.size() != 0)
		{
			return myMerkle.opCount;
		}
	}
	return 0;
}

int pMT::findHash(string mhash)
/**
 * @brief does this hash exist in the tree?
 * @param mhash, a string to search for in the tree
 * @return 0 if not found, else number of opperations required to find the matching hash
 */
{
	myMerkle.opCount = 0;
	string found = myMerkle.locate(mhash);
	if (found.size() != 0)
	{
		return myMerkle.opCount;
	}
	return 0;
}


string pMT::locateData(string vote)
/**
 * @brief Function takes a hash of Vote and returns the sequence of (L)eft and (R)ight moves to get to that node starting from root.
 * @param vote, the data to search for
 * @return sequence of L's and R's comprising the movement to the leaf node; else return a dot '.'
 */
{
	string found = myMerkle.locate(vote);
	if (found.size() != 0)
	{
		return found;
	}
	return ".";
}

string pMT::locateHash(string mhash)
/**
 * @brief Function takes a hash and returns the sequence of (L)eft and (R)ight moves to get to that node starting from root.
 * @param mhash, the hash to search for
 * @return sequence of L's and R's comprising the movement to the hash node, ; else return a dot '.'
 */
{
	string found = myMerkle.locate(mhash);
	if (found.size() != 0)
	{
		return found;
	}
	return ".";
}


string pMT::hash_1(string key)
/**
 * @brief A function that takes in a key and returns a hash of that key using some custom function
 * @param key, a string
 * @return a hash of the key
 */
{
	const char* keyCh = key.c_str();
	string hash;
	int a = 17;
	int b = 23;
	int c = 199;
	for (int i = 0; i < key.length(); i++)
	{
		int hold = (keyCh[i]%48);
			hash += std::to_string(hold*a/c);
			c = c + a;
			a = a + b;
	}
	return hash;
}

string pMT::hash_2(string key)
/**
 * @brief A function that takes in a key and returns a hash of that key using some custom function
 * @param key, a string
 * @return a hash of the key
 */
{
	const char* keyCh = key.c_str();
	string hash;
	int b = 59;
	int a = 139;
	for (int i = key.size(); i > 0; i--)
	{
		int hold = (keyCh[i] % 48);
		hash += std::to_string(hold *b/a);
		b = b + a;
	}
	return hash;
}

string pMT::hash_3(string key)
/**
 * @brief A function that takes in a key and returns a hash of that key using some custom function
 * @param key, a string
 * @return a hash of the key
 */
{
	const char* keyCh = key.c_str();
	string hash;
	int sum = 0;
	for (int i = key.size(); i > 0; i--)
	{
		sum = sum + (int(keyCh[i])%48) * 1313;
		hash +=std::to_string(sum);
	}
	return hash;
}

 bool operator ==(const pMT& lhs, const pMT& rhs)
/**
 * @brief Comparison between two merkle trees
 * @param lhs, the left hand side of the equality statment
 * @param rhs, the right hand side of the equality statement
 * @return true if equal, false otherwise
 */
{
	 if (lhs.myMerkle == rhs.myMerkle)
	 {

		 return true;
	 }
	 else { return false; }
}

 bool operator !=(const pMT& lhs, const pMT& rhs)
/**
 * @brief Comparison between two merkle trees
 * @param lhs, the left hand side of the equality statment
 * @param rhs, the right hand side of the equality statement
 * @return true if not equal, false otherwise
 */
{
	 if (lhs.myMerkle != rhs.myMerkle)
	 {
		 return true;
	 }
	 else { return false; }
}


 std::ostream& operator <<(std::ostream& out, const pMT& p)
/**
 * @brief Print out a tree
 * @param out
 * @param p
 * @return a tree to the screen
 */
{
	pMT hold = p;
	bTREE K = hold.getTree();
	K.print(K.getTrunk(), 0);
	return out;
}


 pMT operator ^(const pMT& lhs, const pMT& rhs)
/**
 * @brief Where do two trees differ
 * @param lhs
 * @param rhs
 * @return a tree comprised of the right hand side tree nodes that are different from the left
 */
{
	 pMT left = lhs;
	 pMT right = rhs;
	 if (left.getSelhash() == right.getSelhash()) {
		 bTREE L = left.getTree();
		 bTREE R = right.getTree();
		 bTREE* result = L^R;
		 pMT* ven = new pMT(left.getSelhash(), *result);
		 return *ven;
	 }
	 else { cout <<endl<< "The Two Merkle Tree's use different hash functions." << endl; }
}

#ifndef PERSONPROFILE
#define PERSONPROFILE

#include <iostream>
#include <list>
#include <vector>
#include "provided.h"
#include "RadixTree.h"
using namespace std;

class PersonProfile {
public:
	PersonProfile(string name, string email);
	~PersonProfile();
	string GetName() const;
	string GetEmail() const;
	void AddAttValPair(const AttValPair& attval);
	int GetNumAttValPairs() const;
	bool GetAttVal(int attribute_num, AttValPair& attval) const;
private:
	string m_name;
	string m_email;
	//Need to change this to a tree
	RadixTree<string> m_attVal;
	vector<AttValPair> m_attValVec;
	//list<AttValPair*> m_attVal;
	//Store List of attribute value pairs (but have to be able to insert O(N), maybe binary search
	
};

#endif //PERSONPROFILE
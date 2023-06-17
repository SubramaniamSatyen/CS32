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
	//Person profile constructor. Dynamically allocates a RadixTree
	PersonProfile(string name, string email);
	//Person profile destructor. Deallocates dynamically allocated RadixTree
	~PersonProfile();
	//Getter function for person name
	string GetName() const;
	//Getter function for person email
	string GetEmail() const;
	//Function to add a new attribute value pair to the PersonProfile
	void AddAttValPair(const AttValPair& attval);
	//Function to return the number of attribute value pairs stored in the PersonProfile
	int GetNumAttValPairs() const;
	//Function that retrieves a specified attribute value pair and stores the values in the parameter
	bool GetAttVal(int attribute_num, AttValPair& attval) const;
private:
	string m_name;
	string m_email;

	RadixTree<string>* m_attVal;
	vector<AttValPair> m_attValVec;
	
};

#endif //PERSONPROFILE
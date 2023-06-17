#include "PersonProfile.h"
#include "RadixTree.h"
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

//Person profile constructor. Dynamically allocates a RadixTree
PersonProfile::PersonProfile(string name, string email) {
	m_name = name;
	m_email = email;
	m_attVal = new RadixTree<string>();
}

//Person profile destructor. Deallocates dynamically allocated RadixTree
PersonProfile::~PersonProfile() {
	delete m_attVal;
}

//Getter function for person name
string PersonProfile::GetName() const {
	return m_name;
}

//Getter function for person email
string PersonProfile::GetEmail() const {
	return m_email;
}

//Function to add a new attribute value pair to the PersonProfile
void PersonProfile::AddAttValPair(const AttValPair& attval) { //O(C)
	//Checks if the pair has already been added
	if (m_attVal->search(attval.attribute + attval.value) == nullptr) { //O(C)
		//If not already added, add the attribute value pair to the RadixTree (as per the spec)
		m_attVal->insert(attval.attribute + attval.value, attval.attribute + attval.value); //O(C)
		//Add the attribute value pair to internal vector storage
		m_attValVec.push_back(attval); //O(1)
	}
}

//Function to return the number of attribute value pairs stored in the PersonProfile
int PersonProfile::GetNumAttValPairs() const {
	return m_attValVec.size();
}

//Function that retrieves a specified attribute value pair and stores the values in the parameter
bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const { //O(2)
	//If the attribute_num is valid
	if (attribute_num > m_attValVec.size() || attribute_num < 0) {
		//Return false to indicate failure
		return false;
	}
	//Store the attribute value pair details from the internal vector into the parameter
	attval.attribute = m_attValVec[attribute_num].attribute; //O(1)
	attval.value = m_attValVec[attribute_num].value;		//O(1)
	//Return true to indicate success
	return true;
}
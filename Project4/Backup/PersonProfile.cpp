#include "PersonProfile.h"
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

PersonProfile::PersonProfile(string name, string email) {
	m_name = name;
	m_email = email;
}

PersonProfile::~PersonProfile() {
	//if (!m_attVal.empty()) {
	//	list<AttValPair*>::iterator it = m_attVal.begin();
	//	while (it != m_attVal.end()) {
	//		it = m_attVal.erase(it);
	//	}
	//}
}

string PersonProfile::GetName() const {
	return m_name;
}

string PersonProfile::GetEmail() const {
	return m_email;
}

void PersonProfile::AddAttValPair(const AttValPair& attval) { //O(C)
	//Handle case of duplicate pairs within member insert function
	//AttValPair temp = AttValPair(attval.attribute, attval.value);
	if (m_attVal.search(attval.attribute + attval.value) == nullptr) { //O(C)
		m_attVal.insert(attval.attribute + attval.value, attval.attribute + attval.value); //O(C)
		m_attValVec.push_back(attval); //O(1)
	}
}

int PersonProfile::GetNumAttValPairs() const {
	return m_attValVec.size();
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const { //O(2)
	if (attribute_num > m_attValVec.size() || attribute_num < 0) {
		return false;
	}
	attval.attribute = m_attValVec[attribute_num].attribute; //O(1)
	attval.value = m_attValVec[attribute_num].value;		//O(1)
	return true;
}
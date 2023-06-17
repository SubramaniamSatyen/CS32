#include "MemberDatabase.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm> 
using namespace std;

MemberDatabase::MemberDatabase(){
	m_attEmail = new RadixTree<vector<string>>;
}

MemberDatabase::~MemberDatabase() {
	delete m_attEmail;
}

bool MemberDatabase::LoadDatabase(string filename) {
	ifstream infile(filename);
	if (!infile) {
		cerr << "File name error!!!!!" << endl;
		return false;
	}
	bool validFormat = true;
	while (validFormat) {
		string name, email, line, att, val, junk;
		int pairs;
		if (!getline(infile, name)) {
			validFormat = false;
			break;
		}
		if (!getline(infile, email)) {
			cerr << "Invalid format!!!!!!" << endl;
			return false;
		}
		//Check if email aready added. IF so, return false;
		if (!(infile >> pairs)) {
			cerr << "Invalid format!!!!!!" << endl;
			return false;
		}
		if (!getline(infile, junk)) { //Not sure if I need this
			cerr << "Invalid format!!!!!!" << endl;
			return false;
		}
		m_emailPeople.insert(email, PersonProfile(name, email));
		PersonProfile* person = m_emailPeople.search(email);
		for (int i = 0; i < pairs; i++) {
			if (!getline(infile, att, ',')) {
				cerr << "Invalid format!!!!!!" << endl;
				return false;
			}
			if (!getline(infile, val, '\n')) {
				cerr << "Invalid format!!!!!!" << endl;
				return false;
			}
			//Add attval pair to radixtree and to person profile
			vector<string>* temp = (m_attEmail->search(att + val));
			if (temp == nullptr) {
				vector<string> tempV;
				tempV.push_back(email);
				m_attEmail->insert(att + val, tempV);
			}
			else {
				if (find(temp->begin(), temp->end(), email) == temp->end()) {
					temp->push_back(email);
				}
			}
			AttValPair pair = AttValPair(att, val);
			person->AddAttValPair(pair);
		}
		//Add person to email profile 

		////THERE IS SOME ISSUE HERE WHERE ESSENTIALLY tHE ATTRIBUTE VALUE PAIRS ADDED TO A PERSON ARE BEING REFERENCED DIRECTLY,
		//RATHER THAN HAVING THEIR VALUES COPIED TO NEW INSTANCES ---- Fixed this by adding person first, than adding pairs directly to person.
		//m_emailPeople.insert(email, person);
		//PersonProfile* var = &person;

		if (!getline(infile, junk, '\n')) {
			validFormat = false;
			break;
		}
	}
	return true;

}

vector<string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const {
	vector<string>* vect = m_attEmail->search(input.attribute + input.value);
	if (vect != nullptr) {
		return *vect;
	}
	return vector<string>();
}
const PersonProfile* MemberDatabase::GetMemberByEmail(string email) const {
	return m_emailPeople.search(email); //O(C) - c is length of email
}
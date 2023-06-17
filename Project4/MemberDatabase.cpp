#include "MemberDatabase.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm> 
using namespace std;

//MemberDatabase Constructor. Dynamically allocates a RadixTree for the email
MemberDatabase::MemberDatabase(){
	m_attEmail = new RadixTree<vector<string>>;
}

//MemberDatabase Destructor. deletes the people pointers from the people vector (necessary due to lack of PersonProfile copy constructor)
//And deletes the dynamically allocated RadixTree.
MemberDatabase::~MemberDatabase() {
	//Deletes RadixTree
	delete m_attEmail;
	//Deletes all PersonProfiles allocated during lifetime
	for (int i = 0; i < m_people.size(); i++) {
		delete m_people[i];
	}
}

//Function to load the database from a provided file
bool MemberDatabase::LoadDatabase(string filename) {
	//If unable to load the file return false
	ifstream infile(filename);
	if (!infile) {
		return false;
	}
	//Loop through each line of the file while format is valid
	bool validFormat = true;
	while (validFormat) {
		//Initialize variables to hold the data for each person
		string name, email, line, att, val, junk;
		int pairs;
		//Load the user's name. If there is no content on this line, break
		if (!getline(infile, name)) {
			validFormat = false;
			break;
		}
		//Load the email for the specified user
		if (!getline(infile, email)) {
			return false;
		}
		//Load the number of pairs as an int
		if (!(infile >> pairs)) {
			return false;
		}
		//Move to the next line after reading the number of pairs
		if (!getline(infile, junk)) { 
			return false;
		}
		//Create a new person profile to store the data 
		PersonProfile* person = new PersonProfile(name, email);
		//Add the person profile to the email RadixTree (this PersonProfile will be copied such that the pointers in this person and the
		//copy point to the same data).
		m_emailPeople.insert(email, person);
		//Store the person to be deleted as the RadixTree is
		m_people.push_back(person);

		//Loop through the number of pairs
		for (int i = 0; i < pairs; i++) {
			//Reads in the attribute
			if (!getline(infile, att, ',')) {
				return false;
			}
			//Reads in the corresponding value
			if (!getline(infile, val, '\n')) {
				return false;
			}
			//Search for vector of emails for giving attribute value pair
			vector<string>* temp = (m_attEmail->search(att + val));
			//If no emails for the attribute value pair, create new vector
			if (temp == nullptr) {
				vector<string> tempV;
				tempV.push_back(email);
				//Add vector with email to the RadixTree
				m_attEmail->insert(att + val, tempV);
			}
			else {
				//If the email has not been added to the vector of the attribute value pair, add the email to the vector
				if (find(temp->begin(), temp->end(), email) == temp->end()) {
					temp->push_back(email);
				}
			}
			//Add the attribute value pair to the person
			AttValPair pair = AttValPair(att, val);
			person->AddAttValPair(pair);
		}
		//Read in blank line between entries of people
		if (!getline(infile, junk, '\n')) {
			validFormat = false;
			break;
		}
	}
	//Return true if successful file read
	return true;

}

//Function to find list of members that have a given attribute value pair. Returns vector of emails.
vector<string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const {
	//Finds the corresponding email addresses by searching RadixTree O(C) such that C << P (searches for the key of the attval pair)
	vector<string>* vect = m_attEmail->search(input.attribute + input.value);
	//If there are matches, return them
	if (vect != nullptr) {
		return *vect;
	}
	//Otherwise return an empty vector
	return vector<string>();
}

//Function to find the PersonProfile corresponding to the provided email
const PersonProfile* MemberDatabase::GetMemberByEmail(string email) const {
	//Searches the RadixTree to find the corresponding PersonProfile
	PersonProfile** p = m_emailPeople.search(email);
	if (p == nullptr) {
		return nullptr;
	}
	return *p; //O(C) - C is length of email. This is better than O(N), N is the number of emails
}
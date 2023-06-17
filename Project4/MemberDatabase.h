#ifndef MEMBERDATABASE
#define MEMBERDATABASE

#include <iostream>
#include "RadixTree.h"
#include "PersonProfile.h"
#include <vector>
using namespace std;

class MemberDatabase {
public:
	//MemberDatabase Constructor. Dynamically allocates a RadixTree for the email
	MemberDatabase();
	//MemberDatabase Destructor. deletes the people pointers from the people vector (necessary due to lack of PersonProfile copy constructor)
	//And deletes the dynamically allocated RadixTree.
	~MemberDatabase();
	//Function to load the database from a provided file
	bool LoadDatabase(std::string filename);
	//Function to find list of members that have a given attribute value pair. Returns vector of emails.
	std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;
	//Function to find the PersonProfile corresponding to the provided email
	const PersonProfile* GetMemberByEmail(std::string email) const;
private:
	//Data structure that maps the attributevaluepair to the user information 
	RadixTree<vector<string>>* m_attEmail;
	RadixTree<PersonProfile*> m_emailPeople;
	vector<PersonProfile*> m_people;
};

#endif //MEMBERDATABASE
#ifndef MEMBERDATABASE
#define MEMBERDATABASE

#include <iostream>
#include "RadixTree.h"
#include "PersonProfile.h"
#include <vector>
using namespace std;

class MemberDatabase {
public:
	MemberDatabase();
	~MemberDatabase();
	bool LoadDatabase(std::string filename);
	std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;
	const PersonProfile* GetMemberByEmail(std::string email) const;
private:
	//Data structure that maps the attributevaluepair to the user information 
	RadixTree<vector<string>>* m_attEmail;
	RadixTree<PersonProfile> m_emailPeople;
};

#endif //MEMBERDATABASE
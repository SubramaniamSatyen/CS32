#ifndef MATCHMAKER
#define MATCHMAKER

#include "AttributeTranslator.h"
#include "MemberDatabase.h"
#include <vector>
#include <iostream>

class MatchMaker {
public:
	//MatchMaker Constructor. Accepts a member database and an attribute as a parameter and sets pointers to them
	MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
	//MatchMaker Destrutor. 
	~MatchMaker();
	std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;
private:
	//Predicate helper function to order the emails in the vector before returning them
	bool compareRec(EmailCount& left, EmailCount& right);
	const MemberDatabase* m_mdb;
	const AttributeTranslator* m_at;
};

#endif //MATCHMAKER
#ifndef MATCHMAKER
#define MATCHMAKER

#include "AttributeTranslator.h"
#include "MemberDatabase.h"
#include <vector>
#include <iostream>

class MatchMaker {
public:
	MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
	~MatchMaker();
	std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;
private:
	bool compareRec(EmailCount& left, EmailCount& right);
	const MemberDatabase* m_mdb;
	const AttributeTranslator* m_at;
};

#endif //MATCHMAKER
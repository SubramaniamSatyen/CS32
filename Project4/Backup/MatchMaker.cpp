#include <iostream>
#include "MatchMaker.h"
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>
using namespace std;

MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at) {
	m_mdb = &mdb;
	m_at = &at;
}
MatchMaker::~MatchMaker() {

}

bool compareEC(EmailCount& left, EmailCount& right) {
	if (left.count < right.count) {
		return false;
	}
	else if (left.count == right.count) {
		//Check names
		if (left.email < right.email) {
			return false;
		}
		return true;
	}
	return true;
}

std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const {
	//Getting relevant profile
	const PersonProfile* member = m_mdb->GetMemberByEmail(email);

	unordered_map<string, AttValPair> tarAttVals;
	//Could change this to a map, (maps att+val to the attval object)
	AttValPair memAttVal;
	//Getting unique target attribute value pairs
	for (int i = 0; i < member->GetNumAttValPairs(); i++) {
		member->GetAttVal(i, memAttVal);
		vector<AttValPair> compAttVals = m_at->FindCompatibleAttValPairs(memAttVal);
		for (int j = 0; j < compAttVals.size(); j++) {
			//tarAttVals.insert(compAttVals[j]);
			tarAttVals[compAttVals[j].attribute + compAttVals[j].value] = compAttVals[j];
		}
	}
	
	//Finding target emails
	map<string, int> matchEmails;
	for (unordered_map<string, AttValPair>::iterator it = tarAttVals.begin(); it != tarAttVals.end(); it++) {
		vector<string> emails = m_mdb->FindMatchingMembers(it->second);
		for (int i = 0; i < emails.size(); i++) {
			if (emails[i] != email) {
				matchEmails[emails[i]]++;
			}
		}
	}

	vector<EmailCount> ret;
	for (map<string, int>::iterator it = matchEmails.begin(); it != matchEmails.end(); it++) {
		if (it->second >= threshold) {
			ret.push_back(EmailCount(it->first, it->second));
		}
	}
	sort(ret.begin(), ret.end(), compareEC);

	return ret;
}
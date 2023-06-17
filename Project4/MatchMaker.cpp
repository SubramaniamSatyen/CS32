#include <iostream>
#include "MatchMaker.h"
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>
using namespace std;

//MatchMaker Constructor. Accepts a member database and an attribute as a parameter and sets pointers to them
MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at) {
	m_mdb = &mdb;
	m_at = &at;
}

//MatchMaker Destrutor. 
MatchMaker::~MatchMaker() {
}

//Predicate helper function to order the emails in the vector before returning them
bool compareEC(EmailCount& left, EmailCount& right) {
	//If the left count is less than the right count, then reorder them
	if (left.count < right.count) {
		return false;
	}
	//If counts are the same use secondary ordering
	else if (left.count == right.count) {
		//If left name is greater than the right name then reorder them
		if (left.email > right.email) {
			return false;
		}
		//Otherwise don't reorder them
		return true;
	}
	//If left count is greater than right count do not reorder
	return true;
}

//MatchMaker workhorse function to map a provided user email to the other PersonProfiles that are in the member database. Returns the 
//emails that have more matches than the parameter threshold
std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const {
	//Getting relevant profile for email - O(C) 
	const PersonProfile* member = m_mdb->GetMemberByEmail(email);
	//Account for member not in database
	if (member == nullptr) {
		return vector<EmailCount>();
	}
	//Create map to store the target attribute value pairs for the provided email
	unordered_map<string, AttValPair> tarAttVals;
	
	//Creating variable to store the member's attribute values
	AttValPair memAttVal;
	
	//Iterate through each of the member's attribute value pairs
	for (int i = 0; i < member->GetNumAttValPairs(); i++) {
		//Store the member's attribute value pair data in the local variable
		member->GetAttVal(i, memAttVal);
		//Search for the corresponding attribute value pairs for the member's attribute value pair
		vector<AttValPair> compAttVals = m_at->FindCompatibleAttValPairs(memAttVal);
		//Add each target attribute value pair to the map
		for (int j = 0; j < compAttVals.size(); j++) {
			//Updates the map value to store the corresponding attribute value pair (Removing duplicates)
			tarAttVals[compAttVals[j].attribute + compAttVals[j].value] = compAttVals[j];
		}
	}

	//Create map to store member emails and their corresponding values
	unordered_map<string, int> matchEmails;
	//Iterate through the target attributes (now without duplicates) and update the relevant emails 
	for (unordered_map<string, AttValPair>::iterator it = tarAttVals.begin(); it != tarAttVals.end(); it++) {
		//Find the vector of emails that have a given attribute
		vector<string> emails = m_mdb->FindMatchingMembers(it->second);
		//Store each email in the map, updating its current value (From zero by default)
		for (int i = 0; i < emails.size(); i++) {
			if (emails[i] != email) {
				matchEmails[emails[i]]++;
			}
		}
	}

	//Create vector to return results
	vector<EmailCount> ret;
	//Move all items from the map that meet the required threshold to the vector
	for (unordered_map<string, int>::iterator it = matchEmails.begin(); it != matchEmails.end(); it++) {
		if (it->second >= threshold) {
			ret.push_back(EmailCount(it->first, it->second));
		}
	}
	
	//Sort the vector based off of the criteria in the spec with a predicate function
	sort(ret.begin(), ret.end(), compareEC);

	//Return the vector
	return ret;
}
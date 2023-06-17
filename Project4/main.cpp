//main.cpp

#include "PersonProfile.h"
#include "AttributeTranslator.h"
#include "MemberDatabase.h"
#include "MatchMaker.h"
#include "provided.h"
#include <iostream>
#include <string>
#include <vector>

const std::string MEMBERS_FILE    = "members.txt";
const std::string TRANSLATOR_FILE = "translator.txt";

bool findMatches(const MemberDatabase& mdb, const AttributeTranslator& at);

int main() {
    MemberDatabase mdb;
    if (!mdb.LoadDatabase(MEMBERS_FILE))
    {
        std::cout << "Error loading " << MEMBERS_FILE << std::endl;
        return 1;
    }
    AttributeTranslator at;
    if (!at.Load(TRANSLATOR_FILE))
    {
        std::cout << "Error loading " << TRANSLATOR_FILE << std::endl;
        return 1;
    }

    while (findMatches(mdb, at))
        ;

    std::cout << "Happy dating!" << std::endl;
}

bool findMatches(const MemberDatabase& mdb, const AttributeTranslator& at)
{
      // Prompt for email
    std::string email;
    const PersonProfile* pp;
    for (;;) {
        std::cout << "Enter the member's email for whom you want to find matches: ";
        std::getline(std::cin, email);
        if (email.empty())
            return false;
        pp = mdb.GetMemberByEmail(email);
        if (pp != nullptr)
            break;
        std::cout << "That email is not in the member database." << std::endl;
    }

      // Show member's attribute-value pairs
    std::cout << "The member has the following attributes:" << std::endl;
    for (int k = 0; k != pp->GetNumAttValPairs(); k++) {
        AttValPair av;
        pp->GetAttVal(k, av);
        std::cout << av.attribute << " --> " << av.value << std::endl;
    }

      // Prompt user for threshold
    int threshold;
    std::cout << "How many shared attributes must matches have? ";
    std::cin >> threshold;
    std::cin.ignore(10000, '\n'); 

      // Print matches and the number of matching translated attributes
    MatchMaker mm(mdb, at);
    std::vector<EmailCount> emails = mm.IdentifyRankedMatches(email, threshold);
    if (emails.empty())
        std::cout << "No member was a good enough match." << std::endl;
    else {
        std::cout << "The following members were good matches:" << std::endl;;
        for (const auto& emailCount : emails) {
            const PersonProfile* pp = mdb.GetMemberByEmail(emailCount.email);
            std::cout << pp->GetName() << " at " << emailCount.email << " with "
                      << emailCount.count << " matches!" << std::endl;
        }
    }
    std::cout << std::endl;
    return true;
}

//main.cpp

//#include "RadixTree.h"
//#include "PersonProfile.h"
//#include "provided.h"
//#include "AttributeTranslator.h"
//#include "MemberDatabase.h"
//#include "MatchMaker.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//void listCompatiblePairs(const AttributeTranslator& translator) {
//	AttValPair att("favorite_food", "del taco");
//	std::vector<AttValPair> results =
//		translator.FindCompatibleAttValPairs(att);
//	if (!results.empty()) {
//		std::cout << "Compatible attributes and values:" << std::endl;
//		for (const auto& p : results)
//			std::cout << p.attribute << " -> " << p.value << std::endl;
//	}
//}
//
//void findMemberByEmail(const MemberDatabase& md,
//	std::string member_email) {
//	const PersonProfile* ptr = md.GetMemberByEmail(member_email);
//	if (ptr != nullptr)
//		std::cout << "Found info for member: " << ptr->GetName() << std::endl;
//	else
//		std::cout << "No member has address " << member_email << std::endl;
//}
//
//int main() {
//	RadixTree<std::string> r;
//	string* test = r.search("Carey Nachenberg");
//	r.insert("key", "test");
//	RadixTree<AttValPair> rt;
//	AttValPair pair = AttValPair("hobby", "coding");
//	rt.insert("Carey Nachenberg", pair);
//	AttValPair * ptr = rt.search("Carey Nachenberg");
//	assert(ptr->attribute == "hobby");
//
//	PersonProfile pp("Carey Nachenberg", "climberkip@gmail.com");
//	pp.AddAttValPair(pair);
//	pp.AddAttValPair(pair);
//	AttValPair pair2 = AttValPair("hobby", "working");
//	AttValPair pair3 = AttValPair("job", "professor");
//	pp.AddAttValPair(pair2);
//	pp.AddAttValPair(pair3);
//	for (int k = 0; k != pp.GetNumAttValPairs(); k++) {
//		AttValPair av;
//		pp.GetAttVal(k, av);
//		std::cout << av.attribute << " -> " << av.value << std::endl;
//	}
//	
//	
//	AttributeTranslator at;
//	assert(at.Load("translator.txt"));
//	AttributeTranslator tacoTest;
//	assert(tacoTest.Load("Taco.txt"));
//	listCompatiblePairs(tacoTest);
//	assert(at.FindCompatibleAttValPairs(AttValPair("fake", "pair")).empty());
//	vector<AttValPair> temp = at.FindCompatibleAttValPairs(AttValPair("job", "historian"));
//	for (int i = 0; i < temp.size(); i++) {
//		cout << temp[i].attribute << "|" << temp[i].value << endl;
//	}
//	assert(tacoTest.FindCompatibleAttValPairs(AttValPair("occupation", "del taco employee2")).empty());
//	temp = tacoTest.FindCompatibleAttValPairs(AttValPair("favorite_food", "taco bell"));
//	for (int i = 0; i < temp.size(); i++) {
//		cout << temp[i].attribute << "|" << temp[i].value << endl;
//	}
//
//
//	MemberDatabase m;
//	assert(m.LoadDatabase("Text.txt"));
//	vector<string> prof = m.FindMatchingMembers(AttValPair("occupation", "professor"));
//	for (int i = 0; i < prof.size(); i++) {
//		cout << prof[i] << endl;
//	}
//	prof = m.FindMatchingMembers(AttValPair("hobby", "pigeon racing"));
//	for (int i = 0; i < prof.size(); i++) {
//		cout << prof[i] << endl;
//	}
//	assert(m.FindMatchingMembers(AttValPair("fake", "pair")).empty());
//	assert(m.FindMatchingMembers(AttValPair("hobby", "none")).empty());
//	assert(m.GetMemberByEmail("") == nullptr);
//	assert(m.GetMemberByEmail("satyen@hotmail.com") != nullptr);
//
//	findMemberByEmail(m, "sm0lbirg@hotmail.com");
//
//	MatchMaker mm = MatchMaker(m, tacoTest);
//	mm.IdentifyRankedMatches("climberkip@gmail.com", 1);
//	assert(mm.IdentifyRankedMatches("notreal@gmail.com", 1).empty());
//	assert(mm.IdentifyRankedMatches("climberkip@gmail.com", 10000).empty());
//	assert(mm.IdentifyRankedMatches("joe@email.com", 1).empty());
//	mm.IdentifyRankedMatches("bob@mail.com", 3);
//}

//#include "RadixTree.h"
//#include "provided.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//
//int main() {
//
//	RadixTree<AttValPair> rt;
//	//Testing building upon current nodes and reinserting
//	//rt.insert("t", AttValPair("key", "value"));
//	//rt.insert("te", AttValPair("key2", "value2"));
//	rt.insert("test", AttValPair("key3", "value3"));
//	//rt.insert("t", AttValPair("key4", "value4"));
//	//rt.insert("te", AttValPair("key5", "value5"));
//
//	//Testing building under current nodes
//	rt.insert("carwash", AttValPair("key6", "value6"));
//	rt.insert("car", AttValPair("key7", "value7"));
//
//	//Testing building adjacent to current nodes (shorter and longer than stored value)
//	rt.insert("flag", AttValPair("key8", "value8"));
//	rt.insert("flying", AttValPair("key9", "value9"));
//	rt.insert("flyer", AttValPair("key10", "value10"));
//
//	//Testing with suggest edge cases
//	rt.insert("water", AttValPair("key11", "value11"));
//	rt.insert("slow", AttValPair("key12", "value12"));
//	rt.insert("slower", AttValPair("key13", "value13"));
//	rt.insert("team", AttValPair("key14", "value14"));
//	rt.insert("toast", AttValPair("key15", "value15"));
//
//	RadixTree<AttValPair> r;
//	r.insert("temperature", AttValPair("1", "1"));
//	r.insert("telephone", AttValPair("2", "2"));
//	r.insert("test", AttValPair("3", "3"));
//	r.insert("testing", AttValPair("4", "4"));
//	r.insert("testing", AttValPair("5", "5"));
//	r.insert("tested", AttValPair("6", "6"));
//	r.insert("tell", AttValPair("7", "7"));
//	r.insert("tame", AttValPair("8", "8"));
//	r.insert("tacos", AttValPair("9", "9"));
//	r.insert("tacoes", AttValPair("10", "10"));
//	r.insert("tac", AttValPair("11", "11"));
//	r.insert("waste", AttValPair("12", "12"));
//	r.insert("wad", AttValPair("13", "13"));
//	r.insert("will", AttValPair("14", "14"));
//	r.insert("tape", AttValPair("15", "15"));
//	r.insert("tap", AttValPair("16", "16"));
//	r.insert("tempered", AttValPair("17", "17"));
//	r.insert("tempering", AttValPair("18", "18"));
//
//	AttValPair* temp;
//	temp = r.search("tape");
//}
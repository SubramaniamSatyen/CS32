#include "AttributeTranslator.h"
#include <iostream>
#include <fstream>
#include <algorithm> 
#include <sstream>
using namespace std;

AttributeTranslator::AttributeTranslator() {
	m_tree = new RadixTree<vector<AttValPair>>;
}

AttributeTranslator::~AttributeTranslator() {
	delete m_tree;
}

bool AttributeTranslator::Load(string filename) { //Ignore empty lines
	ifstream infile(filename);
	if (!infile) {
		cerr << "File name error!!!!!" << endl;
		return false;
	}
	string line;
	while (getline(infile, line)) {
		istringstream iss(line);
		string srcAtt, srcVal, comAtt, comVal;
		if (line == "") {
			continue;
		}
		if (!getline(iss, srcAtt, ',')) {
			cerr << "Invalid format!!!!!!" << endl;
			return false;
		}
		if (!getline(iss, srcVal, ',')) {
			cerr << "Invalid format!!!!!!" << endl;
			return false;
		}
		if (!getline(iss, comAtt, ',')) {
			cerr << "Invalid format!!!!!!" << endl;
			return false;
		}
		if (!getline(iss, comVal, ',')) {
			cerr << "Invalid format!!!!!!" << endl;
			return false;
		}
		AttValPair pair = AttValPair(comAtt, comVal);
		vector<AttValPair>* temp = (m_tree->search(srcAtt + srcVal));
		if (temp == nullptr) {
			vector<AttValPair> tempV;
			tempV.push_back(pair);
			m_tree->insert(srcAtt + srcVal, tempV);
		}
		else {
			if (find(temp->begin(), temp->end(), pair) == temp->end()) {
				temp->push_back(pair);
			}
		}
	}
	return true;
}

vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const {
	vector<AttValPair>* pairs = m_tree->search(source.attribute + source.value); //O(C)
	if (pairs != nullptr) {
		return *pairs;
	}
	return vector<AttValPair>();
}

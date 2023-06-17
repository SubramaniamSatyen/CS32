#include "AttributeTranslator.h"
#include <iostream>
#include <fstream>
#include <algorithm> 
#include <sstream>
using namespace std;

//AttributeTranslator Constructor. Dynamically allocates a new RadixTree to hold the attribute value pairs for a given attribute value pair
AttributeTranslator::AttributeTranslator() {
	m_tree = new RadixTree<vector<AttValPair>>;
}

//AttributeTranslator Destructor. Deletes the dynamically allocated RadixTree
AttributeTranslator::~AttributeTranslator() {
	delete m_tree;
}

//AttributeTranslator function to load the provided parameter file
bool AttributeTranslator::Load(string filename) {
	//Attempt to read the file
	ifstream infile(filename);
	if (!infile) {
		return false;
	}
	//Create variable to hold string content of each line
	string line;
	//While able to read in content for a line
	while (getline(infile, line)) {
		//Create variables to hold the content of the line
		istringstream iss(line);
		string srcAtt, srcVal, comAtt, comVal;
		//If line is empty, move to next line
		if (line == "") {
			continue;
		}
		//Load the first attribute from the line
		if (!getline(iss, srcAtt, ',')) {
			//If content does not exist, return false
			return false;
		}
		//Load the first value from the line
		if (!getline(iss, srcVal, ',')) {
			//If content does not exist return false
			return false;
		}
		//Load the second attribute from the line
		if (!getline(iss, comAtt, ',')) {
			//If the content does not exist return false
			return false;
		}
		//Load the second value from the line
		if (!getline(iss, comVal, ',')) {
			//If the content does not exist return false
			return false;
		}
		//Load the attribute value pair into a struct
		AttValPair pair = AttValPair(comAtt, comVal);
		//Determine if the first attribute value pair exists in the RadixTree - O(C)
		vector<AttValPair>* temp = (m_tree->search(srcAtt + srcVal));
		//If there is are no corresponding attribute value pairs in the RadixTree
		if (temp == nullptr) {
			//Create a vector to hold the corresponding attribute value pair
			vector<AttValPair> tempV;
			tempV.push_back(pair);
			//Add the vector to the tree
			m_tree->insert(srcAtt + srcVal, tempV);
		}
		//If there are already some corresponding attribute value pairs for the first attribute value pair
		else {
			//If the attribute value pair does not exist in the vector add it - O(K), K is the max number of corresponding matches
			if (find(temp->begin(), temp->end(), pair) == temp->end()) {
				temp->push_back(pair);
			}
		}
	}
	//Return true if no issues reading file
	return true;
}

//Function to return the attribute value pairs that correspond to the provided parameter
vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const {
	//Get vector from RadixTree for the given attribute value pair
	vector<AttValPair>* pairs = m_tree->search(source.attribute + source.value); //O(C)
	//If vector exists return it
	if (pairs != nullptr) {
		return *pairs;
	}
	//Otherwise return an empty vector
	return vector<AttValPair>();
}

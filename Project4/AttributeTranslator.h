#ifndef ATTRIBUTETRANSLATOR
#define ATTRIBUTETRANSLATOR

#include <vector>
#include "RadixTree.h"
#include "provided.h"

class AttributeTranslator {
public:
	//AttributeTranslator Constructor. Dynamically allocates a new RadixTree to hold the attribute value pairs for a given attribute value pair
	AttributeTranslator();
	//AttributeTranslator Destructor. Deletes the dynamically allocated RadixTree
	~AttributeTranslator();
	//AttributeTranslator function to load the provided parameter file
	bool Load(string filename);
	//Function to return the attribute value pairs that correspond to the provided parameter
	vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;
private:
	RadixTree<vector<AttValPair>>* m_tree;
};

#endif //ATTRIBUTETRANSLATOR
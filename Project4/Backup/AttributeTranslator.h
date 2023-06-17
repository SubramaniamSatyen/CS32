#ifndef ATTRIBUTETRANSLATOR
#define ATTRIBUTETRANSLATOR

#include <vector>
#include "RadixTree.h"
#include "provided.h"

class AttributeTranslator {
public:
	AttributeTranslator();
	~AttributeTranslator();
	bool Load(string filename);
	vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;
private:
	RadixTree<vector<AttValPair>>* m_tree;
};

#endif //ATTRIBUTETRANSLATOR
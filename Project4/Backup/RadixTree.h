#ifndef RADIXTREE
#define RADIXTREE

#include <iostream>
#include <map>           
#include <vector>
#include <string>
using namespace std;

template <typename ValueType>
class RadixTree {
public:
	RadixTree();
	~RadixTree();
	void insert(std::string key, const ValueType& value);
	ValueType* search(std::string key) const;
private:
	struct Node {
		string m_curr;
		Node* m_after[128] = {};

		ValueType* m_value;
	};

	void insertHelper(string key, const ValueType& value, Node*& root);
	int findConflict(string s, string l) const;
	void splitNode(string key, int index, const ValueType& value, Node*& root);
	ValueType* searchHelper(string key, Node* root) const;
	void copyChildren(Node* modRoot, Node* root);
	//ValueType* searchBinary(std::string key) const;
	Node* m_RadixTree;
	map<std::string, ValueType*> m_mapRadixTree;
};

template <typename ValueType>
RadixTree<ValueType>::RadixTree() {
	m_RadixTree = new Node();
}

template <typename ValueType>
RadixTree<ValueType>::~RadixTree() {
	//Perhaps call recursive function to travesrse tree and delete nodes (postorder)
}

template <typename ValueType>
void RadixTree<ValueType>::insert(std::string key, const ValueType& value) {
	insertHelper(key, value, m_RadixTree);
}

template <typename ValueType>
int RadixTree<ValueType>::findConflict(string s, string l) const {
	for (int i = 0; i < s.length(); i++) {
		if (s[i] != l[i]) {
			return i;
		}
	}
	return -1;
}

template <typename ValueType>
void RadixTree<ValueType>::copyChildren(Node* modRoot, Node* root) {
	for (int i = 0; i < 128; i++) {
		modRoot->m_after[i] = root->m_after[i];
		root->m_after[i] = nullptr;
	}
}

template <typename ValueType>
void RadixTree<ValueType>::splitNode(string key, int index, const ValueType& value, Node*& root) {
	Node* modRoot = new Node();
	int modIndex = root->m_curr[index]/* - 'a'*/;
	modRoot->m_curr = root->m_curr.substr(index + 1);
	modRoot->m_value = root->m_value;
	//Copy children down to new node (may be able to just move array down if we have pointer to array instead of physical array)
	//for (int i = 0; i < 128; i++) {
	//	modRoot->m_after[i] = root->m_after[i];
	//	root->m_after[i] = nullptr;
	//}
	copyChildren(modRoot, root);

	root->m_after[modIndex] = modRoot;


	Node* keyNode = new Node();
	modIndex = key[index]/* - 'a'*/;
	keyNode->m_curr = key.substr(index + 1);
	keyNode->m_value = new ValueType(value);

	root->m_after[modIndex] = keyNode;

	root->m_value = nullptr;
	root->m_curr = key.substr(0, index);
}

template <typename ValueType>
void RadixTree<ValueType>::insertHelper(string key, const ValueType& value, Node*& root) {
	if (root != nullptr) {
		if (root->m_curr == key) {
			root->m_value = new ValueType(value);
			return;
		}
		if (root->m_curr.length() <= key.length()) {
			int index = findConflict(root->m_curr, key);
			if (index == -1) {
				//Create new leaf node starting from index of key m_curr.length()
				int ch = key[root->m_curr.length()] /*- 'a'*/;

				if (root->m_after[ch] != nullptr) {
					//Move down node and try again
					insertHelper(key.substr(root->m_curr.length() + 1), value, root->m_after[ch]);
				}
				else {
					Node* temp = new Node();
					if (key.length() - root->m_curr.length() > 1) {
						temp->m_curr = key.substr(root->m_curr.length() + 1);
					}
					temp->m_value = new ValueType(value);
					root->m_after[ch] = temp;
				}
			}
			//If part or none of the word agrees with current stored value
			else {
				splitNode(key, index, value, root);
			}
		}
		else {
			int index = findConflict(key, root->m_curr);
			//Key is a part of the current root's word
			if (index == -1) {
				Node* temp = new Node();

				temp->m_curr = root->m_curr.substr(key.length() + 1);
				temp->m_value = root->m_value;
				copyChildren(temp, root);

				int index = root->m_curr[key.length()] /* - 'a'*/;
				root->m_after[index] = temp;

				root->m_curr = key;
				root->m_value = new ValueType(value);
			}
			else {
				splitNode(key, index, value, root);
			}
		}
	}
}


template <typename ValueType>
ValueType* RadixTree<ValueType>::search(std::string key) const {
	return searchHelper(key, m_RadixTree);
	//if (m_mapRadixTree.empty()) {
	//	return nullptr;
	//}
	//const typename map<string, ValueType*>::const_iterator it = m_mapRadixTree.find(key);
	//if (it == m_mapRadixTree.end()) {
	//	return nullptr;
	//}
	//return it->second;
}

template <typename ValueType>
ValueType* RadixTree<ValueType>::searchHelper(string key, Node* root) const {
	if (root == nullptr) {
		return nullptr;
	}

	if (key.length() == 0) {
		return root->m_value;
	}

	if (root->m_curr != "") {
		if (findConflict(root->m_curr, key) != -1) {
			return nullptr;
		}
		key = key.substr(root->m_curr.length());
	}
	if (key.length() == 0) {
		return root->m_value;
	}

	//Keep moving downward
	if (key.length() > 0) {
		int index = key[0]/* - 'a'*/;
		key = key.substr(1);
		return searchHelper(key, root->m_after[index]);
	}
	return nullptr;
}

#endif //RADIXTREE
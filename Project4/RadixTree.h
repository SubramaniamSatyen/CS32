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
	//RadixTree constructor. Creates empty root node for the tree
	RadixTree();
	//RadixTree destructor. Recursively deletes the ValueType values of the tree, as well as all nodes of the tree
	~RadixTree();
	//Recursively insert a given key and value into the RadixTree
	void insert(std::string key, const ValueType& value);
	ValueType* search(std::string key) const;
private:
	//Node struct to represent node of RadixTree
	struct Node {
		string m_curr;
		vector<Node*> m_after = vector<Node*>(128);
		ValueType* m_value;
	};

	//Recursive helper function to insert a node into the Radix Tree - less than O(K)
	void insertHelper(string key, const ValueType& value, Node*& root);
	//Helper function to determine index of first conflict between two strings
	int findConflict(string s, string l) const;
	//Helper function to split the current node based off the key, an index which it differs from the root, a value for the key, and the
	//root node to split.
	void splitNode(string key, int index, const ValueType& value, Node*& root);
	ValueType* searchHelper(string key, Node* root) const;
	void copyChildren(Node* modRoot, Node* root);
	//Helper function to recursively delete the tree by visiting nodes, deleting dynamically allocated values, deleting child nodes,
	//then deleting nodes themselves.
	void destroy(Node* root);
	//ValueType* searchBinary(std::string key) const;
	Node* m_RadixTree;
};

template <typename ValueType>
//RadixTree constructor. Creates empty root node for the tree
RadixTree<ValueType>::RadixTree() {
	m_RadixTree = new Node();
}

template <typename ValueType>
//RadixTree destructor. Recursively deletes the ValueType values of the tree, as well as all nodes of the tree
RadixTree<ValueType>::~RadixTree() {
	//Recursively delete tree in postorder traversal
	destroy(m_RadixTree);
}

template <typename ValueType>
//Helper function to recursively delete the tree by visiting nodes, deleting dynamically allocated values, deleting child nodes,
//then deleting nodes themselves.
void RadixTree<ValueType>::destroy(Node* root) {
	//Delete the value
	delete root->m_value;
	//Recursively delete any child nodes
	for (int i = 0; i < 128; i++) {
		if (root->m_after[i] != nullptr) {
			destroy(root->m_after[i]);
		}
	}
	//Delete the current node
	delete root;
}

template <typename ValueType>
//Recursively insert a given key and value into the RadixTree
void RadixTree<ValueType>::insert(std::string key, const ValueType& value) {
	//Call recursive helper function to insert key value pair
	insertHelper(key, value, m_RadixTree);
}

template <typename ValueType>
//Helper function to determine index of first conflict between two strings
int RadixTree<ValueType>::findConflict(string s, string l) const {
	//Iterate through the shorter string
	for (int i = 0; i < s.length(); i++) {
		//If characters do not match, return index
		if (s[i] != l[i]) {
			return i;
		}
	}
	//Return -1 if fully match for length of shorter string
	return -1;
}

template <typename ValueType>
//Helper function to copy the children of a node to anothe node
void RadixTree<ValueType>::copyChildren(Node* modRoot, Node* root) {
	//Uses STL swap function for vectors - O(1)
	swap(modRoot->m_after, root->m_after);
}

template <typename ValueType>
//Helper function to split the current node based off the key, an index which it differs from the root, a value for the key, and the
//root node to split.
void RadixTree<ValueType>::splitNode(string key, int index, const ValueType& value, Node*& root) {
	//Create new node to store node data after modification
	Node* modRoot = new Node();
	//Determine index of at which to add node (based off of letter of difference between key and current node)
	int modIndex = root->m_curr[index];
	//Store the root node's key fragement in the node
	modRoot->m_curr = root->m_curr.substr(index + 1);
	//Store the root node's value in the node
	modRoot->m_value = root->m_value;
	//Copy children of root node to the current node - O(1)
	copyChildren(modRoot, root);

	//Store modified node under the current node
	root->m_after[modIndex] = modRoot;

	//Create node to hold the key data
	Node* keyNode = new Node();
	//Determine the letter to store the node under
	modIndex = key[index];
	//Add the key fragment to the node
	keyNode->m_curr = key.substr(index + 1);
	//Add a copy of the value to the node
	keyNode->m_value = new ValueType(value);

	//Store the key node under the root node
	root->m_after[modIndex] = keyNode;

	//Clean up the root node. Overwrite the value from it
	root->m_value = nullptr;
	//Overwrite the key fragment to contian string up until key and node's key fragment differ
	root->m_curr = key.substr(0, index);
}

template <typename ValueType>
//Recursive helper function to insert a node into the Radix Tree - less than O(K)
void RadixTree<ValueType>::insertHelper(string key, const ValueType& value, Node*& root) {
	//Checking if we can add to the node (it is a root node and not nullptr) - O(1)
	if (root != nullptr) {
		//If we've reached the target node, add the value to it O(1)
		if (root->m_curr == key) {
			root->m_value = new ValueType(value);
			return;
		}
		//If the current node has a key fragment that is smaller than the key, see if the fragment matches the key
		if (root->m_curr.length() <= key.length()) {
			//Finding index of first conflict between key and node's key fragment - O(C), such that C << K, (sum of all C) < K
			int index = findConflict(root->m_curr, key);
			//If full key fragment matches key
			if (index == -1) {
				//Calculate index to store value (based off of next letter) - O(1)
				int ch = key[root->m_curr.length()];
				//If there is is a node branching off current node for that letter
				if (root->m_after[ch] != nullptr) {
					//Adjust key and insert into the respective node - O(alskdjf;alksdjf)
					insertHelper(key.substr(root->m_curr.length() + 1), value, root->m_after[ch]);
				}
				//If there is no node with key's next letter
				else {
					//Create new node to contain the key and value - O(1)
					Node* temp = new Node();
					//Store the rest of the key data in the node - O(1)
					if (key.length() - root->m_curr.length() > 1) {
						temp->m_curr = key.substr(root->m_curr.length() + 1);
					}
					//Store value in node - O(1)
					temp->m_value = new ValueType(value);
					//Save node in tree - O(1)
					root->m_after[ch] = temp;
				}
			}
			//If there is a conflict between the key fragment and the key, split the current node's key fragment - O(1)
			else {
				splitNode(key, index, value, root);
			}
		}
		else {
			//Finding index of first conflict between key and node's key fragment - O(C), such that C << K, (sum of all C) < K
			int index = findConflict(key, root->m_curr);
			//If the key is a part of the current root's key fragment
			if (index == -1) {
				//Create new node to store node's key fragment
				Node* temp = new Node();
				//Store key fragment string that exceeds the key in the new node
				temp->m_curr = root->m_curr.substr(key.length() + 1);
				//Store the current node's value in the new node
				temp->m_value = root->m_value;
				//Copy the current node's children to the new node - O(1)
				copyChildren(temp, root);
				//Determine the index to store the new node under
				int index = root->m_curr[key.length()] ;
				//Store the new node in the current node
				root->m_after[index] = temp;

				//Update the current node to reflect the key and value
				root->m_curr = key;
				root->m_value = new ValueType(value);
			}
			else {
				//If the node and key differ, split the current node at the index at which they differ - O(1)
				splitNode(key, index, value, root);
			}
		}
	}
}


template <typename ValueType>
//RadixTree search function that looks for the provided key in under O(K) time
ValueType* RadixTree<ValueType>::search(std::string key) const {
	//Calls helper recursive search function
	return searchHelper(key, m_RadixTree);
}

template <typename ValueType>
//Recursive helper search function that returns a pointer to the value corresponding to the key if it exists
ValueType* RadixTree<ValueType>::searchHelper(string key, Node* root) const {
	//If the root is null, key does not exist
	if (root == nullptr) {
		return nullptr;
	}
	//If the key is empty, we have reached the correct node
	if (key.length() == 0) {
		//Return the node's value
		return root->m_value;
	}
	//If the root has a key fragment
	if (root->m_curr != "") {
		//If the key fragment does not match with the key, then the key is not in the tree - O(C), C << K and (sum of all C) < K
		if (findConflict(root->m_curr, key) != -1) {
			return nullptr;
		}
		//Reduce the key by the key fragment
		key = key.substr(root->m_curr.length());
	}
	//If the key is now empty, we have reached the correct node
	if (key.length() == 0) {
		//Return the current node's value
		return root->m_value;
	}
	//If the key is still present
	if (key.length() > 0) {
		//Determine index of child array to search through
		int index = key[0];
		//Reduce key to account for the letter of the child array
		key = key.substr(1);
		//Search for the key in the specified index of the child array
		return searchHelper(key, root->m_after[index]);
	}
	//return nullptr as catch all (should never run)
	return nullptr;
}

#endif //RADIXTREE
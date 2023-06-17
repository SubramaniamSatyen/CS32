#include "Map.h"

/*
* Default Constructor
*/
Map::Map() {
	//Initialize dummy node and link it to itself circularly
	ListNode* dummy = new ListNode();
	dummy->next = dummy;
	dummy->prev = dummy;
	m_head = dummy;
	
	//Set internal size to 1
	m_len = 1;
}

/*
* Returns whether the map is empty
*/
bool Map::empty() const {
	//Return if only dummy node
	return (m_len == 1);
}

/*
* Returns number of nodes in map
*/
int Map::size() const {
	//Return number of nodes -1 (for dummy node)
	return m_len-1;
}

/*
* Inserts provided key with the corresponding value if the key is not already in the map. Returns whether the insertion was successful.
* This function will insert the key such that the map is sorted with each node's key greater than the previous.
*/
bool Map::insert(const KeyType& key, const ValueType& value){
	//Begin by pointing to node after dummy node
	ListNode* curr = m_head->next;
	//Looping through list while current node is not the dummy node
	while (curr != m_head) {
		//Return false if key already exists in list
		if (curr->key == key) {
			return false;
		}
		//If current node key is larger than provided key, move pointer to previous node (for easy inserting later) and break
		if (curr->key > key) {
			curr = curr->prev;
			break;
		}
		//Move pointer to next node
		curr = curr->next;
		//If looped through entire list, move pointer to last item in list and break
		if (curr == m_head) {
			curr = curr->prev;
			break;
		}
	}

	//Create new temporary node with provided key and value
	ListNode* temp = new ListNode();
	temp->key = key;
	temp->val = value;

	//Set temporary node's previous and next nodes to their respective values 
	temp->prev = curr;
	temp->next = curr->next;
	//Update node after temp to point to temp, then update node before temp to point to temp
	curr->next->prev = temp;
	curr->next = temp;

	//Increase size of map and return true
	m_len++;
	return true;
}

/*
* If provided key is in the map, update the corresponding value with the provided value, returning whether the update was successful.
*/
bool Map::update(const KeyType& key, const ValueType& value) {
	//Looping through list starting from node after dummy node
	ListNode* curr = m_head->next;
	while (curr != m_head) {
		//If key matches, update the value and return true
		if (curr->key == key) {
			curr->val = value;
			return true;
		}
		curr = curr->next;
	}
	//If unable to find key, return false
	return false;
}

/*
* Function will attempt to both insert and update the provided key with the provided value in the map. 
*/
bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
	//Attempt to update the provided key's corresponding value (if it exists) and return whether successful
	if (update(key, value)) {
		return true;
	}
	//Otherwise, return whether the provided key and value can be inserted
	return (insert(key, value));
}

/*
* Erases key, value pair from the map if the provided key is in the map. Returns true if successful.
*/
bool Map::erase(const KeyType& key) {
	//Looping through the member list, starting from node after dummy node
	ListNode* curr = m_head->next;
	while (curr != m_head) {
		//Checking if key exists
		if (curr->key == key) {
			//Updates previous node to point to node after target node, then updates node after target to point to previous
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
			//Reduces size of list, deletes node, and returns successful
			m_len--;
			delete curr;
			return true;
		}
		curr = curr->next;
	}
	//If key not found in map, returns false
	return false;
}

/*
* Function returns true if the map contains the provided key and false if the provided key does not exist in the map.
*/
bool Map::contains(const KeyType& key) const {
	//Looping through the member list starting with the node after the dummy node
	ListNode* curr = m_head->next;
	while (curr != m_head) {
		//If key matches a key in the list, return true
		if (curr->key == key) {
			return true;
		}
		curr = curr->next;
	}
	//If key does not exist in list, return false
	return false;
}

/*
* Searches for key in map that matches provided key, and saves corresponding value in the provided value parameter if it exists.
* Returns true if key exists, and returns false, leaving the value parameter unchanged, if key does not.
*/
bool Map::get(const KeyType& key, ValueType& value) const {
	//Looping through member list starting with node after dummy node
	ListNode* curr = m_head->next;
	while (curr != m_head) {
		//If key is present in list, store the corresponding value in the "value" parameter passed by reference and return true
		if (curr->key == key) {
			value = curr->val;
			return true;
		}
		curr = curr->next;
	}
	//If key is not present, return false
	return false;
}

/*
* Assuming all keys in the map were ordered from least to greatest using string comparisons (< and >), stores the key and value of the 
* ith key in the two passed by reference parameters. Since list is sorted on insertion, for valid i, stores the values of the ith node
* in the parameters, returning true if successful and false (leaving parameters unchanged) if unsuccessful.
*/
bool Map::get(int i, KeyType& key, ValueType& value) const {
	//Verifying i is valid for current length of list
	if (i >= 0 && i < m_len-1) {
		//starting from node after dummy node
		ListNode* curr = m_head->next;
		//Moving through i nodes
		for (int j = 0; j < i; j++) {
			curr = curr->next;
		}
		//Store key and value of the ith node in parameters and return true
		key = curr->key;
		value = curr->val;
		return true;
	}
	//If i is invalid, return false
	return false;
}

/*
* This function swaps the contents of the current map and the parameter map.
*/
void Map::swap(Map& other) {
	//Switch pointers to each map's list
	ListNode* temp = other.m_head;
	other.m_head = m_head;
	m_head = temp;

	//Switch internal representation of each map's size
	int tempInt = other.m_len;
	other.m_len = m_len;
	m_len = tempInt;
}

/*
* Copy constructor: Taking another map as a parameter, create a new map based off the passed in map.
*/
Map::Map(const Map& other) {
	//Create dummy node for current map, linking it to itself as the previous and next node
	ListNode* dummy = new ListNode();
	dummy->next = dummy;
	dummy->prev = dummy;
	//Save new list as part of the map. Update internal size of map to the same size of the parameter map
	m_head = dummy;
	m_len = other.m_len;

	//Align temporary pointer to point to the node after the dummy node of the parameter map's list
	ListNode* currOther = other.m_head->next;
	//Align temporary pointer to point to the dummy node for the current list
	ListNode* curr = m_head->next;

	//Looping through the length of the parameter map's list to add each node to new list
	for (int i = 1; i < m_len; i++) {
		//Create a new node and store the parameter map's list's values into it
		ListNode* temp = new ListNode();
		temp->key = currOther->key;
		temp->val = currOther->val;
		
		//Add node to the end of the list, updating the previous node to point to the new node, the new node to point to 
		//the previous node, and updating the new node to point to the head (to be circular)
		curr->next = temp;
		temp->prev = curr;
		temp->next = m_head;
		m_head->prev = temp;

		//Move both temporary pointers to the next node
		curr = curr->next;
		currOther = currOther->next;
	}
}

/*
* Map destructor: Destroys dynamically allocated linked list member.
*/
Map::~Map() {
	//Looping through the map's list starting from after dummy node
	ListNode* curr = m_head->next;
	while (curr != m_head) {
		//Store next node, delete current node, update current node to next node
		ListNode* temp = curr->next;
		delete curr;
		curr = temp;
	}
	//Delete the dummy node
	delete m_head;
}

/*
* Assignment operator declaration: Create new map based off of parameter map. If the two maps are not the same, create new map with 
* parameter map's contents, then swap temporary map with current map. Regardless of parameters, returns reference to this map.
*/
Map& Map::operator=(const Map& other) {
	//If maps are not the same, create new map from parameter, then swap contents of temp map and current map.
	if (this != &other) {
		Map temp = Map(other);
		swap(temp);
	}
	return *this;
}

/*
* Provided two maps, merges them into result, overwriting whatever was in result. Merges all keys exclusive to either map,
* as well as any key that is present in both maps with the same value in both maps. If there is a key present in both maps
* with conflicting values, returns false after merging, otherwise returns true.
*/
bool merge(const Map& m1, const Map& m2, Map& result) {
	//Creates temporary map to hold merging content and boolean to represent success
    Map temp = Map();
    bool ret = true;

	// Initializes key and value for later use
    KeyType k;
    ValueType v;
	//Looping through the size of the first map
    for (int i = 0; i < m1.size(); i++) {
		//Stores ith key and value in k and v
        m1.get(i, k, v);
		//Checks if key is present in other map
        if (m2.contains(k)) {
			//If key present in both maps, store value in second map in v2
            ValueType v2;
            m2.get(k, v2);
			//If values match for keys, insert the key value pair into temp Map
            if (v == v2) {
                temp.insert(k, v);
            }
			//If values do not match for keys, do not insert key into temp, and update status to false
            else {
                ret = false;
            }
        }
		//If key is unique to first map, insert it into temporary map
        else {
            temp.insert(k, v);
        }
    }
	//Looping through second map
    for (int i = 0; i < m2.size(); i++) {
		//Store ith key and value from second map
        m2.get(i, k, v);
		//If key is not present in first map, add it to the temporary map
        if (!m1.contains(k)) {
            temp.insert(k, v);
        }
    }
	//Swap the temporary map with the result map (whose list will be deleted once the scope of temp ends). Return whether conflicting
	//key, value pairs were detected.
    temp.swap(result);
    return ret;
}

/*
* For each key in the provided map, store that same key in result with a different value from the original map. Implementation
* bumps each value "up" to the next key value, with the final node's key looping to the first node.
*/
void reassign(const Map& m, Map& result) {
	//Create temporary map and variables to store keys and values
	Map temp = Map();
	KeyType k;
	ValueType v;
	ValueType lastVal;
	
	//Gets value from final node and stores it
	m.get(m.size() - 1, k, v);
	lastVal = v;
	
	//Looping through the size of the map
	for (int i = 0; i < m.size(); i++) {
		//Stores key and value of the ith node in k and v
		m.get(i, k, v);
		//Inserts key with the last value into the temporary map
		temp.insert(k, lastVal);
		//Updates the last value with the (so far unused) current value for next iteration
		lastVal = v;
	}
	//Swap result with the current temporary map
	temp.swap(result);
}
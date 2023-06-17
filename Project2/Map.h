#ifndef MAP
#define MAP

#include <iostream>
#include <string>

using KeyType = std::string;
using ValueType = double;

class Map
{
public:
    Map();
    bool empty() const;
    int size() const;
    bool insert(const KeyType& key, const ValueType& value);
    bool update(const KeyType& key, const ValueType& value);
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    bool erase(const KeyType& key);
    bool contains(const KeyType& key) const;
    bool get(const KeyType& key, ValueType& value) const;
    bool get(int i, KeyType& key, ValueType& value) const;
    void swap(Map& other);

    ~Map();
    Map(const Map& other);
    Map& operator=(const Map& other);

private:
    struct ListNode {
    public:
        ListNode* prev;
        ListNode* next;
        KeyType key;
        ValueType val;
    };

    ListNode* m_head;
    int m_len;

};

bool merge(const Map& m1, const Map& m2, Map& result);
void reassign(const Map& m, Map& result);

#endif //MAP
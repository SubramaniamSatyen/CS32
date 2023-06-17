#include "newMap.h"

Map::Map() {
    m_len = 0;
    m_map = new Data[DEFAULT_MAX_ITEMS];
    m_max = DEFAULT_MAX_ITEMS;
}

Map::Map(int size) {
    if (size < 0) {
        exit(1);
    }
    m_len = 0;
    m_map = new Data[size];
    m_max = size;
}

Map::Map(const Map& other) {
    m_max = other.m_max;
    m_len = other.m_len;
    m_map = new Data[m_max];
    for (int i = 0; i < m_len; i++) {
        m_map[i].Key = other.m_map[i].Key;
        m_map[i].Val = other.m_map[i].Val;
    }
}

Map::~Map() {
    delete[] m_map;
}

Map& Map::operator=(const Map& other) {
    if (this != &other) {
        Map temp = Map(other);
        swap(temp);
    }
    return *this;
}

bool Map::empty() const {
    return m_len == 0;
}

int Map::size() const {
    return m_len;
}

bool Map::insert(const KeyType& key, const ValueType& value) {
    if (m_len == m_max) {
        return false;
    }
    int loc = 0;
    for (int i = 0; i < m_len; i++) {
        if (m_map[i].Key == key) {
            return false;
        }
        if (m_map[loc].Key < key) {
            loc++;
        }
    }
    for (int i = m_len; i > loc; i--) {
        m_map[i] = m_map[i - 1];
    }
    m_map[loc].Key = key;
    m_map[loc].Val = value;
    m_len++;
    return true;
}

bool Map::update(const KeyType& key, const ValueType& value) {
    int i;
    for (i = 0; i < m_len; i++) {
        if (m_map[i].Key == key) {
            break;
        }
    }
    if (i == m_len) {
        return false;
    }
    m_map[i].Val = value;
    return true;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
    if (update(key, value)) {
        return true;
    }
    else if (insert(key, value)) {
        return true;
    }
    return false;
}

bool Map::erase(const KeyType& key) {
    int i;
    for (i = 0; i < m_len; i++) {
        if (m_map[i].Key == key) {
            break;
        }
    }
    if (i == m_len) {
        return false;
    }
    for (i; i < m_len - 1; i++) {
        m_map[i] = m_map[i + 1];
    }
    m_len--;
    return true;
}

bool Map::contains(const KeyType& key) const {
    for (int i = 0; i < m_len; i++) {
        if (m_map[i].Key == key) {
            return true;
        }
    }
    return false;
}

bool Map::get(const KeyType& key, ValueType& value) const {
    for (int i = 0; i < m_len; i++) {
        if (m_map[i].Key == key) {
            value = m_map[i].Val;
            return true;
        }
    }
    return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const {
    if (i < m_len && i >= 0) {
        key = m_map[i].Key;
        value = m_map[i].Val;
        return true;
    }
    return false;
}

void Map::swap(Map& other) {
    Data* temp = other.m_map;
    other.m_map = m_map;
    m_map = temp;

    int tempInt = other.m_max;
    other.m_max = m_max;
    m_max = tempInt;

    tempInt = other.m_len;
    other.m_len = m_len;
    m_len = tempInt;
}

#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

const KeyType DUMMY = "junk";
const KeyType DEFAULT = "";
const KeyType ARRAY[6] = {
    "alfa", "baker", "charlie", "delta", "echo", "foxtrot"
};

const ValueType DUMMYV = 123;
const ValueType DEFAULTV = 0;
const ValueType ARRAYV[6] = { 10, 20, 30, 40, 50, 60 };

bool has(const Map& m, const KeyType& k, const ValueType& v)
{
    ValueType v2 = DEFAULTV;
    m.get(k, v2);
    ValueType v3 = DUMMYV;
    m.get(k, v3);
    return v2 == v && v3 == v;
}

const int SPEC_MAX = 260;

bool get2type(bool (Map::*)(const KeyType&, ValueType&) const) { return true; }
bool get2type(bool (Map::*)(const KeyType&, ValueType&)) { return false; }
bool get2type(...) { return false; }
bool get3type(bool (Map::*)(int, KeyType&, ValueType&) const) { return true; }
bool get3type(bool (Map::*)(int, KeyType&, ValueType&)) { return false; }
bool get3type(...) { return false; }

void testone(int n)
{
	if (n <= 5)
	{
		switch (n)
		{
		default: {
			cout << "Bad argument" << endl;
		} break; case  1: {
			assert((is_same<decltype(&Map::empty), bool (Map::*)() const>::value));
		} break; case  2: {
			assert((is_same<decltype(&Map::size), int (Map::*)() const>::value));
		} break; case  3: {
			assert((is_same<decltype(&Map::contains), bool (Map::*)(const KeyType&) const>::value));
		} break; case  4: {
			assert(get2type(&Map::get));
		} break; case  5: {
			assert(get3type(&Map::get));
		}
		}
		return;
	}
	Map m;
	switch (n)
	{
	default: {
		cout << "Bad argument" << endl;
	} break; case  1: {
		assert((is_same<decltype(&Map::empty), bool (Map::*)() const>::value));
	} break; case  2: {
		assert((is_same<decltype(&Map::size), int (Map::*)() const>::value));
	} break; case  3: {
		assert((is_same<decltype(&Map::contains), bool (Map::*)(const KeyType&) const>::value));
	} break; case  4: {
		assert(get2type(&Map::get));
	} break; case  5: {
		assert(get3type(&Map::get));
	} break; case  6: {
		assert(m.empty());
	} break; case  7: {
		assert(m.size() == 0);
	} break; case  8: {
		assert(!m.update(DEFAULT, DUMMYV) && m.size() == 0);
	} break; case  9: {
		assert(!m.erase(DEFAULT) && m.size() == 0);
	} break; case 10: {
		assert(!m.contains(DEFAULT));
	} break; case 11: {
		ValueType v = DUMMYV;
		assert(!m.get(DEFAULT, v) && v == DUMMYV);
	} break; case 12: {
		KeyType k = DEFAULT;
		ValueType v = DUMMYV;
		assert(!m.get(0, k, v) && k == DEFAULT && v == DUMMYV);
	} break; case 13: {
		assert(m.insert(DUMMY, DUMMYV));
	} break; case 14: {
		m.insert(DUMMY, DUMMYV);
		assert(!m.empty());
	} break; case 15: {
		m.insert(DUMMY, DUMMYV);
		assert(m.size() == 1);
	} break; case 16: {
		m.insert(DUMMY, DUMMYV);
		assert(m.contains(DUMMY));
	} break; case 17: {
		m.insert(DUMMY, DUMMYV);
		ValueType v = DEFAULTV;
		assert(m.get(DUMMY, v));
	} break; case 18: {
		m.insert(DUMMY, DUMMYV);
		ValueType v = DEFAULTV;
		m.get(DUMMY, v);
		assert(v == DUMMYV);
	} break; case 19: {
		m.insert(ARRAY[1], DUMMYV);
		ValueType v = DEFAULTV;
		assert(!m.get(ARRAY[0], v) && !m.get(ARRAY[2], v));
	} break; case 20: {
		m.insert(ARRAY[1], ARRAYV[1]);
		ValueType v = DUMMYV;
		m.get(ARRAY[0], v);
		assert(v == DUMMYV);
		m.get(ARRAY[2], v);
		assert(v == DUMMYV);
	} break; case 21: {
		m.insert(DUMMY, DUMMYV);
		KeyType k = DEFAULT;
		ValueType v = DEFAULTV;
		assert(m.get(0, k, v));
	} break; case 22: {
		m.insert(DUMMY, DUMMYV);
		KeyType k = DEFAULT;
		ValueType v = DEFAULTV;
		m.get(0, k, v);
		assert(k == DUMMY && v == DUMMYV);
	} break; case 23: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		assert(!m.empty() && m.size() == 2);
	} break; case 24: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		assert(m.contains(ARRAY[0]) && m.contains(ARRAY[1]));
	} break; case 25: {
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[0], ARRAYV[0]);
		assert(has(m, ARRAY[0], ARRAYV[0]) && has(m, ARRAY[1], ARRAYV[1]));
	} break; case 26: {
		m.insert(ARRAY[0], DUMMYV);
		m.insert(ARRAY[1], DUMMYV);
		assert(has(m, ARRAY[0], DUMMYV) && has(m, ARRAY[1], DUMMYV));
	} break; case 27: {
		assert(m.insert(ARRAY[1], ARRAYV[1]));
		assert(m.insert(ARRAY[0], ARRAYV[0]));
	} break; case 28: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[0], ARRAYV[2]);
		assert(m.size() == 2);
	} break; case 29: {
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[2]);
		assert(has(m, ARRAY[0], ARRAYV[0]) && has(m, ARRAY[1], ARRAYV[1]));
	} break; case 30: {
		assert(m.insert(ARRAY[0], ARRAYV[0]));
		assert(m.insert(ARRAY[1], ARRAYV[1]));
		assert(!m.insert(ARRAY[0], ARRAYV[2]));
	} break; case 31: {
		assert(m.insert(ARRAY[1], ARRAYV[1]));
		assert(m.insert(ARRAY[0], ARRAYV[0]));
		assert(!m.insert(ARRAY[1], ARRAYV[1]));
	} break; case 32: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[2], ARRAYV[2]);
		m.update(ARRAY[1], DUMMYV);
		assert(m.size() == 3 && m.contains(ARRAY[0]) &&
			m.contains(ARRAY[1]) && m.contains(ARRAY[2]));
	} break; case 33: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[2], ARRAYV[2]);
		m.update(ARRAY[1], DUMMYV);
		assert(has(m, ARRAY[0], ARRAYV[0]) && has(m, ARRAY[1], DUMMYV) &&
			has(m, ARRAY[2], ARRAYV[2]));
	} break; case 34: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[2], ARRAYV[2]);
		assert(m.update(ARRAY[1], DUMMYV));
	} break; case 35: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.update(ARRAY[2], ARRAYV[0]);
		assert(m.size() == 2 && has(m, ARRAY[0], ARRAYV[0]) &&
			has(m, ARRAY[1], ARRAYV[1]) && !m.contains(ARRAY[2]));
	} break; case 36: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		assert(!m.update(ARRAY[2], ARRAYV[2]) && !m.update(ARRAY[3], ARRAYV[0]));
	} break; case 37: {
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insertOrUpdate(ARRAY[0], ARRAYV[0]);
		assert(!m.empty() && m.size() == 2);
	} break; case 38: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insertOrUpdate(ARRAY[1], ARRAYV[1]);
		assert(has(m, ARRAY[0], ARRAYV[0]) && has(m, ARRAY[1], ARRAYV[1]));
	} break; case 39: {
		m.insert(ARRAY[0], DUMMYV);
		m.insertOrUpdate(ARRAY[1], DUMMYV);
		assert(has(m, ARRAY[0], DUMMYV) && has(m, ARRAY[1], DUMMYV));
	} break; case 40: {
		assert(m.insert(ARRAY[1], ARRAYV[1]));
		assert(m.insertOrUpdate(ARRAY[0], ARRAYV[0]));
	} break; case 41: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insertOrUpdate(ARRAY[0], ARRAYV[2]);
		assert(m.size() == 2 && has(m, ARRAY[0], ARRAYV[2]) &&
			has(m, ARRAY[1], ARRAYV[1]));
	} break; case 42: {
		assert(m.insert(ARRAY[0], ARRAYV[0]));
		assert(m.insert(ARRAY[1], ARRAYV[1]));
		assert(m.insertOrUpdate(ARRAY[0], ARRAYV[2]));
	} break; case 43: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[2], ARRAYV[2]);
		m.insertOrUpdate(ARRAY[1], DUMMYV);
		assert(m.size() == 3 && has(m, ARRAY[0], ARRAYV[0]) &&
			has(m, ARRAY[1], DUMMYV) && has(m, ARRAY[2], ARRAYV[2]));
	} break; case 44: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[2], ARRAYV[2]);
		assert(m.insertOrUpdate(ARRAY[1], DUMMYV));
	} break; case 45: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insertOrUpdate(ARRAY[2], ARRAYV[0]);
		assert(m.size() == 3 && has(m, ARRAY[0], ARRAYV[0]) &&
			has(m, ARRAY[1], ARRAYV[1]) && has(m, ARRAY[2], ARRAYV[0]));
	} break; case 46: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		assert(m.insertOrUpdate(ARRAY[2], ARRAYV[2]));
	} break; case 47: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		assert(m.erase(ARRAY[1]));
	} break; case 48: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.erase(ARRAY[1]);
		assert(!m.empty() && m.size() == 1 && has(m, ARRAY[0], ARRAYV[0]) &&
			!m.contains(ARRAY[1]));
	} break; case 49: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.erase(ARRAY[0]);
		assert(!m.empty() && m.size() == 1 && has(m, ARRAY[1], ARRAYV[1]) &&
			!m.contains(ARRAY[0]));
	} break; case 50: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.erase(ARRAY[0]);
		m.erase(ARRAY[1]);
		assert(m.size() == 0);
	} break; case 51: {
		m.insert(ARRAY[3], ARRAYV[3]);
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[4], ARRAYV[4]);
		m.erase(ARRAY[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.erase(ARRAY[4]);
		m.insert(ARRAY[5], ARRAYV[5]);
		m.erase(ARRAY[3]);
		m.insert(ARRAY[2], ARRAYV[2]);
		assert(m.size() == 3 && has(m, ARRAY[1], ARRAYV[1]) &&
			has(m, ARRAY[2], ARRAYV[2]) && has(m, ARRAY[5], ARRAYV[5]) &&
			!m.contains(ARRAY[0]) && !m.contains(ARRAY[3]) &&
			!m.contains(ARRAY[4]));
	} break; case 52: {
		m.insert(ARRAY[3], ARRAYV[3]);
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[3], ARRAYV[3]);
		m.insert(ARRAY[4], ARRAYV[4]);
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[4], ARRAYV[4]);
		m.erase(ARRAY[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.erase(ARRAY[4]);
		m.insert(ARRAY[5], ARRAYV[5]);
		m.erase(ARRAY[3]);
		m.insert(ARRAY[2], ARRAYV[2]);
		m.insert(ARRAY[1], ARRAYV[1]);
		assert(m.size() == 3 && has(m, ARRAY[1], ARRAYV[1]) &&
			has(m, ARRAY[2], ARRAYV[2]) && has(m, ARRAY[5], ARRAYV[5]) &&
			!m.contains(ARRAY[0]) && !m.contains(ARRAY[3]) &&
			!m.contains(ARRAY[4]));
	} break; case 53: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		assert(!m.erase(ARRAY[2]) && m.size() == 2);
	} break; case 54: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		KeyType k;
		ValueType v;
		assert(!m.get(-1, k, v));
	} break; case 55: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		KeyType k = DUMMY;
		ValueType v = DUMMYV;
		m.get(-1, k, v);
		assert(k == DUMMY && v == DUMMYV);
	} break; case 56: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		KeyType k;
		ValueType v;
		assert(!m.get(2, k, v));
	} break; case 57: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		KeyType k = DUMMY;
		ValueType v = DUMMYV;
		m.get(2, k, v);
		assert(k == DUMMY && v == DUMMYV);
	} break; case 58: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		KeyType k = DUMMY;
		ValueType v = DUMMYV;
		m.get(0, k, v);
		assert(k == ARRAY[0]);
	} break; case 59: {
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[0], ARRAYV[0]);
		KeyType k = DUMMY;
		ValueType v = DUMMYV;
		m.get(0, k, v);
		assert(k == ARRAY[0]);
	} break; case 60: {
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[0], ARRAYV[0]);
		KeyType k0 = DUMMY;
		ValueType v0 = DUMMYV;
		m.get(0, k0, v0);
		KeyType k1 = DUMMY;
		ValueType v1 = DUMMYV;
		m.get(1, k1, v1);
		assert(k0 == ARRAY[0] && v0 == ARRAYV[0] && k1 == ARRAY[1] && v1 == ARRAYV[1]);
	} break; case 61: {
		m.insert(ARRAY[3], ARRAYV[3]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[4], ARRAYV[4]);
		m.insert(ARRAY[2], ARRAYV[2]);
		assert(m.size() == 5);
		KeyType k;
		ValueType v;
		for (int i = 0; i < 5; i++)
		{
			m.get(i, k, v);
			assert(k == ARRAY[i]);
		}
	} break; case 62: {
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[0], ARRAYV[0]);
		assert(m.size() == 2);
		KeyType k;
		ValueType v;
		for (int i = 0; i < 2; i++)
		{
			m.get(i, k, v);
			assert(k == ARRAY[i]);
		}
	} break; case 63: {
		m.insert(DEFAULT, DUMMYV);
		assert(m.size() == 1 && has(m, DEFAULT, DUMMYV));
	} break; case 64: {
		m.update(DEFAULT, DUMMYV);
		assert(m.size() == 0 && !m.contains(DEFAULT));
	} break; case 65: {
		m.insertOrUpdate(DEFAULT, DUMMYV);
		assert(m.size() == 1 && has(m, DEFAULT, DUMMYV));
	} break; case 66: {
		m.insert(DEFAULT, DUMMYV);
		m.erase(DEFAULT);
		assert(m.size() == 0 && !m.contains(DEFAULT));
	} break; case 67: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		{
			Map m2;
			m2.insert(ARRAY[2], ARRAYV[2]);
			m2.insert(ARRAY[3], ARRAYV[3]);
			m2.insert(ARRAY[1], ARRAYV[1]);
			m.swap(m2);
			assert(m.size() == 3);
		}
	} break; case 68: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		{
			Map m2;
			m2.insert(ARRAY[2], ARRAYV[2]);
			m2.insert(ARRAY[3], ARRAYV[3]);
			m2.insert(ARRAY[1], ARRAYV[1]);
			m.swap(m2);
			assert(has(m, ARRAY[1], ARRAYV[1]) && has(m, ARRAY[2], ARRAYV[2]) &&
				has(m, ARRAY[3], ARRAYV[3]) && !m.contains(ARRAY[0]));
		}
	} break; case 69: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		{
			Map m2;
			m2.insert(ARRAY[2], ARRAYV[2]);
			m2.insert(ARRAY[3], ARRAYV[3]);
			m2.insert(ARRAY[1], ARRAYV[1]);
			m.swap(m2);
			assert(m2.size() == 2);
		}
	} break; case 70: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		{
			Map m2;
			m2.insert(ARRAY[2], ARRAYV[2]);
			m2.insert(ARRAY[3], ARRAYV[3]);
			m2.insert(ARRAY[1], ARRAYV[1]);
			m.swap(m2);
			assert(has(m2, ARRAY[0], ARRAYV[0]) && has(m2, ARRAY[1], ARRAYV[1]) &&
				!m2.contains(ARRAY[2]) && !m2.contains(ARRAY[3]));
		}
	} break; case 71: {
		KeyType k;
		for (int n = 0; n < SPEC_MAX; n++)
		{
			assert(m.insert(k, DUMMYV));
			k += 'x';
		}
		assert(m.size() == SPEC_MAX);
	} break; case 72: {
		KeyType k;
		for (int n = 0; n < SPEC_MAX; n++)
		{
			assert(m.insert(k, DUMMYV));
			k += 'x';
		}
		assert(!m.insert(k, DUMMYV) && m.size() == SPEC_MAX && !m.contains(k));
	} break; case 73: {
		assert(m.insert(DUMMY, DUMMYV));
		for (int n = 0; n < 10 * SPEC_MAX; n++)
			assert(m.insertOrUpdate(DUMMY, DUMMYV));
		assert(m.size() == 1);
	} break; case 74: {
		KeyType k;
		KeyType kfirst;
		for (int n = 0; n < SPEC_MAX; n++)
		{
			if (n == 0)
			{
				kfirst = k;
				assert(m.insert(kfirst, DUMMYV));
			}
			else
				assert(m.insert(k, DUMMYV));
			k += 'x';
		}
		assert(!m.insert(k, DUMMYV));
		m.erase(kfirst);
		assert(m.insert(k, DUMMYV));
		k += 'x';
		assert(!m.insert(k, DUMMYV));
	} break; case 75: {
		// This test checked that swap takes the same amount of time
		// no matter how many items are in the Maps.
	} break; /*case 76: {
		const int CAPACITY = 2;
		Map m2(CAPACITY);
		KeyType k;
		for (int n = 0; n < CAPACITY; n++)
		{
			assert(m2.insert(k, DUMMYV));
			k += 'x';
		}
		assert(!m2.insert(k, DUMMYV));
	} break; case 77: {
		const int CAPACITY = SPEC_MAX * 2;
		Map m2(CAPACITY);
		KeyType k;
		for (int n = 0; n < CAPACITY; n++)
		{
			assert(m2.insert(k, DUMMYV));
			k += 'x';
		}
		assert(!m2.insert(k, DUMMYV));
	}*/ break; case 78: {
		// This test checked that the destructor deletes the dynamic array.
	} break; case 79: {
		// This test checked that empty Maps can be copied and properly
		// destroyed.
	} break; case 80: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[2], ARRAYV[2]);
		{
			Map m2(m);
			m2.insert(ARRAY[3], ARRAYV[3]);
			assert(m2.size() == m.size() + 1);
		}
	} break; case 81: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[2], ARRAYV[2]);
		{
			Map m2(m);
			m2.insert(ARRAY[3], ARRAYV[3]);
			assert(m2.size() == 4);
			for (int n = 0; n < m2.size(); n++)
			{
				KeyType k;
				ValueType v;
				m2.get(n, k, v);
				assert(k == ARRAY[n]);
			}
		}
	} break; case 82: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		m.insert(ARRAY[2], ARRAYV[2]);
		{
			Map m2(m);
			m2.insert(ARRAY[3], ARRAYV[3]);
			assert(m.size() == 3);
			for (int n = 0; n < m.size(); n++)
			{
				KeyType k;
				ValueType v;
				m.get(n, k, v);
				assert(k == ARRAY[n]);
			}
		}
	} break; case 83: {
		{
			Map m2;
			Map m3(m2);
			assert(m2.size() == 0 && m3.size() == 0);
			m2.insert(ARRAY[0], ARRAYV[0]);
			m3.insert(ARRAY[1], ARRAYV[1]);
			assert(m2.size() == 1 && m3.size() == 1);
			KeyType k;
			ValueType v;
			m2.get(0, k, v);
			assert(k == ARRAY[0]);
			m3.get(0, k, v);
			assert(k == ARRAY[1]);

		}
	} break; /*case 84: {
		{
			Map m2(2);
			m2.insert(ARRAY[0], ARRAYV[0]);
			m2.insert(ARRAY[1], ARRAYV[1]);
			Map m3(m2);
			assert(!m3.insert(ARRAY[2], ARRAYV[2]));
		}
	}*/ break; case 85: {
		// This test checked that the assignment operator doesn't just
		// copy a pointer.
	} break; case 86: {
		{
			Map m2;
			Map m3;
			m3.insert(ARRAY[0], ARRAYV[0]);
			m3.insert(ARRAY[1], ARRAYV[1]);
			m3 = m2;
			m2.insert(ARRAY[2], ARRAYV[2]);
			m3.insert(ARRAY[3], ARRAYV[3]);
			assert(m2.size() == 1 && m3.size() == 1);
			KeyType k;
			ValueType v;
			m2.get(0, k, v);
			assert(k == ARRAY[2]);
			m3.get(0, k, v);
			assert(k == ARRAY[3]);
		}
	} break; case 87: {
		{
			Map m2;
			Map m3;
			m3.insert(ARRAY[0], ARRAYV[0]);
			m3.insert(ARRAY[1], ARRAYV[1]);
			assert(m3.size() == 2);
			m2 = m3;
			assert(m2.size() == 2 && m3.size() == 2);
			m2.insert(ARRAY[2], ARRAYV[2]);
			m3.insert(ARRAY[3], ARRAYV[3]);
			assert(m2.size() == 3 && m3.size() == 3);
			for (int n = 0; n < m2.size(); n++)
			{
				KeyType k;
				ValueType v;
				m2.get(n, k, v);
				assert(k == ARRAY[n]);
			}
			KeyType ka[3] = { ARRAY[0], ARRAY[1], ARRAY[3] };
			for (int n = 0; n < m3.size(); n++)
			{
				KeyType k;
				ValueType v;
				m3.get(n, k, v);
				assert(k == ka[n]);
			}
		}
	} break; case 88: {
		// This test checked that the assignment operator doesn't just
		// copy a pointer.
	} break; case 89: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		{
			Map m2;
			m2.insert(ARRAY[2], ARRAYV[2]);
			m2.insert(ARRAY[3], ARRAYV[3]);
			m2.insert(ARRAY[4], ARRAYV[4]);
			m2 = m;
			m2.insert(ARRAY[5], ARRAYV[5]);
			assert(m2.size() == m.size() + 1);
		}
	} break; case 90: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		{
			Map m2;
			m2.insert(ARRAY[3], ARRAYV[3]);
			m2.insert(ARRAY[4], ARRAYV[4]);
			m2.insert(ARRAY[5], ARRAYV[5]);
			m2 = m;
			m2.insert(ARRAY[2], ARRAYV[2]);
			assert(m2.size() == 3);
			for (int n = 0; n < m2.size(); n++)
			{
				KeyType k;
				ValueType v;
				m2.get(n, k, v);
				assert(k == ARRAY[n]);
			}
		}
	} break; case 91: {
		m.insert(ARRAY[0], ARRAYV[0]);
		m.insert(ARRAY[1], ARRAYV[1]);
		{
			Map m2;
			m2.insert(ARRAY[3], ARRAYV[3]);
			m2.insert(ARRAY[4], ARRAYV[4]);
			m2.insert(ARRAY[5], ARRAYV[5]);
			m2 = m;
			m2.insert(ARRAY[2], ARRAYV[2]);
			assert(m.size() == 2);
			for (int n = 0; n < m.size(); n++)
			{
				KeyType k;
				ValueType v;
				m.get(n, k, v);
				assert(k == ARRAY[n]);
			}
		}
	} break; case 92: {
		{
			// This test checked that self-assignment doesn't change the
			// number of items in existence.
		}
	} break; case 93: {
		{
			Map m2;
			m2.insert(ARRAY[0], ARRAYV[0]);
			m2.insert(ARRAY[1], ARRAYV[1]);
			m2.insert(ARRAY[2], ARRAYV[2]);
			m2 = m2;
			m2.insert(ARRAY[3], ARRAYV[3]);
			assert(m2.size() == 4);
			for (int n = 0; n < m2.size(); n++)
			{
				KeyType k;
				ValueType v;
				m2.get(n, k, v);
				assert(k == ARRAY[n]);
			}
		}
	}
	}
}


int main()
{
    KeyType testKey = "Anything";
    ValueType testVal = 1.00;

    Map test1;                                          //Default constructor
    assert(test1.size() == 0);                          //Confirming empty map size
    assert(test1.empty());                              //Confirming empty map empty
    assert(test1.erase("Anything") == false);           //Confirming cannot erase from empty map
    assert(test1.get(testKey, testVal) == false);       //Confirming cannot get value from empty map
    assert(test1.get(0, testKey, testVal) == false);    //Confirming cannot get value from empty map
    assert(test1.update(testKey, testVal) == false);    //Confirming cannot update value in empty map

    Map test2 = Map();                                  //Explicit constructor call
    assert(test2.insert("a", 1));                       //Attempting to add various simple strings
    assert(test2.insert("c", 2));                       //Attempting to add various simple strings
    assert(test2.insert("b", 3));                       //Attempting to add various simple strings
    assert(test2.insert("e", 4));                       //Attempting to add various simple strings
    assert(test2.insert("d", 5));                       //Attempting to add various simple strings
    assert(test2.size() == 5);                          //Confirming size of updated map
    assert(test2.contains("a"));                        //Confirming map contains specified keys
    assert(test2.contains("c"));                        //Confirming map contains specified keys
    assert(test2.contains("b"));                        //Confirming map contains specified keys
    assert(test2.contains("e"));                        //Confirming map contains specified keys
    assert(test2.contains("d"));                        //Confirming map contains specified keys
    assert(!test2.contains("D"));                        //Confirming map contains specified keys
    assert(!test2.contains("A"));                        //Confirming map contains specified keys
    assert(!test2.contains("a "));                       //Confirming map contains specified keys
    assert(test2.get(0, testKey, testVal) && testKey == "a" && testVal == 1);   //Confirming order of list
    assert(test2.get(1, testKey, testVal) && testKey == "b" && testVal == 3);   //Confirming order of list
    assert(test2.get(2, testKey, testVal) && testKey == "c" && testVal == 2);   //Confirming order of list
    assert(test2.get(3, testKey, testVal) && testKey == "d" && testVal == 5);   //Confirming order of list
    assert(test2.get(4, testKey, testVal) && testKey == "e" && testVal == 4);   //Confirming order of list
    assert(!test2.insert("a", 6));                      //Cannot add value with same key
    assert(!test2.insert("c", 7));                      //Cannot add value with same key
    assert(!test2.insert("e", 8));                      //Cannot add value with same key
    assert(test2.insertOrUpdate("b", 9));               //Can update value of existing key
    assert(test2.insertOrUpdate("c", 10));              //Can update value of existing key
    assert(test2.insertOrUpdate("f", 11));              //Can add value that is not present
    assert(test2.size() == 6);                          //Verifying size of map
    assert(test2.get("a", testVal)&& testVal == 1);     //Confirming order of list
    assert(test2.get("b", testVal) && testVal == 9);    //Confirming order of list
    assert(test2.get("c", testVal) && testVal == 10);   //Confirming order of list
    assert(test2.get("d", testVal) && testVal == 5);    //Confirming order of list
    assert(test2.get("e", testVal) && testVal == 4);    //Confirming order of list
    assert(test2.get("f", testVal) && testVal == 11);   //Confirming order of list

    Map test3 = Map(test2);                             //Testing copy constructor
    assert(test3.size() == 6);                          //Confirming size of array
    assert(test3.erase("a"));                           //Confirming erase function for map
    assert(test3.erase("b"));                           //Confirming erase function for map
    assert(test3.erase("c"));                           //Confirming erase function for map
    assert(!test3.erase("Fake"));                       //Confirming erase function for map with key not in map
    assert(test3.size() == 3);                          //Confirming size of array after erasing
    assert(test3.get(0, testKey, testVal) && testKey == "d" && testVal == 5);    //Confirming order of list after erasing
    assert(test3.get(1, testKey, testVal) && testKey == "e" && testVal == 4);    //Confirming order of list after erasing
    assert(test3.get(2, testKey, testVal) && testKey == "f" && testVal == 11);   //Confirming order of list after erasing
    test1.swap(test3);                                  //Testing swap function
    assert(test1.size() == 3);                          //Confirming swap function
    assert(test3.size() == 0);                          //Confirming swap function
    assert(test1.get(0, testKey, testVal) && testKey == "d" && testVal == 5);    //Confirming order of list after swapping
    assert(test1.get(1, testKey, testVal) && testKey == "e" && testVal == 4);    //Confirming order of list after swapping
    assert(test1.get(2, testKey, testVal) && testKey == "f" && testVal == 11);   //Confirming order of list after swapping
    assert(test1.erase("d"));                           //Confirming erase function for map
    assert(test1.erase("e"));                           //Confirming erase function for map
    assert(test1.erase("f"));                           //Confirming erase function for map
    test1.swap(test3);                                  //Swapping maps back
    assert(test3.size() == 0);                          //Confirming swap worked 
    assert(test3.empty());                              //Confirming empty function after filling and erasing values
    assert(test1.empty());                              //Confirming empty function

    test3 = test2;                                      //Using assignment operator
    assert(test3.size() == 6);                          //Confirming assigned correct size
    test3.swap(test3);                                  //Attempting to swap map with itself
    assert(test3.size() == 6);                          //Confirming map still has correct size after swap
    assert(test3.update("a", 12.0));                    //Testing update function with valid key
    assert(test3.update("b", 13));                      //Testing update function with valid key
    assert(!test3.update("NOTREAL", 14));               //Testing update function with key not in map
    assert(!test3.update("A", 15));                     //Testing update function with key not in map
    
    Map test4;
    Map test5;
    Map test6;
    reassign(test3, test4);                             //Confirming reassign function
    assert(test4.size() == 6);                          //Confirming size of new array        
    assert(test4.get(0, testKey, testVal) && testVal == 11 && testKey == "a");    //Confirming proper reassignment (bumping values "up" a node)       
    assert(test4.get(1, testKey, testVal) && testVal == 12 && testKey == "b");    //Confirming proper reassignment (bumping values "up" a node)       
    assert(test4.get(2, testKey, testVal) && testVal == 13 && testKey == "c");    //Confirming proper reassignment (bumping values "up" a node)       
    assert(test4.get(3, testKey, testVal) && testVal == 10 && testKey == "d");    //Confirming proper reassignment (bumping values "up" a node)       
    assert(test4.get(4, testKey, testVal) && testVal == 5 && testKey == "e");     //Confirming proper reassignment (bumping values "up" a node)       
    assert(test4.get(5, testKey, testVal) && testVal == 4 && testKey == "f");     //Confirming proper reassignment (bumping values "up" a node)       
    reassign(test4, test5);                             //Confirming reassign function with same maps
    assert(test5.get(0, testKey, testVal) && testVal == 4 && testKey == "a");     //Confirming proper reassignment (bumping values "up" a node)       
    assert(test5.get(1, testKey, testVal) && testVal == 11 && testKey == "b");    //Confirming proper reassignment (bumping values "up" a node)       
    assert(test5.get(2, testKey, testVal) && testVal == 12 && testKey == "c");    //Confirming proper reassignment (bumping values "up" a node)       
    assert(test5.get(3, testKey, testVal) && testVal == 13 && testKey == "d");    //Confirming proper reassignment (bumping values "up" a node)       
    assert(test5.get(4, testKey, testVal) && testVal == 10 && testKey == "e");    //Confirming proper reassignment (bumping values "up" a node)       
    assert(test5.get(5, testKey, testVal) && testVal == 5 && testKey == "f");     //Confirming proper reassignment (bumping values "up" a node)       

    merge(test4, test5, test6);                         //Confirming merge function with conflicting values
    assert(test6.size() == 0);                          //Does not merge since keys are same and values are all different
    assert(test6.insert("a", 11));                      //Preparing array to test merge function
    assert(test6.insert("key1", 1.01));                 //Preparing array to test merge function
    assert(test6.insert("key2", 1.02));                 //Preparing array to test merge function

    Map test7;
    merge(test4, test6, test7);                         //Confirming merge function with matching key
    assert(test7.size() == 8);                          //Confirming merged successfully
    assert(test7.get(0, testKey, testVal) && testVal == 11 && testKey == "a");          //Confirming merged successfully  
    assert(test7.get(1, testKey, testVal) && testVal == 12 && testKey == "b");          //Confirming merged successfully  
    assert(test7.get(2, testKey, testVal) && testVal == 13 && testKey == "c");          //Confirming merged successfully  
    assert(test7.get(3, testKey, testVal) && testVal == 10 && testKey == "d");          //Confirming merged successfully  
    assert(test7.get(4, testKey, testVal) && testVal == 5 && testKey == "e");           //Confirming merged successfully  
    assert(test7.get(5, testKey, testVal) && testVal == 4 && testKey == "f");           //Confirming merged successfully  
    assert(test7.get(6, testKey, testVal) && testVal == 1.01 && testKey == "key1");     //Confirming merged successfully  
    assert(test7.get(7, testKey, testVal) && testVal == 1.02 && testKey == "key2");     //Confirming merged successfully  
    Map test8;
    assert(test6.insert("b", 999));                     //Preparing array to test merge function
    merge(test4, test6, test8);                         //Confirming merge function with one matching key, one conflicting key, and exclusive keys
    assert(test8.size() == 7);                          //Confirming merged successfully
    assert(test8.get(0, testKey, testVal) && testVal == 11 && testKey == "a");          //Confirming merged successfully  
    assert(test8.get(1, testKey, testVal) && testVal == 13 && testKey == "c");          //Confirming merged successfully  
    assert(test8.get(2, testKey, testVal) && testVal == 10 && testKey == "d");          //Confirming merged successfully  
    assert(test8.get(3, testKey, testVal) && testVal == 5 && testKey == "e");           //Confirming merged successfully  
    assert(test8.get(4, testKey, testVal) && testVal == 4 && testKey == "f");           //Confirming merged successfully  
    assert(test8.get(5, testKey, testVal) && testVal == 1.01 && testKey == "key1");     //Confirming merged successfully  
    assert(test8.get(6, testKey, testVal) && testVal == 1.02 && testKey == "key2");     //Confirming merged successfully 
    Map test9;
    merge(test4, test4, test9);                         //Confirming merge function merging map with itself
    assert(test9.get(0, testKey, testVal) && testVal == 11 && testKey == "a");    //Confirming merged successfully       
    assert(test9.get(1, testKey, testVal) && testVal == 12 && testKey == "b");    //Confirming merged successfully      
    assert(test9.get(2, testKey, testVal) && testVal == 13 && testKey == "c");    //Confirming merged successfully     
    assert(test9.get(3, testKey, testVal) && testVal == 10 && testKey == "d");    //Confirming merged successfully      
    assert(test9.get(4, testKey, testVal) && testVal == 5 && testKey == "e");     //Confirming merged successfully      
    assert(test9.get(5, testKey, testVal) && testVal == 4 && testKey == "f");     //Confirming merged successfully
    merge(test4, test4, test4);                         //Confirming merge function merging map with itself
    assert(test4.get(0, testKey, testVal) && testVal == 11 && testKey == "a");    //Confirming merged successfully       
    assert(test4.get(1, testKey, testVal) && testVal == 12 && testKey == "b");    //Confirming merged successfully      
    assert(test4.get(2, testKey, testVal) && testVal == 13 && testKey == "c");    //Confirming merged successfully     
    assert(test4.get(3, testKey, testVal) && testVal == 10 && testKey == "d");    //Confirming merged successfully      
    assert(test4.get(4, testKey, testVal) && testVal == 5 && testKey == "e");     //Confirming merged successfully      
    assert(test4.get(5, testKey, testVal) && testVal == 4 && testKey == "f");     //Confirming merged successfully    

    /*VARIOUS TEST CASE FROM PROJECT SPEC AND HW 1 TEST CASES BELOW*/
    Map msd;
    msd.insert("ccc", 80);
    msd.insert("aaa", 40);
    msd.insert("ddd", 60);
    msd.insert("bbb", 20);
    KeyType kkk = "xxx";
    ValueType vvv = 0;
    assert(!msd.get(4, kkk, vvv) && kkk == "xxx");
    assert(msd.get(1, kkk, vvv) && kkk == "bbb");

    Map m;
    assert(m.empty());
    ValueType v = -1234.5;
    assert(!m.get("abc", v) && v == -1234.5); 
    m.insert("xyz", 9876.5);
    assert(m.size() == 1);
    KeyType k = "hello";
    assert(m.get(0, k, v) && k == "xyz" && v == 9876.5);

    Map mm;
    mm.insert("Little Ricky", 3.206);
    mm.insert("Ethel", 3.538);
    mm.insert("Ricky", 3.350);
    mm.insert("Lucy", 2.956);
    mm.insert("Ethel", 3.538);
    mm.insert("Fred", 2.956);
    mm.insert("Lucy", 2.956);
    assert(mm.size() == 5);
    string x;
    double y;
    mm.get(0, x, y);
    assert(x == "Ethel"); 
    mm.get(4, x, y);
    assert(x == "Ricky"); 
    mm.get(2, x, y);
    assert(x == "Little Ricky"); 
    assert(y == 3.206); 

    Map m1;
    m1.insert("Fred", 2.956);
    Map m2;
    m2.insert("Ethel", 3.538);
    m2.insert("Lucy", 2.956);
    m1.swap(m2);
    assert(m1.size() == 2 && m1.contains("Ethel") && m1.contains("Lucy") && m2.size() == 1 && m2.contains("Fred"));

    Map gpas;
    gpas.insert("Fred", 2.956);
    assert(!gpas.contains(""));
    gpas.insert("Ethel", 3.538);
    gpas.insert("", 4.000);
    gpas.insert("Lucy", 2.956);
    assert(gpas.contains(""));
    gpas.erase("Fred");
    assert(gpas.size() == 3 && gpas.contains("Lucy") && gpas.contains("Ethel") && gpas.contains(""));
    KeyType k2;
    ValueType v2;
    assert(gpas.get(1, k2, v2) && k2 == "Ethel");
    assert(gpas.get(0, k2, v2) && k2 == "");

    Map a = Map(mm);
    Map mapp;
    mapp.insert("d", 4);
    mapp.insert("e", 5);
    mapp.insert("f", 6);
    mapp.insert("a", 1);
    mapp.insert("b", 2);
    mapp.insert("c", 3);
    mapp.insertOrUpdate("a", 7);
    mapp.insertOrUpdate("e", 8);
    assert(a.size() == 5);
    assert(mapp.size() == 6);
    assert(mapp.contains("e"));
    mapp.swap(a);
    assert(a.get(0, x, y) && x == "a" && y == 7);
    assert(a.get(1, x, y) && x == "b" && y == 2);
    assert(a.get(2, x, y) && x == "c" && y == 3);
    assert(a.get(3, x, y) && x == "d" && y == 4);
    assert(a.get(4, x, y) && x == "e" && y == 8);

	for (int i = 1; i < 94; i++) {
		if (i == 72 || i == 74 || i == 76 || i == 77 || i == 84) {
			continue;
		}
		testone(i);
	}
	testone(73);

    cout << "Passed all tests" << endl;

}
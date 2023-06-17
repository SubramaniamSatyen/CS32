#include "newMap.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Map m;  // maps strings to doubles
    assert(m.empty());
    ValueType v = -1234.5;
    assert(!m.get("abc", v) && v == -1234.5); // v unchanged by get failure
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
    assert(mm.size() == 5);  // duplicate "Ethel" and "Lucy" were not added
    string x;
    double y;
    mm.get(0, x, y);
    assert(x == "Ethel");  // "Ethel" is greater than exactly 0 items in mm
    mm.get(4, x, y);
    assert(x == "Ricky");  // "Ricky" is greater than exactly 4 items in mm
    mm.get(2, x, y);
    assert(x == "Little Ricky");  // "Little Ricky" is greater than exactly 2 items in mm
    assert(y == 3.206);  // the value corresponding to the key "Little Ricky"

    Map m1;
    m1.insert("Fred", 2.956);
    Map m2;
    m2.insert("Ethel", 3.538);
    m2.insert("Lucy", 2.956);
    //m1.swap(m2);
    //assert(m1.size() == 2 && m1.contains("Ethel") && m1.contains("Lucy") && m2.size() == 1 && m2.contains("Fred"));

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

    Map a(1000);   // a can hold at most 1000 key/value pairs
    Map b(5);      // b can hold at most 5 key/value pairs
    Map c;         // c can hold at most DEFAULT_MAX_ITEMS key/value pairs
    KeyType k3[6] = { "string1", "string2", "string3", "string4", "string5", "string6"};
    ValueType v3 = 1.00;
    
    Map test(mm);
    assert(test.size() == 5);  // duplicate "Ethel" and "Lucy" were not added
    test.get(0, x, y);
    assert(x == "Ethel");  // "Ethel" is greater than exactly 0 items in mm
    test.get(4, x, y);
    assert(x == "Ricky");  // "Ricky" is greater than exactly 4 items in mm
    test.get(2, x, y);
    assert(x == "Little Ricky");  // "Little Ricky" is greater than exactly 2 items in mm
    assert(y == 3.206);  // the value corresponding to the key "Little Ricky"
    test.erase(x);
    assert(test.size() == 4);
    assert(mm.size() == 5);
    assert(!test.get(x, y));
    assert(mm.get(x, y));

    Map testmap = mm;
    testmap.erase(x);
    assert(mm.get(x, y));
    assert(!testmap.get(x, y));
    assert(testmap.size() == 4);
    assert(mm.size() == 5);

    // No failures inserting pairs with 5 distinct keys into b
    for (int n = 0; n < 5; n++)
        assert(b.insert(k3[n], v3));

    // Failure if we try to insert a pair with a sixth distinct key into b
    assert(!b.insert(k3[5], v3));

    // When two Maps' contents are swapped, their capacities are swapped
    // as well:
    a.swap(b);
    assert(!a.insert(k3[5], v3) && b.insert(k3[5], v3));


    Map mapp;
    mapp.insert("d", 4);
    mapp.insert("e", 5);
    mapp.insert("f", 6);
    mapp.insert("a", 1);
    mapp.insert("b", 2);
    mapp.insert("c", 3);
    assert(mapp.get(0, x, y) && x == "a" && y == 1);
    assert(mapp.get(1, x, y) && x == "b" && y == 2);
    assert(mapp.get(2, x, y) && x == "c" && y == 3);
    assert(mapp.get(3, x, y) && x == "d" && y == 4);
    assert(mapp.get(4, x, y) && x == "e" && y == 5);


    cout << "Passed all tests" << endl;

}


/*
#include "newMap.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Map m;
    assert(m.insert("Fred", 2.956));
    assert(m.insert("Ethel", 3.538));
    assert(m.size() == 2);
    ValueType v = 42;
    assert(!m.get("Lucy", v) && v == 42);
    assert(m.get("Fred", v) && v == 2.956);
    v = 42;
    KeyType x = "Lucy";
    assert(m.get(0, x, v) &&
        ((x == "Fred" && v == 2.956) || (x == "Ethel" && v == 3.538)));
    KeyType x2 = "Ricky";
    assert(m.get(1, x2, v) &&
        ((x2 == "Fred" && v == 2.956) || (x2 == "Ethel" && v == 3.538)) &&
        x != x2);
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}
*/

/*
#include "newMap.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Map m;
    assert(m.insert(10, "diez"));
    assert(m.insert(20, "veinte"));
    assert(m.size() == 2);
    ValueType v = "cuarenta y dos";
    assert(!m.get(30, v) && v == "cuarenta y dos");
    assert(m.get(10, v) && v == "diez");
    v = "cuarenta y dos";
    KeyType x = 30;
    assert(m.get(0, x, v) &&
        ((x == 10 && v == "diez") || (x == 20 && v == "veinte")));
    KeyType x2 = 40;
    assert(m.get(1, x2, v) &&
        ((x2 == 10 && v == "diez") || (x2 == 20 && v == "veinte")) &&
        x != x2);
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}
*/
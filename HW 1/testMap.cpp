//
//  main.cpp
//  CS32-HW1
//
//  Created by Margaret Capetz on 1/15/22.
//

#include "Map.h"
    #include <iostream>
    #include <cassert>
    using namespace std;

    // To test a Map from string to double, leave the following #define line
    // commented out; to test a Map from int to string, remove the "//".

    // #define INT_TO_STRING

    #ifdef INT_TO_STRING

    const KeyType DUMMY_KEY = 9876543;
    const ValueType DUMMY_VALUE = "Ouch";
    const KeyType NO_SUCH_KEY = 42;
    const KeyType KEY1 = 123456789;
    const ValueType VALUE1 = "Wow!";

    #else // assume string to double

    const KeyType DUMMY_KEY = "hello";
    const ValueType DUMMY_VALUE = -1234.5;
    const KeyType NO_SUCH_KEY = "abc";
    const KeyType KEY1 = "xyz";
    const ValueType VALUE1 = 9876.5;

    #endif

    void test()
    {
        Map m;
        assert(m.empty());
        ValueType v = DUMMY_VALUE;
        assert( !m.get(NO_SUCH_KEY, v)  &&  v == DUMMY_VALUE); // v unchanged by get failure
        m.insert(KEY1, VALUE1);
        assert(m.size() == 1);
        KeyType k = DUMMY_KEY;
        assert(m.get(0, k, v)  &&  k == KEY1  &&  v == VALUE1);
    }

    void test2() {
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
                    m1.swap(m2);
                    assert(m1.size() == 2  &&  m1.contains("Ethel")  &&  m1.contains("Lucy")  &&
                           m2.size() == 1  &&  m2.contains("Fred"));

                
                Map gpas;
                    gpas.insert("Fred", 2.956);
                    assert(!gpas.contains(""));
                    gpas.insert("Ethel", 3.538);
                    gpas.insert("", 4.000);
                    gpas.insert("Lucy", 2.956);
                    assert(gpas.contains(""));
                    gpas.erase("Fred");
                    assert(gpas.size() == 3  &&  gpas.contains("Lucy")  &&  gpas.contains("Ethel")  &&
                                gpas.contains(""));
                    string k;
                    double v;
                    assert(gpas.get(1, k, v)  &&  k == "Ethel");
                    assert(gpas.get(0, k, v)  &&  k == "");
                
                cout << "all tests passed" << endl;
    }

    int main()
    {
        test();
        test2();
        cout << "Passed all tests from testMap" << endl;
    }
        


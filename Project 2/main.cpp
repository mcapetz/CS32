//
//  main.cpp
//  CS32-Proj2
//
//  Created by Margaret Capetz on 1/21/22.
//



// There are 74 test cases for problem 3 of Homework 1.  Build an executable
// from this file and Map.cpp

// There are 93 test cases for problem 5 of Homework 1.
// To test problem 5, uncomment the following line and build an executable
// from this file and newMap.cpp:

//#define TESTNEW

#ifdef TESTNEW
#include "Map.h"
#endif

#include "Map.h"

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <type_traits>
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
    return v2 == v  &&  v3 == v;
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
        assert(!m.update(DEFAULT, DUMMYV)  &&  m.size() == 0);
            } break; case  9: {
        assert(!m.erase(DEFAULT)  &&  m.size() == 0);
            } break; case 10: {
        assert(!m.contains(DEFAULT));
            } break; case 11: {
        ValueType v = DUMMYV;
        assert(!m.get(DEFAULT, v)  &&  v == DUMMYV);
            } break; case 12: {
        KeyType k = DEFAULT;
        ValueType v = DUMMYV;
        assert(!m.get(0, k, v)  &&  k == DEFAULT  &&  v == DUMMYV);
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
        assert(!m.get(ARRAY[0], v)  &&  !m.get(ARRAY[2], v));
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
        assert(k == DUMMY  &&  v == DUMMYV);
            } break; case 23: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        assert(!m.empty()   &&  m.size() == 2);
            } break; case 24: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        assert(m.contains(ARRAY[0])  &&  m.contains(ARRAY[1]));
            } break; case 25: {
        m.insert(ARRAY[1], ARRAYV[1]);
        m.insert(ARRAY[0], ARRAYV[0]);
        assert(has(m, ARRAY[0], ARRAYV[0])  &&  has(m, ARRAY[1], ARRAYV[1]));
            } break; case 26: {
        m.insert(ARRAY[0], DUMMYV);
        m.insert(ARRAY[1], DUMMYV);
        assert(has(m, ARRAY[0], DUMMYV)  &&  has(m, ARRAY[1], DUMMYV));
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
        assert(has(m, ARRAY[0], ARRAYV[0])  &&  has(m, ARRAY[1], ARRAYV[1]));
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
        assert(m.size() == 3  &&  m.contains(ARRAY[0])  &&
            m.contains(ARRAY[1])  &&  m.contains(ARRAY[2]));
            } break; case 33: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        m.insert(ARRAY[2], ARRAYV[2]);
        m.update(ARRAY[1], DUMMYV);
        assert(has(m, ARRAY[0], ARRAYV[0])  &&  has(m, ARRAY[1], DUMMYV)  &&
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
        assert(m.size() == 2  &&  has(m, ARRAY[0], ARRAYV[0])  &&
            has(m, ARRAY[1], ARRAYV[1])  &&  !m.contains(ARRAY[2]));
            } break; case 36: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        assert(!m.update(ARRAY[2], ARRAYV[2])  &&  !m.update(ARRAY[3], ARRAYV[0]));
            } break; case 37: {
        m.insert(ARRAY[1], ARRAYV[1]);
        m.insertOrUpdate(ARRAY[0], ARRAYV[0]);
        assert(!m.empty()   &&  m.size() == 2);
            } break; case 38: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insertOrUpdate(ARRAY[1], ARRAYV[1]);
        assert(has(m, ARRAY[0], ARRAYV[0])  &&  has(m, ARRAY[1], ARRAYV[1]));
            } break; case 39: {
        m.insert(ARRAY[0], DUMMYV);
        m.insertOrUpdate(ARRAY[1], DUMMYV);
        assert(has(m, ARRAY[0], DUMMYV)  &&  has(m, ARRAY[1], DUMMYV));
            } break; case 40: {
        assert(m.insert(ARRAY[1], ARRAYV[1]));
        assert(m.insertOrUpdate(ARRAY[0], ARRAYV[0]));
            } break; case 41: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        m.insertOrUpdate(ARRAY[0], ARRAYV[2]);
        assert(m.size() == 2  &&  has(m, ARRAY[0], ARRAYV[2])  &&
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
        assert(m.size() == 3  &&  has(m, ARRAY[0], ARRAYV[0])  &&
            has(m, ARRAY[1], DUMMYV)  &&  has(m, ARRAY[2], ARRAYV[2]));
            } break; case 44: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        m.insert(ARRAY[2], ARRAYV[2]);
        assert(m.insertOrUpdate(ARRAY[1], DUMMYV));
            } break; case 45: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        m.insertOrUpdate(ARRAY[2], ARRAYV[0]);
        assert(m.size() == 3  &&  has(m, ARRAY[0], ARRAYV[0])  &&
            has(m, ARRAY[1], ARRAYV[1])  &&  has(m, ARRAY[2], ARRAYV[0]));
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
        assert(!m.empty()  &&  m.size() == 1  &&  has(m, ARRAY[0], ARRAYV[0])  &&
                            !m.contains(ARRAY[1]));
            } break; case 49: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        m.erase(ARRAY[0]);
        assert(!m.empty()  &&  m.size() == 1  &&  has(m, ARRAY[1], ARRAYV[1])  &&
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
        assert(m.size() == 3  &&  has(m, ARRAY[1], ARRAYV[1])  &&
            has(m, ARRAY[2], ARRAYV[2])  &&  has(m, ARRAY[5], ARRAYV[5])  &&
            !m.contains(ARRAY[0])  &&  !m.contains(ARRAY[3])  &&
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
        assert(m.size() == 3  &&  has(m, ARRAY[1], ARRAYV[1])  &&
            has(m, ARRAY[2], ARRAYV[2])  &&  has(m, ARRAY[5], ARRAYV[5])  &&
            !m.contains(ARRAY[0])  &&  !m.contains(ARRAY[3])  &&
            !m.contains(ARRAY[4]));
            } break; case 53: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        assert(!m.erase(ARRAY[2])  &&  m.size() == 2);
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
        assert(k == DUMMY  &&  v == DUMMYV);
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
        assert(k == DUMMY  &&  v == DUMMYV);
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
        assert(k0 == ARRAY[0]  &&  v0 == ARRAYV[0]  &&  k1 == ARRAY[1]  &&  v1 == ARRAYV[1]);
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
        assert(m.size() == 1  &&  has(m, DEFAULT, DUMMYV));
            } break; case 64: {
        m.update(DEFAULT, DUMMYV);
        assert(m.size() == 0  &&  !m.contains(DEFAULT));
            } break; case 65: {
        m.insertOrUpdate(DEFAULT, DUMMYV);
        assert(m.size() == 1  &&  has(m, DEFAULT, DUMMYV));
            } break; case 66: {
        m.insert(DEFAULT, DUMMYV);
        m.erase(DEFAULT);
        assert(m.size() == 0  &&  !m.contains(DEFAULT));
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
        assert(has(m, ARRAY[1], ARRAYV[1])  &&  has(m, ARRAY[2], ARRAYV[2])  &&
            has(m, ARRAY[3], ARRAYV[3])  &&  !m.contains(ARRAY[0]));
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
        assert(has(m2, ARRAY[0], ARRAYV[0])  &&  has(m2, ARRAY[1], ARRAYV[1])  &&
            !m2.contains(ARRAY[2])  &&  !m2.contains(ARRAY[3]));
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
        assert(m.insert(k, DUMMYV)  &&  m.contains(k));
            } break; case 73: {
        assert(m.insert(DUMMY, DUMMYV));
        for (int n = 0; n < 10*SPEC_MAX; n++)
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
//        assert(!m.insert(k, DUMMYV)); //not relevant bc size is dynamic
        m.erase(kfirst);
        assert(m.insert(k, DUMMYV));
        k += 'x';
        //assert(!m.insert(k, DUMMYV)); //not relevant bc size is dynamic
#ifdef TESTNEW
            } break; case 75: {
          // This test checked that swap takes the same amount of time
          // no matter how many items are in the Maps.
            } break; case 76: {
//        const int CAPACITY = 2;
//        Map m2(CAPACITY);
//        KeyType k;
//        for (int n = 0; n < CAPACITY; n++)
//        {
//        assert(m2.insert(k, DUMMYV));
//        k += 'x';
//        }
//        assert(!m2.insert(k, DUMMYV));
            } break; case 77: {
//        const int CAPACITY = SPEC_MAX*2;
//        Map m2(CAPACITY);
//        KeyType k;
//        for (int n = 0; n < CAPACITY; n++)
//        {
//        assert(m2.insert(k, DUMMYV));
//        k += 'x';
//        }
//        assert(!m2.insert(k, DUMMYV));
            } break; case 78: {
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
        assert(m2.size() == m.size()+1);
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
        assert(m2.size() == 0  &&  m3.size() == 0);
        m2.insert(ARRAY[0], ARRAYV[0]);
        m3.insert(ARRAY[1], ARRAYV[1]);
        assert(m2.size() == 1  &&  m3.size() == 1);
        KeyType k;
        ValueType v;
        m2.get(0, k, v);
        assert(k == ARRAY[0]);
        m3.get(0, k, v);
        assert(k == ARRAY[1]);

        }
            } break; case 84: {
        {
//        Map m2(2);
//        m2.insert(ARRAY[0], ARRAYV[0]);
//        m2.insert(ARRAY[1], ARRAYV[1]);
//        Map m3(m2);
//        assert(!m3.insert(ARRAY[2], ARRAYV[2]));
        }
            } break; case 85: {
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
        assert(m2.size() == 1  &&  m3.size() == 1);
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
        assert(m2.size() == 2  &&  m3.size() == 2);
        m2.insert(ARRAY[2], ARRAYV[2]);
        m3.insert(ARRAY[3], ARRAYV[3]);
        assert(m2.size() == 3  &&  m3.size() == 3);
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
        assert(m2.size() == m.size()+1);
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
#endif
            }
    }
}

int main()
{
    
    for(int i = 1; i <= 74; i++) {
        testone(i);
        cerr << i << " passed" << endl;
    }
    
    cout << "Passed" << endl;
}


//#include "Map.h"
//
//using namespace std;
//
//#include <iostream>
//#include <cassert>
//
//void test1() { //basic functions
//    cerr << "test 1 start" << endl;
//
//    // default constructor
//  Map x;
//    // For an empty map:
//  assert(x.size() == 0);      // test size
//  assert(x.empty());          // test empty
//  assert(!x.erase("Ricky"));  // nothing to erase
//
//    Map m;
//    assert(m.size() == 0); //assert initial size is zero
//    assert(m.empty() == true); //assert the map is empty
//    m.insert("a" , 1);
//    m.insert("b" , 2);
//    m.insert("c" , 3);
//    assert(m.size() == 3); //assert size is 3 after adding 3 pairs
//    m.dump();
//    m.update("a" , 100);
//    m.dump();
//    assert(m.size() == 3); //assert size doesn't change after updating
//    m.erase("b");
//    assert(m.size() == 2); //assert size decreases after erasing
//    assert(m.contains("b") == false); //assert pair is gone after erase
//    m.dump();
//    m.erase("a");
//    m.erase("c");
//    assert(m.size() == 0); //assert size is 0 when there are no more pairs
//    assert(m.contains("a") == false); //assert erased pair is not longer in list
//    assert(m.update("a", 1) == false); //pair is no longer in map, update should return false
//
//    cerr << "test 1 passed" << endl;
//}
//
//void test2() { //insert/update functions
//    cerr << "test 2 start" << endl;
//    Map m;
//    m.insert("a" , 1);
//    m.insert("b" , 2);
//    m.insert("c" , 3);
//    assert(m.insert("a", 1) == false); //cannot insert if there is already a key existing
//    ValueType val;
//    assert(m.get("a", val) == true && val == 1); //can get and update val
//    assert(m.get("z", val) == false && val == 1); //cannot get if not in map, val is unchanged
//    assert(m.update("a", 2) == true); //can update
//    assert(m.get("a", val) == true && val == 2); //should fetch updated value
//    m.dump();
//    cerr << "test 2 passed" << endl;
//}
//
//void test3() { //2nd get function
//    cerr << "test 3 start" << endl;
//    Map m;
//    m.insert("z", 1);
//    m.insert("a", 3);
//    m.insert("g", 5);
//    m.insert("b", 4);
//    m.dump();
//
//    KeyType key;
//    ValueType val;
//    assert(m.get(0, key, val) == true && key == "a" && val == 3); //the key that is strictly greater than 0 keys is the first key which should be "a"
//    assert(m.get(-1, key, val) == false && key == "a" && val == 3); //if i < 0 then false, key/value pair should not be altered
//    assert(m.get(4, key, val) == false && key == "a" && val == 3); //if i >= size then false, key/value pair should not be altered
//    assert(m.get(1, key, val) == true && key == "b" && val == 4); //the key strictly greater than 1 key is "b" the second key
//
//    Map msd;  // KeyType is std::string, ValueType is double
//            msd.insert("ccc", 80);
//            msd.insert("aaa", 40);
//            msd.insert("ddd", 60);
//            msd.insert("bbb", 20);
//            KeyType k = "xxx";
//            ValueType v;
//            assert(!msd.get(4, k, v)  &&  k == "xxx");  // x is unchanged
//            assert(msd.get(1, k, v)  &&  k == "bbb");   // "bbb" is greater than
//                                                        // exactly 1 item
//
//    cerr << "test 3 passed" << endl;
//}
//
//void test4() {
//    cerr << "test 4 start" << endl;
//    Map m;
//    m.insert("x1", 1);
//    m.insert("x2", 1);
//    m.insert("x3", 1);
//    m.insert("x4", 1);
//    m.insert("x5", 1);
//    m.insert("x6", 1);
//    m.insert("x7", 1);
//    Map n;
//    m.swap(n);
//    assert(n.contains("x1") == true); //check that the swap works between an empty map and a filled map
//    cerr << "m" << endl;
//    m.dump();
//    cerr << "n" << endl;
//    n.dump();
//    Map l;
//    l.insert("y1", 2);
//    l.insert("y2", 2);
//    l.insert("y3", 2);
//    n.swap(l);
//    assert(n.contains("y2") == true); //check swap works between non-empty maps
//    assert(l.contains("x5") == true); //check swap works between non-empty maps
//    cerr << "n" << endl;
//    n.dump();
//    cerr << "l" << endl;
//    l.dump();
//    cerr << "test 4 passed" << endl;
//}
//
//
//void test5() { //merge function
//    cerr << "test 5 start" << endl;
//    Map m;
//    m.insert("fred", 123);
//    m.insert("ethel", 456);
//    m.insert("lucy", 789);
//
//    Map n;
//    n.insert("lucy", 789);
//    n.insert("ricky", 321);
//
//    Map o;
//    o.insert("lucy", 000);
//    o.insert("ricky", 321);
//
//    Map p; //empty
//
//    Map result;
//    assert(merge(m, n, result) == true); //merge returns true because it doesn't run into the case in which a key has two unique vals in both maps
////    cerr << "result" << endl;
////    result.dump();
////    cerr << "result end" << endl;
//
//    Map result2;
//    assert(merge(m, o, result2) == false); //merge returns false because one key has two vals in both maps
//    assert(result2.contains("ethel") == true);
//    assert(result2.contains("fred") == true);
//    assert(result2.contains("ricky") == true); //should not contain lucy because two lucy keys had 2 different values between the two maps
////    cerr << "result 2" << endl;
////    result2.dump();
////    cerr << "result 2 end" << endl;
//
//    Map result3;
//    assert(merge(m, p, result3) == true); //merge returns true because merging a non-empty and empty map should be successful
//    assert(result3.contains("fred") == true);
//    assert(result3.contains("ethel") == true);
//    assert(result3.contains("lucy") == true); //assert that result contains contents of Map m
////    cerr << "result 3" << endl;
////    result3.dump();
////    cerr << "result 3 end" << endl;
//
//    Map x;
//    Map y;
//    Map result4;
//    assert(merge(x, y, result4) == true);
//    assert(result4.empty() == true);
//
//    cerr << "test 5 passed" << endl;
//}
//
//
//void test6() {
//    cerr << "test 6 start" << endl;
//    //"Fred"  123      "Ethel"  456      "Lucy"  789      "Ricky"  321
//    Map m;
//    m.insert("fred", 123);
//    m.insert("ethel", 456);
//    m.insert("lucy", 789);
//    m.insert("ricky", 321); //testing a map that has an even size
//    Map result;
//    reassign(m, result);
//    cerr << "result" << endl;
//    result.dump();
//    cerr << "result end" << endl;
//    ValueType val;
//    assert(result.get("fred", val) == true && val != 123);
//    assert(result.get("ethel", val) == true && val != 456);
//    assert(result.get("lucy", val) == true && val != 789);
//    assert(result.get("ricky", val) == true && val != 321);
//
//    Map n;
//    n.insert("shiv", 123);
//    n.insert("tom", 456);
//    n.insert("greg", 789);
//    reassign(n, result); //testing when result is nonempty
//    cerr << "result" << endl;
//    result.dump();
//    cerr << "result end" << endl;
//    assert(result.get("shiv", val) == true && val != 123);
//    assert(result.get("tom", val) == true && val != 456);
//    assert(result.get("greg", val) == true && val != 789);
//
//    Map g;
//    g.insert("t", 1);
//    g.insert("k", 2);
//    g.insert("l", 3);
//    Map result2;
//    result2 = g; //assignment operator
//    reassign(g, result2);
//    assert(result2.get("t", val) == true && val != 1);
//    assert(result2.get("k", val) == true && val != 2);
//    assert(result2.get("l", val) == true && val != 3);
//
//    cerr << "before reassign" << endl;
//    cerr << "m" << endl;
//    m.dump();
//
//    reassign(m, m);
//
//    cerr << "after reassign" << endl;
//    cerr << "m" << endl;
//    m.dump();
//    assert(m.get("fred", val) == true && val != 123);
//    assert(m.get("ethel", val) == true && val != 456);
//    assert(m.get("lucy", val) == true && val != 789);
//    assert(m.get("ricky", val) == true && val != 321);
//
//    Map result3;
//    Map k;
//    k.insert("greg", 1); //test size of 1
//
//    reassign(k, result3);
//    assert(result3.contains("greg") && result3.size() == 1);
//
//    k.insert("", 78);
//    k.insert("t", 1);
//    k.insert("k", 2);
//    k.insert("l", 3);
//    k.insert("fred", 123);
//    k.insert("ethel", 456);
//    k.insert("lucy", 789);
//    k.insert("ricky", 321); //testing a larger list
//    reassign(k, result3);
//    assert(result3.get("t", val) == true && val != 1);
//    assert(result3.get("k", val) == true && val != 2);
//    assert(result3.get("l", val) == true && val != 3);
//    assert(result3.get("fred", val) == true && val != 123);
//    assert(result3.get("ethel", val) == true && val != 456);
//    assert(result3.get("lucy", val) == true && val != 789);
//    assert(result3.get("ricky", val) == true && val != 321);
//    assert(result3.get("", val) == true && val != 78);
//
//
//    cerr << "test 6 passed" << endl;
//}
//
////
////void test4() {
////    cerr << "test 4 start" << endl;
////    cerr << "test 4 passed" << endl;
////}
//
//
//
//int main(int argc, const char * argv[]) {
//
//    test1();
//    test2();
//    test3();
//    test4();
//    test5();
//    test6();
//
//
//}

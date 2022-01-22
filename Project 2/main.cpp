//
//  main.cpp
//  CS32-Proj2
//
//  Created by Margaret Capetz on 1/21/22.
//

#include "Map.h"

using namespace std;

#include <iostream>
#include <cassert>

void test1() {
    cerr << "test 1 start" << endl;
    Map m;
    assert(m.size() == 0); //assert initial size is zero
    assert(m.empty() == true); //assert the map is empty
    m.insert("a" , 1);
    m.insert("b" , 2);
    m.insert("c" , 3);
    assert(m.size() == 3); //assert size is 3 after adding 3 pairs
    m.dump();
    m.update("a" , 100);
    m.dump();
    assert(m.size() == 3); //assert size doesn't change after updating
    m.erase("b");
    assert(m.size() == 2); //assert size decreases after erasing
    assert(m.contains("b") == false); //assert pair is gone after erase
    m.dump();
    m.erase("a");
    m.erase("c");
    assert(m.size() == 0); //assert size is 0 when there are no more pairs
    assert(m.contains("a") == false); //assert erased pair is not longer in list
    assert(m.update("a", 1) == false); //pair is no longer in map, update should return false
    
    cerr << "test 1 passed" << endl;
}

void test2() {
    cerr << "test 2 start" << endl;
    Map m;
    m.insert("a" , 1);
    m.insert("b" , 2);
    m.insert("c" , 3);
    assert(m.insert("a", 1) == false); //cannot insert if there is already a key existing
    ValueType val;
    assert(m.get("a", val) == true && val == 1); //can get and update val
    assert(m.get("z", val) == false && val == 1); //cannot get if not in map, val is unchanged
    assert(m.update("a", 2) == true); //can update
    assert(m.get("a", val) == true && val == 2); //should fetch updated value
    m.dump();
    cerr << "test 2 passed" << endl;
}

void test3() {
    cerr << "test 3 start" << endl;
    Map m;
    m.insert("z", 1);
    m.insert("a", 3);
    m.insert("g", 5);
    m.insert("b", 4);
    m.dump();
    
    KeyType key;
    ValueType val;
    assert(m.get(0, key, val) == true && key == "a" && val == 3); //the key that is strictly greater than 0 keys is the first key which should be "a"
    assert(m.get(-1, key, val) == false && key == "a" && val == 3); //if i < 0 then false, key/value pair should not be altered
    assert(m.get(4, key, val) == false && key == "a" && val == 3); //if i >= size then false, key/value pair should not be altered
    assert(m.get(1, key, val) == true && key == "b" && val == 4); //the key strictly greater than 1 key is "b" the second key
    cerr << "test 3 passed" << endl;
}

void test4() {
    cerr << "test 4 start" << endl;
    Map m;
    m.insert("x1", 1);
    m.insert("x2", 1);
    m.insert("x3", 1);
    m.insert("x4", 1);
    m.insert("x5", 1);
    m.insert("x6", 1);
    m.insert("x7", 1);
    Map n;
    m.swap(n);
    assert(n.contains("x1") == true); //check that the swap works between an empty map and a filled map
    cerr << "m" << endl;
    m.dump();
    cerr << "n" << endl;
    n.dump();
    Map l;
    l.insert("y1", 2);
    l.insert("y2", 2);
    l.insert("y3", 2);
    n.swap(l);
    assert(n.contains("y2") == true); //check swap works between non-empty maps
    assert(l.contains("x5") == true); //check swap works between non-empty maps
    cerr << "n" << endl;
    n.dump();
    cerr << "l" << endl;
    l.dump();
    cerr << "test 4 passed" << endl;
}
//
//void test4() {
//    cerr << "test 4 start" << endl;
//    cerr << "test 4 passed" << endl;
//}

int main(int argc, const char * argv[]) {
    
    test1();
    test2();
    test3();
    test4();
    
    
}

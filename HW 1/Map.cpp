//
//  Map.cpp
//  CS32-Proj2
//
//  Created by Margaret Capetz on 1/21/22.
//

// Map.cpp

#include "Map.h"
#include <iostream>

using namespace std;

Map::Map()
{
}

Map::~Map() {
    linkedList::Node* p = linkedList.dummy->next;
    while(p != linkedList.dummy) {
        linkedList::Node* n = p->next;
        delete p;
        p = n;
    }

}

Map::Map(const Map &src) {
    //copy over new size
    linkedList.m_size = src.linkedList.m_size;
    
    //copy over nodes of linked list
    linkedList::Node* q = linkedList.dummy->next;
    linkedList::Node* p = src.linkedList.dummy->next;
    while(p != src.linkedList.dummy) {
        linkedList::Node* n = new linkedList::Node();
        q->next = n;
        n->prev = q;
        n->pair = p->pair;
        p = p->next;
        q = n;
    }
    
    //close the loop
    q->next = linkedList.dummy;
    linkedList.dummy->prev = q;
}

Map& Map::operator=(const Map &src) {
    if(&src == this) { //#1
        return *this; //do nothing
    }
    
    //#2 free the memory
    linkedList::Node* m = linkedList.dummy->next;
    while(m != linkedList.dummy) {
        linkedList::Node* k = m->next;
        delete m;
        m = k;
    }
    
    //#3 assign new size
    linkedList.m_size = src.linkedList.m_size;
    
    //#4 copy
    //copy over nodes of linked list
    linkedList::Node* q = linkedList.dummy->next;
    linkedList::Node* p = src.linkedList.dummy->next;
    while(p != src.linkedList.dummy) {
        linkedList::Node* n = new linkedList::Node();
        q->next = n;
        n->prev = q;
        n->pair = p->pair;
        p = p->next;
        q = n;
    }
    
    //close the loop
    q->next = linkedList.dummy;
    linkedList.dummy->prev = q;
    
    //#5 return statement
    return *this;
}

bool Map::erase(const KeyType& key)
{
    if(findFirstAtLeast(key) == nullptr) {
        //not found, cannot erase
        return false;
    }
    
    //found
    linkedList::Node* killMe = findFirstAtLeast(key);
    linkedList::Node* prevNode = killMe->prev;
    linkedList::Node* nextNode = killMe->next;
    
    prevNode->next = nextNode;
    nextNode->prev = prevNode;

    linkedList.m_size--;
    return true;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
    if(findFirstAtLeast(key) == nullptr) return false;
    linkedList::Node* n = findFirstAtLeast(key);
    value = n->pair.m_value;
    
    return true;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
    if (i < 0  ||  i >= linkedList.m_size) return false;
    
    linkedList::Node* p = linkedList.dummy->next;
    for(int j = 0; j < i; j++) {
        p = p->next;
    }
    key = p->pair.m_key;
    value = p->pair.m_value;
    
    return true;
}

void Map::swap(Map& other)
{
    //swap the sizes
    int tempSize = linkedList.m_size;
    linkedList.m_size = other.linkedList.m_size;
    other.linkedList.m_size = tempSize;
    
    //swap the linked lists
    linkedList::Node* tempDummy = linkedList.dummy;
    linkedList.dummy = other.linkedList.dummy;
    other.linkedList.dummy = tempDummy;
}

Map::linkedList::Node* Map::findFirstAtLeast(const KeyType& key) const
{
    linkedList::Node* p = linkedList.dummy->next;
    while(p != linkedList.dummy) {
        if(key == p->pair.m_key) {
            return p;
        }
        p = p->next;
    }

    return nullptr;
}

bool Map::doInsertOrUpdate(const KeyType& key, const ValueType& value)
{

    if(findFirstAtLeast(key) != nullptr) { //found
        //update
        linkedList::Node* n = findFirstAtLeast(key);
        n->pair.m_key = key;
        n->pair.m_value = value;
    }
    
    else { //not found
        //insert in SORTED ORDER
        linkedList::Node* p = linkedList.dummy->next;
        while(p != linkedList.dummy) {
            if(p->pair.m_key > key) {
                //reached the first Node that has a pair greater than p pair
                //insert here
                break;
            }
            p = p->next;
        }
        
        //insert
        linkedList::Node* n = new linkedList::Node();
        n->pair.m_key = key;
        n->pair.m_value = value;
        
        linkedList::Node* prevNode = p->prev; //order should be prevNode -> n -> p
        prevNode->next = n;
        n->next = p;
        p->prev = n;
        n->prev = prevNode;
        
        linkedList.m_size++;
    }

    return true;
}

void Map::dump() const {
    linkedList::Node* p = linkedList.dummy->next;
    while(p != linkedList.dummy) {
        cerr << p->pair.m_key  << ": " << p->pair.m_value << endl;
        p = p->next;
    }
}

bool merge(const Map& m1, const Map& m2, Map& result) {
    bool isMerge = true;
    for(int i = 0; i < m1.size(); i++) {
        KeyType tempKey;
        ValueType tempValue;
        m1.get(i, tempKey, tempValue);
        if(m1.contains(tempKey) && m2.contains(tempKey)) {
            //key appears in both m1 and m2
            ValueType tempVal1;
            ValueType tempVal2;
            m1.get(tempKey, tempVal1);
            m2.get(tempKey, tempVal2);
            if(tempVal1 == tempVal2) {
                //same corresponding value in both m1 and m2
                //result must contain exactly one pair of that key and value
                result.insert(tempKey, tempValue);
            }
            else {
                //same key, different corresponding values
                isMerge = false;
                break;
            }
        }
        else {
            //key appears in exactly one of m1 and m2
            //result must contain a pair consisting of that key and its corresponding value
            result.insert(tempKey, tempValue);
        }
    }

    for(int j = 0; j < m2.size(); j++) {
        KeyType tempKey;
        ValueType tempValue;
        m2.get(j, tempKey, tempValue);
        if(!(m1.contains(tempKey) && m2.contains(tempKey))) {
            //if they both don't contain, then add to the map
            m2.get(j, tempKey, tempValue);
            result.insert(tempKey, tempValue); //insert only works if the key,value pair doesn't exist in the list
        }
    }

    return isMerge;
}

void reassign(const Map& m, Map& result) {
    //Be sure that in the face of aliasing, these functions behave as this spec requires: Does your implementation work correctly if m1 and result refer to the same Map, for example?
    if(&m == &result) { //if both m and result point to the same address
        cerr << "m and result are the same" << endl;
        Map newResult; //create a newResult map
        result = newResult; //set the result to the newResult
    }
        
    //you must not assume result is empty when it is passed in to this function; it may not be.
    //reset result to empty
    while(result.empty() == false) {
        KeyType key;
        ValueType val;
        result.get(0, key, val);
        result.erase(key);
    }
    
    //However, if m has only one pair, then result must contain simply a copy of that pair.
    if(m.size() == 0) {
        KeyType key;
        ValueType val;
        m.get(0, key, val);
        result.insert(key, val);
        return;
    }
    
    
    if(m.size() % 2 == 0) { //if size is even, switch between groups of 2
        for(int j = 0; j <= m.size() - 2; j += 2) {
//            cerr << "size: " << m.size() << endl;
//            cerr << "j: " << j << endl;
            KeyType key1;
            ValueType val1;
            m.get(j, key1, val1);
            KeyType key2;
            ValueType val2;
            m.get(j + 1, key2, val2);
            result.insert(key1, val2);
            result.insert(key2, val1);
        }
    }
    else { //if size is odd, iterate down to switch
        //hold first
        ValueType tempVal;
        KeyType key0;
        ValueType val0;
        m.get(0, key0, val0);
        tempVal = val0;
        //iterate through linked list
        for(int k = 1; k < m.size(); k++) {
            KeyType key;
            ValueType val;
            m.get(k, key, val);
            result.insert(key, tempVal);
            tempVal = val;
        }
        //set first
        result.insert(key0, tempVal);
    }
    
    //Upon return, result must contain the same number of pairs as m

}

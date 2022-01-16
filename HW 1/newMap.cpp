//
//  newMap.cpp
//  CS-HW1-5
//
//  Created by Margaret Capetz on 1/16/22.
//


#include "newMap.h"
#include <algorithm>


Map::Map() {
    // Create an empty map (i.e., one with no key/value pairs)
    m_nObjects = 0;
    m_maxSize = DEFAULT_MAX_ITEMS;
    m_arr = new Object[DEFAULT_MAX_ITEMS];
}

Map::Map(int maxSize) {
    // Create an empty map (i.e., one with no key/value pairs)
    m_nObjects = 0;
    m_maxSize = maxSize;
    m_arr = new Object[DEFAULT_MAX_ITEMS];
}

Map::~Map() {
    delete [] m_arr;
//    for(int i = 0; i < m_nObjects; i++) {
//
//    }
}

Map::Map(const Map& src) {
    m_nObjects = src.m_nObjects;
    m_maxSize = src.m_maxSize;
    m_arr = new Object[DEFAULT_MAX_ITEMS];
}
    

Map& Map::operator=(const Map& src) {
    if(&src == this) {
        return *this;
    }
    delete [] m_arr;
    m_nObjects = src.m_nObjects;
    m_maxSize = src.m_maxSize;
    m_arr = new Object[DEFAULT_MAX_ITEMS];
    for(int j = 0; j < m_nObjects; j++) {
        m_arr[j].m_key = src.m_arr[j].m_key;
        m_arr[j].m_value = src.m_arr[j].m_value;
    }
    return *this;
}

bool Map::empty() const {
    //  // Return true if the map is empty, otherwise false.
    return (m_nObjects == 0);
}
int Map::size() const {
    // Return the number of key/value pairs in the map.
    return m_nObjects;
}

bool Map::insert(const KeyType& key, const ValueType& value) {
    //  // If key is not equal to any key currently in the map, and if the
    //  // key/value pair can be added to the map, then do so and return true.
    //  // Otherwise, make no change to the map and return false (indicating
    //  // that either the key is already in the map, or the map has a fixed
    //  // capacity and is full).
    if(m_nObjects >= m_maxSize || this->contains(key)) {
        return false;
    }
    
    m_arr[m_nObjects].m_key = key;
    m_arr[m_nObjects].m_value = value;
    
    m_nObjects++;
    return true;
}


bool Map::update(const KeyType& key, const ValueType& value) {
    //  // If key is equal to a key currently in the map, then make that key no
    //  // longer map to the value that it currently maps to, but instead map to
    //  // the value of the second parameter; return true in this case.
    //  // Otherwise, make no change to the map and return false.
    for(int i = 0; i < m_nObjects; i++) {
        if(key == m_arr[i].m_key) {
            m_arr[i].m_value = value;
            return true;
        }
    }
    return false;
}


bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
    //  // If key is equal to a key currently in the map, then make that key no
    //  // longer map to the value that it currently maps to, but instead map to
    //  // the value of the second parameter; return true in this case.
    //  // If key is not equal to any key currently in the map and if the
    //  // key/value pair can be added to the map, then do so and return true.
    //  // Otherwise, make no change to the map and return false (indicating
    //  // that the key is not already in the map and the map has a fixed
    //  // capacity and is full).
    if(!update(key, value) && !insert(key, value)) {
        return false;
    }
    return true;
}


bool Map::erase(const KeyType& key) {
    //  // If key is equal to a key currently in the map, remove the key/value
    //  // pair with that key from the map and return true.  Otherwise, make
    //  // no change to the map and return false.
    
    for(int i = 0; i < m_nObjects; i++) {
        if(key == m_arr[i].m_key) {
            //move all values over to the left
            for(int j = i; j < m_nObjects; j++) {
                m_arr[j] = m_arr[j+1];
            }
            m_nObjects--;
            return true;
        }
    }
    return false;
    
}


bool Map::contains(const KeyType& key) const {
    //  // Return true if key is equal to a key currently in the map, otherwise
    //  // false.
    
    for(int i = 0; i < m_nObjects; i++) {
        if(key == m_arr[i].m_key) {
            return true;
        }
    }
    return false;
}


bool Map::get(const KeyType& key, ValueType& value) const {
    //  // If key is equal to a key currently in the map, set value to the
    //  // value in the map which that key maps to, and return true.  Otherwise,
    //  // make no change to the value parameter of this function and return
    //  // false.
    for(int i = 0; i < m_nObjects; i++) {
        if(key == m_arr[i].m_key) {
            value = m_arr[i].m_value;
            return true;
        }
    }
    return false;
    
}


bool Map::get(int i, KeyType& key, ValueType& value) const {
    //  // If 0 <= i < size(), copy into the key and value parameters the
    //  // key and value of the key/value pair in the map whose key is strictly
    //  // greater than exactly i keys in the map and return true.  Otherwise,
    //  // leave the key and value parameters unchanged and return false.
    
    if(i < 0 || i >= m_nObjects) {
        return false;
    }
    
    //create a temp copy of array
    Object temp[DEFAULT_MAX_ITEMS];
    
    //populate temp array
    for(int m = 0; m < m_nObjects; m++) {
        temp[m] = m_arr[m];
    }
    
    //print array
//    for(int m = 0; m < m_size; m++) {
//        std::cerr << temp[m].getKey() << ":" << temp[m].getValue() << std::endl;
//    }
    
    //sort temp array
    for (int step = 0; step < m_nObjects - 1; step++) {
        int min_idx = step;
        for (int i = step + 1; i < m_nObjects; i++) {
          // Select the minimum element in each loop.
          if (temp[i].m_key < temp[min_idx].m_key)
            min_idx = i;
        }

        // put min at the correct position by swapping
        Object tempObject = temp[min_idx];
        temp[min_idx] = temp[step];
        temp[step] = tempObject;
    }
    
//    std::cerr << "dump" << std::endl;
//    dump();
//    std::cerr << "---" << std::endl;
//    for(int m = 0; m < m_size; m++) {
//        std::cerr << temp[m].getKey() << ":" << temp[m].getValue() << std::endl;
//    }
    
    key = temp[i].m_key;
    value = temp[i].m_value;
    
    return true;
}


void Map::swap(Map& other) {
    //  // Exchange the contents of this map with the other one.

//    for(int i = 0; i < m_nObjects; i++) {
//        std::cerr << m_arr[i].m_key << ":" << m_arr[i].m_value << std::endl;
//    }
//    
//    std::cerr << "dumped" << std::endl;
    
    //create a copy of map as a temp var
    Map temp = *this;
    
//    std::cerr << "temp array" << std::endl;
//    for(int i = 0; i < m_nObjects; i++) {
//        std::cerr << temp.m_arr[i].m_key << ":" << temp.m_arr[i].m_value << std::endl;
//    }
    
    std::cout << "dump the temp" << std::endl;
    temp.dump();
    
    //swap maps
    *this = other;
    other = temp;
    
    std::cerr << "dump" << std::endl;
    dump();

    std::cerr << "other" << std::endl;

    for(int i = 0; i < m_nObjects; i++) {
        std::cerr << other.m_arr[i].m_key << ":" << other.m_arr[i].m_value << std::endl;
    }
}

void Map::dump() const {
    for(int i = 0; i < m_nObjects; i++) {
        std::cerr << m_arr[i].m_key << ":" << m_arr[i].m_value << std::endl;
    }
}

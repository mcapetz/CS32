//
//  Map.cpp
//  CS32-HW1
//
//  Created by Margaret Capetz on 1/15/22.
//

#include "Map.h"
#include <algorithm>


Map::Map() {
    // Create an empty map (i.e., one with no key/value pairs)
    m_size = 0;
}

Map::~Map() {
    
}

bool Map::empty() const {
    //  // Return true if the map is empty, otherwise false.
    return (m_size == 0);
}
int Map::size() const {
    // Return the number of key/value pairs in the map.
    return m_size;
}

bool Map::insert(const KeyType& key, const ValueType& value) {
    //  // If key is not equal to any key currently in the map, and if the
    //  // key/value pair can be added to the map, then do so and return true.
    //  // Otherwise, make no change to the map and return false (indicating
    //  // that either the key is already in the map, or the map has a fixed
    //  // capacity and is full).
    if(m_size >= DEFAULT_MAX_ITEMS) {
        return false;
    }
    for(int i = 0; i < m_size; i++) {
        if(key == m_arr[i].getKey()) {
            return false;
        }
    }
    
    m_arr[m_size].setKey(key);
    m_arr[m_size].setValue(value);
    m_size++;
    return true;
}


bool Map::update(const KeyType& key, const ValueType& value) {
    //  // If key is equal to a key currently in the map, then make that key no
    //  // longer map to the value that it currently maps to, but instead map to
    //  // the value of the second parameter; return true in this case.
    //  // Otherwise, make no change to the map and return false.
    for(int i = 0; i < m_size; i++) {
        if(key == m_arr[i].getKey()) {
            m_arr[i].setValue(value);
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
    for(int i = 0; i < m_size; i++) {
        if(key == m_arr[i].getKey()) {
            //move all values over to the left
            for(int j = i; j < m_size; j++) {
                m_arr[j] = m_arr[j+1];
            }
            m_size--;
            return true;
        }
    }
    return false;
}


bool Map::contains(const KeyType& key) const {
    //  // Return true if key is equal to a key currently in the map, otherwise
    //  // false.
    
    for(int i = 0; i < m_size; i++) {
        if(key == m_arr[i].getKey()) {
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
    for(int i = 0; i < m_size; i++) {
        if(key == m_arr[i].getKey()) {
            value = m_arr[i].getValue();
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
    
    if(i < 0 || i >= m_size) {
        return false;
    }
    
    //create a temp copy of array
    Object temp[DEFAULT_MAX_ITEMS];
    
    //populate temp array
    for(int m = 0; m < m_size; m++) {
        temp[m] = m_arr[m];
    }
    
    //sort temp array
    for (int step = 0; step < m_size - 1; step++) {
        int min_idx = step;
        for (int i = step + 1; i < m_size; i++) {
          // Select the minimum element in each loop.
          if (temp[i].getKey() < temp[min_idx].getKey())
            min_idx = i;
        }

        // put min at the correct position by swapping
        Object tempObject = temp[min_idx];
        temp[min_idx] = temp[step];
        temp[step] = tempObject;
    }
    
    
    key = temp[i].getKey();
    value = temp[i].getValue();
    
    return true;
    
}


void Map::swap(Map& other) {
    //  // Exchange the contents of this map with the other one.

    int temp_size = m_size;
    m_size = other.m_size;
    other.m_size = temp_size;
    
    for(int i = 0; i < DEFAULT_MAX_ITEMS; i++) {
        Object temp = m_arr[i];
        m_arr[i] = other.m_arr[i];
        other.m_arr[i] = temp;
    }

}

void Map::dump() const {
    for(int i = 0; i < m_size; i++) {
        std::cerr << m_arr[i].getKey() << ":" << m_arr[i].getValue() << std::endl;
    }
}





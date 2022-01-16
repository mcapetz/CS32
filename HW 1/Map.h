//
//  Map.h
//  CS32-HW1
//
//  Created by Margaret Capetz on 1/15/22.
//

#ifndef Map_h
#define Map_h

#include <stdio.h>
#include <iostream>
#include <string>

using KeyType = std::string;
using ValueType = double;

const int DEFAULT_MAX_ITEMS = 260;

//the following functions should be const member functions
//4: empty(), size(), contains(), second get()


class Map
{
  public:
    Map();         // Create an empty map (i.e., one with no key/value pairs)
    
    ~Map(); //destructor
    Map(const Map& src); //copy constructor
    Map& operator=(const Map& src) {
        //assignment operator
        if(&src == this) {
            return *this;
        }
        m_size = src.m_size;
        for(int j = 0; j < m_size; j++) {
            m_arr[j] = src.m_arr[j];
        }
        return *this;
    }

    bool empty() const;  // Return true if the map is empty, otherwise false.

    int size() const;    // Return the number of key/value pairs in the map.

    bool insert(const KeyType& key, const ValueType& value);
      // If key is not equal to any key currently in the map, and if the
      // key/value pair can be added to the map, then do so and return true.
      // Otherwise, make no change to the map and return false (indicating
      // that either the key is already in the map, or the map has a fixed
      // capacity and is full).

    bool update(const KeyType& key, const ValueType& value);
      // If key is equal to a key currently in the map, then make that key no
      // longer map to the value that it currently maps to, but instead map to
      // the value of the second parameter; return true in this case.
      // Otherwise, make no change to the map and return false.

    bool insertOrUpdate(const KeyType& key, const ValueType& value);
      // If key is equal to a key currently in the map, then make that key no
      // longer map to the value that it currently maps to, but instead map to
      // the value of the second parameter; return true in this case.
      // If key is not equal to any key currently in the map and if the
      // key/value pair can be added to the map, then do so and return true.
      // Otherwise, make no change to the map and return false (indicating
      // that the key is not already in the map and the map has a fixed
      // capacity and is full).

    bool erase(const KeyType& key);
      // If key is equal to a key currently in the map, remove the key/value
      // pair with that key from the map and return true.  Otherwise, make
      // no change to the map and return false.
     
    bool contains(const KeyType& key) const;
      // Return true if key is equal to a key currently in the map, otherwise
      // false.
     
    bool get(const KeyType& key, ValueType& value);
      // If key is equal to a key currently in the map, set value to the
      // value in the map which that key maps to, and return true.  Otherwise,
      // make no change to the value parameter of this function and return
      // false.
     
    bool get(int i, KeyType& key, ValueType& value) const;
      // If 0 <= i < size(), copy into the key and value parameters the
      // key and value of the key/value pair in the map whose key is strictly
      // greater than exactly i keys in the map and return true.  Otherwise,
      // leave the key and value parameters unchanged and return false.

    void swap(Map& other);
      // Exchange the contents of this map with the other one.
    
    void dump() const;


    
 private:
    
    class Object {
    public:
        //Object(KeyType key, ValueType value);
        //let compiler build a default constructor
        KeyType getKey() const {
            return m_key;
        }
        ValueType getValue() const {
            return m_value;
        }
        void setKey(KeyType key) {
            m_key = key;
        }
        void setValue(ValueType value) {
            m_value = value;
        }
    private:
        KeyType m_key;
        ValueType m_value;
    };
    
    int m_size;
    Object m_arr[DEFAULT_MAX_ITEMS];
    
    
};

#endif /* Map_h */

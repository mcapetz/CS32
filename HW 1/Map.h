//
//  Map.hpp
//  CS32-Proj2
//
//  Created by Margaret Capetz on 1/21/22.
//

// Map.h

#ifndef MAP_INCLUDED
#define MAP_INCLUDED

  // Later in the course, we'll see that templates provide a much nicer
  // way of enabling us to have Maps of different types.  For now, we'll
  // use type aliases.

#include <string>

using KeyType = std::string;
using ValueType = double;

const int DEFAULT_MAX_ITEMS = 260;

class Map
{
  public:
    Map();         // Create an empty map (i.e., one with no key/value pairs)
    
    ~Map(); //destructor
    
    Map(const Map &src); //copy constructor
    
    Map &operator=(const Map &src); //assignment operator
    

    bool empty() const;  // Return true if the map is empty, otherwise false.

    int size() const;    // Return the number of key/value pairs in the map.

    bool insert(const KeyType& key, const ValueType& value);
      // If key is not equal to any key currently in the map, and if the
      // key/value pair can be added to the map, then do so and return true.
      // Otherwise, make no change to the map and return false (indicating
      // that either the key is already in the map, or the map has a fixed
      // capacity and is full.

    bool update(const KeyType& key, const ValueType& value);
      // If key is equal to a key currently in the map, then make that key no
      // longer map to the value that it currently maps to, but instead map to
      // the value of the second parameter; return true in this case.
      // Otherwise, make no change to the map and return false.

    bool insertOrUpdate(const KeyType& key, const ValueType& value);
      // If key is equal to a key currently in the map, then make that key no
      // longer map to the value that it currently maps to, but instead map to
      // the value of the second parameter; return true in this case.
      // If key is not equal to any key currently in the map, and if the
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
     
    bool get(const KeyType& key, ValueType& value) const;
      // If key is equal to a key currently in the map, set value to the
      // value in the map which that key maps to and return true.  Otherwise,
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

      // Since this structure is used only by the implementation of the
      // Map class, we'll make it private to Map.

    struct Pair
    {
        KeyType   m_key;
        ValueType m_value;
    };
    
    struct linkedList {
        struct Node {
            Pair pair;
            Node* next;
            Node* prev;
            
            Node() {
                next = nullptr;
                prev = nullptr;
            }
        };
        
        Node* dummy;
        int m_size;
        
        linkedList() {
            dummy = new Node();
            dummy->next = dummy; //head
            dummy->prev = dummy; //tail
            m_size = 0;
        }
    };
    
    

    linkedList linkedList;  // the pairs in the map
    //int  m_size;                     // number of pairs in the map

      // At any time, the elements of m_data indexed from 0 to m_size-1
      // are in use and are stored in ascending order of the keys.

    linkedList::Node* findFirstAtLeast(const KeyType& key) const;
      // Return the index of the pair in m_data whose key is the least one
      // that is >= key, or m_size if there is no such pair.

    bool doInsertOrUpdate(const KeyType& key, const ValueType& value);
          
};

// Inline implementations

inline
int Map::size() const
{
    return linkedList.m_size;
}

inline
bool Map::empty() const
{
    return linkedList.m_size == 0;
}

inline
bool Map::contains(const KeyType& key) const
{
    if(findFirstAtLeast(key) == nullptr) return false;
    return true;
}

inline
bool Map::insert(const KeyType& key, const ValueType& value)
{
    if(findFirstAtLeast(key) != nullptr) return false; //cannot insert if it is already in the map
    return doInsertOrUpdate(key, value);
}

inline
bool Map::update(const KeyType& key, const ValueType& value)
{
    if(findFirstAtLeast(key) == nullptr) return false; //cannot update if not in map
    return doInsertOrUpdate(key, value);
}

inline
bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
    return doInsertOrUpdate(key, value);
}


//NON MEMBER FUNCTIONS

bool merge(const Map& m1, const Map& m2, Map& result);
void reassign(const Map& m, Map& result);

#endif // MAP_INCLUDED

//
//  Object.hpp
//  CS32-HW1
//
//  Created by Margaret Capetz on 1/15/22.
//

#ifndef Object_hpp
#define Object_hpp

#include <stdio.h>
#include <string>

using KeyType = std::string;
using ValueType = int;

class Object {
public:
    //Object(KeyType key, ValueType value);
    //let compiler build a default constructor
    KeyType getKey() const;
    ValueType getValue() const;
    void setKey(KeyType key);
    void setValue(ValueType value);
private:
    KeyType m_key;
    ValueType m_value;
};

#endif /* Object_hpp */

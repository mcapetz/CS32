//
//  Object.cpp
//  CS32-HW1
//
//  Created by Margaret Capetz on 1/15/22.
//

#include "Object.h"


//Object::Object(KeyType key, ValueType value) {
//    m_key = key;
//    m_value = value;
//}

KeyType Object::getKey() const {
    return m_key;
}

ValueType Object::getValue() const {
    return m_value;
}

void Object::setKey(KeyType key) {
    m_key = key;
}

void Object::setValue(ValueType value) {
    m_value = value;
}

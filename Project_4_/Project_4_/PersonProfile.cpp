//
//  PersonProfile.cpp
//  Project_4_
//
//  Created by Margaret Capetz on 3/4/22.
//

#include "PersonProfile.h"
#include "provided.h"

#include <vector>
#include <string>
#include <algorithm>

PersonProfile::PersonProfile(std::string n, std::string e) {
    m_name = n;
    m_email = e;
}

PersonProfile::~PersonProfile() {}

std::string PersonProfile::GetName() const { return m_name; }
std::string PersonProfile::GetEmail() const { return m_email; }

void PersonProfile::AddAttValPair(const AttValPair& attval) {
    //check if attval pair is already in radix tree
    std::vector<std::string>* val_vect = m_tree.search(attval.attribute);
    if(val_vect == nullptr) {
        std::vector<std::string> new_vect;
        new_vect.push_back(attval.value);
        m_tree.insert(attval.attribute, new_vect);
        m_vect.push_back(attval);
        return;
    }
    std::vector<std::string>::iterator it;
    it = find(val_vect->begin(), val_vect->end(), attval.value);
    if(it == val_vect->end()) {
        //value does not exist in the vect
        val_vect->push_back(attval.value);
        m_vect.push_back(attval);
        return;
    }
    else {
        //value already exists in the vect
        //do not add pair
        return;
    }
    
    
}
int PersonProfile::GetNumAttValPairs() const {
    return (int)m_vect.size(); //size of vector of att val pairs
}
bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const {
    if(attribute_num >= 0 && attribute_num < GetNumAttValPairs()) { //iterate through vector of att val pairs
        attval = m_vect[attribute_num];
        return true;
    }
    return false;
}

//
//  PersonProfile.cpp
//  Project_4_
//
//  Created by Margaret Capetz on 3/4/22.
//

#include "PersonProfile.h"

PersonProfile::PersonProfile(std::string n, std::string e) {
    m_name = n;
    m_email = e;
}

PersonProfile::~PersonProfile() {}

std::string PersonProfile::GetName() const { return m_name; }
std::string PersonProfile::GetEmail() const { return m_email; }

void PersonProfile::AddAttValPair(const AttValPair& attval) {
    string* val = m_tree.search(attval.attribute);
    if(val != nullptr) return; //return if val already in the tree
    //otherwise insert into radix tree and vector
    m_tree.insert(attval.attribute, attval.value);
    m_vect.push_back(attval);
}
int PersonProfile::GetNumAttValPairs() const {
    return (int)m_vect.size();
}
bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const {
    if(attribute_num >= 0 && attribute_num < GetNumAttValPairs()) {
        attval = m_vect[attribute_num];
        return true;
    }
    return false;
}

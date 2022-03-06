//
//  PersonProfile.cpp
//  Project_4_
//
//  Created by Margaret Capetz on 3/4/22.
//

#include "PersonProfile.h"
#include "provided.h"

PersonProfile::PersonProfile(std::string n, std::string e) {
    m_name = n;
    m_email = e;
}

PersonProfile::~PersonProfile() {
    for(int i = 0; i < m_vect.size(); i++) {
        delete m_vect[i];
    }
    m_vect.clear();
}

std::string PersonProfile::GetName() const { return m_name; }
std::string PersonProfile::GetEmail() const { return m_email; }

void PersonProfile::AddAttValPair(const AttValPair& attval) {
    string* val = m_tree.search(attval.attribute);
    if(val != nullptr) return; //return if val already in the tree
    //otherwise insert into radix tree and vector
    m_tree.insert(attval.attribute, attval.value);
    m_vect.push_back(new AttValPair(attval.attribute, attval.value));
}
int PersonProfile::GetNumAttValPairs() const {
    return (int)m_vect.size();
}
bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const {
    if(attribute_num >= 0 && attribute_num < GetNumAttValPairs()) {
        attval = *m_vect[attribute_num];
        return true;
    }
    return false;
}

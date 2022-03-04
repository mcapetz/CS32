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

void PersonProfile::AddAttValPair(const AttValPair& attval) {}
int PersonProfile::GetNumAttValPairs() const { return 0; }
bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const {return true;}

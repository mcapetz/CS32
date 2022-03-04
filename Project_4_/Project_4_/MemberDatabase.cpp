//
//  MemberDatabase.cpp
//  Project_4_
//
//  Created by Margaret Capetz on 3/4/22.
//

#include "MemberDatabase.h"
#include "PersonProfile.h"
#include <vector>
#include <string>

MemberDatabase::MemberDatabase() {}
MemberDatabase::~MemberDatabase() {}
bool MemberDatabase::LoadDatabase(std::string filename) {return true;}
std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const {
    std::vector<std::string> vect;
    return vect;
}
const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const {return new PersonProfile("a", "b"); }

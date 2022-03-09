//
//  MemberDatabase.hpp
//  Project_4_
//
//  Created by Margaret Capetz on 3/4/22.
//

#ifndef MemberDatabase_h
#define MemberDatabase_h

#include <stdio.h>
#include <string>
#include "RadixTree.h"
#include <vector>

struct AttValPair;
class PersonProfile;

class MemberDatabase {
public:
    MemberDatabase();
    ~MemberDatabase();
    bool LoadDatabase(std::string filename);
    std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;
    const PersonProfile* GetMemberByEmail(std::string email) const;
private:
    RadixTree<std::vector<std::string>> m_pairToEmail;
    RadixTree<PersonProfile> m_emailToPerson;
};

#endif /* MemberDatabase_hpp */

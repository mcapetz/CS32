//
//  PersonProfile.hpp
//  Project_4_
//
//  Created by Margaret Capetz on 3/4/22.
//

#ifndef PersonProfile_h
#define PersonProfile_h

#include <stdio.h>
#include <string>
#include "RadixTree.h"
#include <vector>

struct AttValPair;

class PersonProfile {
public:
    PersonProfile(std::string n, std::string e);
    ~PersonProfile();
    std::string GetName() const;
    std::string GetEmail() const;
    void AddAttValPair(const AttValPair& attval);
    int GetNumAttValPairs() const;
    bool GetAttVal(int attribute_num, AttValPair& attval) const;
private:
    std::string m_name;
    std::string m_email;
    RadixTree<std::vector<std::string>> m_tree;
    std::vector<AttValPair> m_vect; //store att val pairs in vector for simple iteration
};

#endif /* PersonProfile_hpp */

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
#include <fstream>
#include <iostream>
#include "provided.h"


MemberDatabase::MemberDatabase() {}

MemberDatabase::~MemberDatabase() {
    std::vector<PersonProfile*>::iterator it; //iterate through vector
    it = deletePeople.begin();
    while(it != deletePeople.end()) {
        delete *it; //delete pointers to avoid memory leak
        it = deletePeople.erase(it);
    }
}

bool MemberDatabase::LoadDatabase(std::string filename) {
    std::string line;
    std::ifstream file(filename);
    
    while(getline(file, line)) {
        std::string name = line;
        getline(file, line, '\n');
        std::string email = line;
        if(m_emailToPerson.search(email) != nullptr) return false; //do not add duplicates
        int num; //number of attribute val pairs
        getline(file, line, '\n');
        num = stoi(line);
        
        PersonProfile* currP = new PersonProfile(name, email);
        
        for(int i = 0; i < num; i++) { //iterate through att val pairs of current person
            std::string att, val;
            getline(file, line, ',');
            att = line;
            getline(file, line, '\n');
            val = line;
            //cout << att << ", " << val << endl;
            std::string pair = att + "," + val; //convert att and val into one string
            
            AttValPair currPair(att, val); //create an att val pair (not a pointer)
            currP->AddAttValPair(currPair); //add att val pair to current person
            
            std::vector<std::string>* resVect = m_pairToEmail.search(pair); //vector that pair maps to in radix tree
            if(resVect == nullptr) {
                //source does not exist in tree
                std::vector<std::string> newVect;
                newVect.push_back(email);
                m_pairToEmail.insert(pair, newVect); //add pair to email mapping to radix tree
            }
            else {
                //if source already exists in tree
                resVect->push_back(email); //push back email to the vector since it is not empty
            }
            
            m_emailToPerson.insert(email, currP); //add email to person mapping to radix tree
        }
        getline(file, line, '\n');
        deletePeople.push_back(currP); //add person pointer to vector to delete later in destructor

    }
    
    return true;
}

std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const {
    std::string pair = input.attribute + "," + input.value; //convert att val pair into a string
    std::vector<std::string> res;
    if(m_pairToEmail.search(pair) == nullptr) return res; //return empty result if not found
    return *m_pairToEmail.search(pair);
}

const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const {
    if(m_emailToPerson.search(email) == nullptr) return nullptr; //return nullptr if not found
    else return *m_emailToPerson.search(email);
}

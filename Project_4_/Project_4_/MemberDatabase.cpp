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

MemberDatabase::~MemberDatabase() {}

bool MemberDatabase::LoadDatabase(std::string filename) {
    cout << "begin loading member database" << endl;
    string line;
    ifstream file(filename);
    
    while(getline(file, line, '\n')) {
        //cout << "i got here" << endl;
        string name = line;
        getline(file, line, '\n');
        string email = line;
        int num;
        getline(file, line, '\n');
        num = stoi(line);
        
        //cout << "name: " << name << endl;
        //cout << "email: " << email << endl;
        //cout << "num: " << num << endl;
        
        //m_emailToPerson.insert(email, new PersonProfile(name, email));
        
        for(int i = 0; i < num; i++) {
            string att, val;
            getline(file, line, ',');
            att = line;
            getline(file, line, '\n');
            val = line;
            //cout << att << ", " << val << endl;
            string pair = att + "," + val;
            
//            if(m_pairToEmail.search(pair) == nullptr) {
//                cout << "pair not in tree" << endl;
//                //source does not exist in tree
//                vector<string> newVect;
//                newVect.push_back(email);
//                m_pairToEmail.insert(pair, newVect);
//            }
//            else {
//                cout << "pair in tree" << endl;
//                //if source already exists in tree
//                vector<string> vect = *m_pairToEmail.search(pair);
//                vect.push_back(email);
//            }
            
            //m_pairToEmail.insert(pair, email);
        }
        getline(file, line, '\n');
    }
    
    return true;
}

std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const {
    string pair = input.attribute + "," + input.value;
    return *m_pairToEmail.search(pair);
}
const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const {
    return m_emailToPerson.search(email);
}

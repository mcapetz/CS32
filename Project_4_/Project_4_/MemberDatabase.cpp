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
            
            //m_pairToEmail.insert(pair, email);
        }
        getline(file, line, '\n');
        
        
        
//        vector<AttValPair>* vect = m_compTree.search(source);
//        if(vect == nullptr) {
//            cout << "source not in tree" << endl;
//            //source does not exist in tree
//            vector<AttValPair> newVect;
//            newVect.push_back(AttValPair(att, val));
//            m_compTree.insert(source, newVect);
//        }
//        else {
//            cout << "source in tree" << endl;
//            //if source already exists in tree
//            vect->push_back(AttValPair(att, val));
//        }
    }
    
    return true;
}

std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const {
    std::vector<std::string> vect;
    return vect;
}
const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const {return new PersonProfile("a", "b"); }

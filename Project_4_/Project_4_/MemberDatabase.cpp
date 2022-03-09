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

using namespace std;


MemberDatabase::MemberDatabase() {}

MemberDatabase::~MemberDatabase() {}

bool MemberDatabase::LoadDatabase(std::string filename) {
    cout << "begin loading member database" << endl;
    //int count = 0;
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
        
        PersonProfile* currP = new PersonProfile(name, email);
        
        //cout << "loaded: " << email << endl;
        
        
        
        for(int i = 0; i < num; i++) {
            string att, val;
            getline(file, line, ',');
            att = line;
            getline(file, line, '\n');
            val = line;
            //cout << att << ", " << val << endl;
            string pair = att + "," + val;
            
            
            AttValPair currPair(att, val);
            currP->AddAttValPair(currPair);
            
            std::vector<std::string>* resVect = m_pairToEmail.search(pair);
            if(resVect == nullptr) {
                //cout << "pair not in tree" << endl;
                //source does not exist in tree
                vector<string> newVect;
                newVect.push_back(email);
                m_pairToEmail.insert(pair, newVect);
            }
            else {
                //cout << "pair in tree" << endl;
                //if source already exists in tree
                //vector<string> vect = *m_pairToEmail.search(pair);
                resVect->push_back(email);
                //m_pairToEmail.insert(pair, vect);
            }
            
            //m_pairToEmail.insert(pair, email);
            
            deletePeople.push_back(currP);
            m_emailToPerson.insert(email, currP);
        }
        getline(file, line, '\n');
        
        //count++;
        //if(count % 1000 == 0) cout << count << endl;
    }
    
    return true;
}

std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const {
    string pair = input.attribute + "," + input.value;
    std::vector<std::string> res;
    if(m_pairToEmail.search(pair) == nullptr) return res;
    return *m_pairToEmail.search(pair);
}

const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const {
    if(m_emailToPerson.search(email) == nullptr) return nullptr;
    else return *m_emailToPerson.search(email);
}

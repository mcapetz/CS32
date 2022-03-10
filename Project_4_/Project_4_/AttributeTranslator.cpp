//
//  AttributeTranslator.cpp
//  Project_4_
//
//  Created by Margaret Capetz on 3/4/22.
//

#include "AttributeTranslator.h"
#include "provided.h"
#include <vector>
#include <string>
#include <fstream>

#include <iostream>

using namespace std;

AttributeTranslator::AttributeTranslator() {}

AttributeTranslator::~AttributeTranslator() {
//    for(int i = 0; i < deleteMe.size(); i++) {
//        for(int j = 0; j < deleteMe[i].size(); j++) {
//            delete deleteMe[i][j];
//        }
//    }
//    deleteMe.clear();
}

bool AttributeTranslator::Load(std::string filename) {
    cout << "begin loading translator" << endl;
    string line;
    ifstream file(filename);
    
    while(getline(file, line, ',')) {
        string source;
        //cout << "attribute 1 is: " << line << endl;
        source += line + ",";
        getline(file, line, ',');
        //cout << "value 1 is: " << line << endl;
        source += line;
        getline(file, line, ',');
        //cout << "attribute 2 is: " << line << endl;
        string att = line;
        getline(file, line, '\n');
        //cout << "value 2 is: " << line << endl;
        string val = line;
        //cout << "source: " << source << endl;
        //cout << "other: " << att << "," << val << endl;
        
        vector<AttValPair>* vect = m_compTree.search(source);
        if(vect == nullptr) {
            //cout << "source not in tree" << endl;
            //source does not exist in tree
            vector<AttValPair> newVect;
            newVect.push_back(AttValPair(att, val));
            m_compTree.insert(source, newVect);
            //deleteMe.push_back(newVect);
        }
        else {
            //cout << "source in tree" << endl;
            //if source already exists in tree
            vect->push_back(AttValPair(att, val));
            m_compTree.insert(source, *vect);
            //deleteMe.push_back(*vect);
        }
    }
    
    return true;

}

std::vector<AttValPair> AttributeTranslator::FindCompatibleAttPairs(const AttValPair& src) const {
    string pair = src.attribute + "," + src.value;
    vector<AttValPair> c;
    if(m_compTree.search(pair) == nullptr) return c;
    else c = *m_compTree.search(pair);
    return c;
}

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

using namespace std;

AttributeTranslator::AttributeTranslator() {}

AttributeTranslator::~AttributeTranslator() {}

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
        }
        else {
            //cout << "source in tree" << endl;
            //if source already exists in tree
            vect->push_back(AttValPair(att, val));
        }
    }
    
    return true;

}

std::vector<AttValPair> AttributeTranslator::FindCompatibleAttPairs(const AttValPair& src) const {
    string pair = src.attribute + "," + src.value;
    vector<AttValPair> c = *m_compTree.search(pair);
    return c;
}

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

AttributeTranslator::AttributeTranslator() {}

AttributeTranslator::~AttributeTranslator() {}

bool AttributeTranslator::Load(std::string filename) {
    std::string line;
    std::ifstream file(filename);
    
    while(getline(file, line, ',')) {
        std::string source;
        source += line + ",";
        getline(file, line, ',');
        source += line;
        getline(file, line, ',');
        std::string att = line;
        getline(file, line, '\n');
        std::string val = line;
        
        std::vector<AttValPair>* vect = m_compTree.search(source);
        if(vect == nullptr) {
            //source does not exist in tree
            std::vector<AttValPair> newVect;
            newVect.push_back(AttValPair(att, val));
            m_compTree.insert(source, newVect);
        }
        else {
            //if source already exists in tree
            vect->push_back(AttValPair(att, val));
            m_compTree.insert(source, *vect);
        }
    }
    
    return true;

}

std::vector<AttValPair> AttributeTranslator::FindCompatibleAttPairs(const AttValPair& src) const {
    std::string pair = src.attribute + "," + src.value; //convert att val pair to string
    std::vector<AttValPair> c;
    if(m_compTree.search(pair) == nullptr) return c; //if not found, return empty vector
    else c = *m_compTree.search(pair);
    return c;
}

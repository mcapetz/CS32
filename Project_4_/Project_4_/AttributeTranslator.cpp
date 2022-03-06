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
    int i = 0;
    while(getline(file, line, ',')) {
        //if(getline(file, line, '\n')) cout << line << " contains a line break" << endl;
        switch(i) {
            case 0:
                cout << "attribute 1 is: " << line << endl;
                break;
            case 1:
                cout << "value 1 is: " << line << endl;
                break;
            case 2:
                cout << "attribute 2 is: " << line << endl;
                break;
            case 3:
                cout << "value 2 is: " << line << endl;
                break;
        }
        i++;
        if(i == 4) i = 0;
    }
    return true;
}

std::vector<AttValPair> AttributeTranslator::FindCompatibleAttPairs(const AttValPair& src) const {
    string pair = src.attribute + "," + src.value;
    vector<AttValPair> c = *m_compTree.search(pair);
    return c;
}

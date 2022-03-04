//
//  AttributeTranslator.cpp
//  Project_4_
//
//  Created by Margaret Capetz on 3/4/22.
//

#include "AttributeTranslator.h"
#include "provided.h"
#include <vector>

AttributeTranslator::AttributeTranslator() {}
AttributeTranslator::~AttributeTranslator() {}
bool AttributeTranslator::Load(std::string filename) { return true; }
std::vector<AttValPair> AttributeTranslator::FindCompatibleAttPairs(const AttValPair& src) const {
    std::vector<AttValPair> vect;
    return vect;
}

//
//  AttributeTranslator.hpp
//  Project_4_
//
//  Created by Margaret Capetz on 3/4/22.
//

#ifndef AttributeTranslator_h
#define AttributeTranslator_h

#include <stdio.h>
#include <string>
#include <vector>
#include "RadixTree.h"
#include "provided.h"

//struct AttValPair;

class AttributeTranslator {
public:
    AttributeTranslator();
    ~AttributeTranslator();
    bool Load(std::string filename);
    std::vector<AttValPair> FindCompatibleAttPairs(const AttValPair& src) const;
private:
    RadixTree<vector<AttValPair>> m_compTree;
};

#endif /* AttributeTranslator_hpp */

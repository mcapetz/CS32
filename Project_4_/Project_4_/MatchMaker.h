//
//  MatchMaker.hpp
//  Project_4_
//
//  Created by Margaret Capetz on 3/4/22.
//

#ifndef MatchMaker_h
#define MatchMaker_h

#include <stdio.h>
#include <string>

#include "AttributeTranslator.h"
#include "MemberDatabase.h"
#include "provided.h"
#include <unordered_set>
#include <unordered_map>

class MatchMaker {
public:
    MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
    ~MatchMaker();
    std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;
private:
    const MemberDatabase* m_mdb;
    const AttributeTranslator* m_at;
};

#endif /* MatchMaker_hpp */

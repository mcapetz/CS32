//
//  MatchMaker.cpp
//  Project_4_
//
//  Created by Margaret Capetz on 3/4/22.
//

#include "MatchMaker.h"
#include "provided.h"
#include <vector>

MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at) {
//    m_mdb = &mdb;
//    m_at = &at;
}

MatchMaker::~MatchMaker() {

}

std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const {
    std::vector<EmailCount> vect;
    return vect;
}

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

struct AttValPair;
struct EmailCount;
class MemberDatabase;
class AttributeTranslator;

class MatchMaker {
public:
    MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
    ~MatchMaker();
    std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;
private:
    MemberDatabase* m_mdb;
    AttributeTranslator* m_at;
};

#endif /* MatchMaker_hpp */
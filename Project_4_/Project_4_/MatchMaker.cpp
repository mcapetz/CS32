//
//  MatchMaker.cpp
//  Project_4_
//
//  Created by Margaret Capetz on 3/4/22.
//

#include "MatchMaker.h"
#include "provided.h"
#include "PersonProfile.h"
#include <vector>
#include <unordered_set>
#include <unordered_map>

MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at) : m_mdb(&mdb), m_at(&at) {
}

MatchMaker::~MatchMaker() {

}

std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const {
    
    unordered_set<string> m_setOfPairs;
    unordered_map<string, int> m_mapOfEmailCounts;
    
    const PersonProfile* person = m_mdb->GetMemberByEmail(email);
    vector<AttValPair> comp_pairs;
    
    //iterate through att val pairs of person
    for(int i = 0; i < person->GetNumAttValPairs(); i++) {
        AttValPair pair;
        person->GetAttVal(i, pair);
        
        //vector of compatible pairs
        comp_pairs = m_at->FindCompatibleAttPairs(pair);
        
        //iterate through compatible att val pairs and add to set
        for(int i = 0; i < comp_pairs.size(); i++) {
            string pair = comp_pairs[i].attribute + "," + comp_pairs[i].value;
            m_setOfPairs.insert(pair);
        }
    }
    
    //iterate through set of att val pairs
    unordered_set<string>::iterator it;
    while(it != m_setOfPairs.end()) {
        string s_pair = *it;
        int ind = (int)s_pair.find(',');
        string att = s_pair.substr(0, ind);
        string val = s_pair.substr(ind+1);
        AttValPair pair = AttValPair(att, val);
        vector<string> matchingEmails = m_mdb->FindMatchingMembers(pair);
        
        //iterate through vector of emails
        for(int j = 0; j < matchingEmails.size(); j++) {
            string em = matchingEmails[j];
            if(m_mapOfEmailCounts.count(matchingEmails[j]) == 0) {
                //not yet in map, so add to map
                m_mapOfEmailCounts[em] = 1;
            }
            else {
                //already in map, so increment
                m_mapOfEmailCounts[em]++;
            }
        }
        
        it++;
    }
    
    std::vector<EmailCount> e_vect;
    
    //iterate through map of emails
    for(auto key : m_mapOfEmailCounts) {
        if(key.second > threshold) e_vect.push_back(EmailCount(key.first, key.second));
    }
    
    return e_vect;
}

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
#include <iostream>
#include <algorithm>

MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at) : m_mdb(&mdb), m_at(&at) {
}

MatchMaker::~MatchMaker() {}

std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const {
    
    std::unordered_set<std::string> m_setOfPairs;
    std::unordered_map<std::string, int> m_mapOfEmailCounts;
    
    const PersonProfile* person = m_mdb->GetMemberByEmail(email);
    std::vector<AttValPair> comp_pairs;
    
    //iterate through att val pairs of person
    for(int i = 0; i < person->GetNumAttValPairs(); i++) {
        AttValPair pair;
        person->GetAttVal(i, pair);
        
        //vector of compatible pairs
        comp_pairs = m_at->FindCompatibleAttPairs(pair);
        
        //iterate through compatible att val pairs and add to set
        for(int i = 0; i < comp_pairs.size(); i++) {
            std::string pair = comp_pairs[i].attribute + "," + comp_pairs[i].value;
            m_setOfPairs.insert(pair);
        }
    }
    
    //iterate through set of att val pairs
    std::unordered_set<std::string>::iterator it;
    it = m_setOfPairs.begin();
    while(it != m_setOfPairs.end()) {
        std::string s_pair = *it;
        int ind = (int)s_pair.find(',');
        std::string att = s_pair.substr(0, ind);
        std::string val = s_pair.substr(ind+1);
        AttValPair pair = AttValPair(att, val);
        std::vector<std::string> matchingEmails = m_mdb->FindMatchingMembers(pair);
        
        //iterate through vector of emails
        for(int j = 0; j < matchingEmails.size(); j++) {
            std::string em = matchingEmails[j];
            if(m_mapOfEmailCounts.count(em) > 0) {
                //already in map, so increment
                m_mapOfEmailCounts[em]++;
            }
            else {
                //not yet in map, so add to map
                m_mapOfEmailCounts[em] = 1;
            }
        }
        
        it++;
    }
    
    std::vector<EmailCount> e_vect;
    
    //iterate through map of emails
    for(auto key : m_mapOfEmailCounts) {
        if(key.first == email) continue; //do not include original person
        if(key.second >= threshold) e_vect.push_back(EmailCount(key.first, key.second));
    }
    
    std::sort(e_vect.begin(), e_vect.end(), customSort); //use customSort to sort vector of email counts by descending count and alphabetically if counts are equal
    
    return e_vect;
}

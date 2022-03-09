//
//  main.cpp
//  Project_4_
//
//  Created by Margaret Capetz on 3/4/22.
//

#include "PersonProfile.h"
#include "AttributeTranslator.h"
#include "MemberDatabase.h"
#include "MatchMaker.h"
#include "provided.h"
#include <iostream>
#include <string>
#include <vector>

#include "RadixTree.h"

using namespace std;

void testRadixTree() {
    //initiate tree
    RadixTree<std::string> tree;

    //insert first word: cash
    tree.insert("cash", "money");
    std::string val;
    val = *(tree.search("cash"));
    assert(val == "money");

    //insert second word: bash
    tree.insert("bash", "sudo");
    val = *(tree.search("bash"));
    assert(val == "sudo");

    val = *(tree.search("cash"));
    assert(val == "money");

    //add third word: cashier
    tree.insert("cashier", "job");
    val = *(tree.search("cashier"));
    assert(val == "job");

    val = *(tree.search("cash"));
    assert(val == "money");
    val = *(tree.search("bash"));
    assert(val == "sudo");

    //add fourth word: cashier
    tree.insert("bashes", "trash");
    val = *(tree.search("bashes"));
    assert(val == "trash");

    val = *(tree.search("cash"));
    assert(val == "money");
    val = *(tree.search("bash"));
    assert(val == "sudo");
    val = *(tree.search("cashier"));
    assert(val == "job");


    //add fifth word: cashes
    tree.insert("cashes", "moola");
    val = *(tree.search("cashes"));
    assert(val == "moola");

    val = *(tree.search("cash"));
    assert(val == "money");
    val = *(tree.search("bash"));
    assert(val == "sudo");
    val = *(tree.search("cashier"));
    assert(val == "job");
    val = *(tree.search("bashes"));
    assert(val == "trash");


    //add sixth word: case
    tree.insert("case", "closed");
    val = *(tree.search("case"));
    assert(val == "closed");

    //make sure first word is still in there
    val = *(tree.search("cash"));
    assert(val == "money");

    //add seventh word: call
    tree.insert("call", "me");
    val = *(tree.search("call"));
    assert(val == "me");

    //add eighth word: ca
    tree.insert("ca", "lifornia");
    val = *(tree.search("ca"));
    assert(val == "lifornia");

    //make sure previous words are still there
    val = *(tree.search("cash"));
    assert(val == "money");
    val = *(tree.search("bash"));
    assert(val == "sudo");
    val = *(tree.search("cashier"));
    assert(val == "job");
    val = *(tree.search("bashes"));
    assert(val == "trash");
    val = *(tree.search("cashes"));
    assert(val == "moola");
    val = *(tree.search("case"));
    assert(val == "closed");
    val = *(tree.search("call"));
    assert(val == "me");
    val = *(tree.search("ca"));
    assert(val == "lifornia");

    //add ninth word: ba
    tree.insert("ba", "kery");
    val = *(tree.search("ba"));
    assert(val == "kery");

    //make sure previous words are still there
    val = *(tree.search("cash"));
    assert(val == "money");
    val = *(tree.search("bash"));
    assert(val == "sudo");
    val = *(tree.search("cashier"));
    assert(val == "job");
    val = *(tree.search("bashes"));
    assert(val == "trash");
    val = *(tree.search("cashes"));
    assert(val == "moola");
    val = *(tree.search("case"));
    assert(val == "closed");
    val = *(tree.search("call"));
    assert(val == "me");
    val = *(tree.search("ca"));
    assert(val == "lifornia");


}

void testRT2() {
    RadixTree<std::string> tree;
    string val;

    tree.insert("cashier", "lifornia");
    val = *(tree.search("cashier"));
    assert(val == "lifornia");

    tree.insert("cash", "x");
    val = *(tree.search("cash"));
    assert(val == "x");
}

void testRT3() {
    RadixTree<std::string> tree;
    string val;

    tree.insert("Ahart@gmail.com", "1");
    val = *(tree.search("Ahart@gmail.com"));
    assert(val == "1");

    tree.insert("AmJuare@gmail.com", "2");
    val = *(tree.search("AmJuare@gmail.com"));
    assert(val == "2");
    val = *(tree.search("Ahart@gmail.com"));
    assert(val == "1");

    tree.insert("AmH74@gmail.com", "3");
    cout << *(tree.search("AmH74@gmail.com")) << endl;
    val = *(tree.search("AmH74@gmail.com"));
    assert(val == "3");
    val = *(tree.search("AmJuare@gmail.com"));
    assert(val == "2");
    val = *(tree.search("Ahart@gmail.com"));
    assert(val == "1");
}

void testAttTranslator() {
    AttributeTranslator at;
    string filename = "/Users/mcapetz/Desktop/projects/CS32/Project_4_/Project_4_/translator.txt";
    cout << at.Load(filename) << endl;
}

void testMDB() {
    MemberDatabase mdb;
    string filename = "/Users/mcapetz/Desktop/projects/CS32/Project_4_/Project_4_/members.txt";
    cout << mdb.LoadDatabase(filename) << endl;
}

int main() {
    std::cout << "begin testing" << std::endl;
//    testRadixTree();
//    testAttTranslator();
//    testMDB();
//    testRT2();
    testRT3();
    std::cout << "all tests passed" << std::endl;
}

//const std::string MEMBERS_FILE    = "/Users/mcapetz/Desktop/projects/CS32/Project_4_/Project_4_/members.txt";
//const std::string TRANSLATOR_FILE = "/Users/mcapetz/Desktop/projects/CS32/Project_4_/Project_4_/translator.txt";
//
//bool findMatches(const MemberDatabase& mdb, const AttributeTranslator& at);
//
//int main() {
//    MemberDatabase mdb;
//    if (!mdb.LoadDatabase(MEMBERS_FILE))
//    {
//        std::cout << "Error loading " << MEMBERS_FILE << std::endl;
//        return 1;
//    }
//    AttributeTranslator at;
//    if (!at.Load(TRANSLATOR_FILE))
//    {
//        std::cout << "Error loading " << TRANSLATOR_FILE << std::endl;
//        return 1;
//    }
//
//    while (findMatches(mdb, at))
//        ;
//
//    std::cout << "Happy dating!" << std::endl;
//}
//
//bool findMatches(const MemberDatabase& mdb, const AttributeTranslator& at)
//{
//      // Prompt for email
//    std::string email;
//    const PersonProfile* pp;
//    for (;;) {
//        std::cout << "Enter the member's email for whom you want to find matches: ";
//        std::getline(std::cin, email);
//        if (email.empty())
//            return false;
//        pp = mdb.GetMemberByEmail(email);
//        if (pp != nullptr)
//            break;
//        std::cout << "That email is not in the member database." << std::endl;
//    }
//
//      // Show member's attribute-value pairs
//    std::cout << "The member has the following attributes:" << std::endl;
//    for (int k = 0; k != pp->GetNumAttValPairs(); k++) {
//        AttValPair av;
//        pp->GetAttVal(k, av);
//        std::cout << av.attribute << " --> " << av.value << std::endl;
//    }
//
//      // Prompt user for threshold
//    int threshold;
//    std::cout << "How many shared attributes must matches have? ";
//    std::cin >> threshold;
//    std::cin.ignore(10000, '\n');
//
//      // Print matches and the number of matching translated attributes
//    MatchMaker mm(mdb, at);
//    std::vector<EmailCount> emails = mm.IdentifyRankedMatches(email, threshold);
//    if (emails.empty())
//        std::cout << "No member was a good enough match." << std::endl;
//    else {
//        std::cout << "The following members were good matches:" << std::endl;;
//        for (const auto& emailCount : emails) {
//            const PersonProfile* pp = mdb.GetMemberByEmail(emailCount.email);
//            std::cout << pp->GetName() << " at " << emailCount.email << " with "
//                      << emailCount.count << " matches!" << std::endl;
//        }
//    }
//    std::cout << std::endl;
//    return true;
//}

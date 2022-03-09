//
//  RadixTree.h
//  Project_4_
//
//  Created by Margaret Capetz on 3/4/22.
//

//USING MAP BECAUSE I CANNOT HANDLE THIS RN

//#ifndef RadixTree_h
//
//#define RadixTree_h
//
//#include <string>
//
//#include <vector>
//
//#include <map>
//
//#include "provided.h"
//
///*
//
//
//
// ● MUST be a class template, implemented fully in RadixTree.h.
//
// ● MUST hold a number of nodes that is proportional to the number of unique key-value
//
// pairs inserted in the Radix Tree, NOT a number of nodes that is proportional to the
//
// number of keys times the average key length.
//
// ● MUST have a big-O for insertion of O(K) where K is the maximum key length of a new
//
// item being inserted into the Radix Tree, and for searches, O(K) where K is the maximum
//
// key length of the items in the Radix Tree.
//
// ● MUST be case-sensitive for all searches
//
// ● MUST be able to accommodate any number of key-value pairs
//
// ● MUST NOT use the STL map, unordered_map, multimap, or unordered_multimap types
//
// (in your final submission)
//
// ● MUST NOT add any new public member functions or variables
//
// ● MAY avoid dealing with an empty key string
//
// ● MAY use the STL set, list and vector classes
//
// ● MAY have any private member functions or variables you choose to add
//
//
//
// */
//
//
//
//
//
//
//
//
//
////TODO: MUST REPLACE WITH ACTUAL RADIX TREE INSTEAD OF MAP
//
//template<typename ValueType>
//
//class RadixTree{
//
//public:
//
//    RadixTree():m_size(0){}
//
//    ~RadixTree(){}
//
//    void insert(std::string key, const ValueType& value){
//
//        m_map[key] = value;
//
//    }
//
//    ValueType* search(std::string key) const{
//
//        auto it = m_map.find(key);
//
//        if(it == m_map.end()) return nullptr;
//
//        return const_cast<ValueType*>(&(it->second));
//
//    }
//
//    std::map<std::string, ValueType> m_map;
//
//private:
//
//    int m_size;
//
////    struct Node{
//
////        std::string key;
//
////        ValueType& value;
//
////        vector<Node*> children;
//
////    }
//
//};
//
//
//
//#endif

#ifndef RadixTree_h
#define RadixTree_h
#define CHAR_SIZE 128

#include <string>

#include <iostream>

using namespace std;

template <typename ValueType>
class RadixTree {
public:
    RadixTree() {
        root = new Node();
    }
    ~RadixTree() {

    }
    
    //ValueType* search(std::string key) const;


    void insert(std::string key, const ValueType& value) {
        //cout << "beginnign to insert: " << key << endl;
        
        //insert first node
        if(root->edges[key[0]] == nullptr) {
            //root is nullptr so make a new node
            Node* newKey = new Node();
            newKey->word = key;
            newKey->value = value;
            newKey->endOfWord = true;
            root->edges[key[0]] = newKey;
            return;
        }

        Node* curr = root->edges[key[0]];
        
        int i = 0;
        
        while(i < key.size()) {
            int j = 0;
            
            //case 1: key and curr word are the same
            if(curr->word == key.substr(i)) {
                //cout << "case 1: " << key << endl;
                curr->value = value;
                if(!curr->endOfWord) curr->endOfWord = true;
                return;
            }
            
            //prefix
            while(i < key.size() && j < curr -> word.size()) {
                if(key[i] == curr->word[j]) {
                    i++;
                    j++;
                }
                else break;
            }
            string prefix = curr->word.substr(0,j);
            
            
            //case 2: all of child is in parent (carpet is already there, inputting car)
            if(i == key.size()) {
                //cout << "case 2" << endl;
                //make a new node
                Node* newKey = new Node();
                newKey->word = curr->word.substr(prefix.size());
                newKey->value = curr->value;
                newKey->endOfWord = curr->endOfWord;
                //cout << "new key word: " << newKey->word << endl;
                
                //copy over the children & wipe out curr children
                for(int k = 0; k < CHAR_SIZE; k++) {
                    newKey->edges[k] = curr->edges[k];
                    curr->edges[k] = nullptr;
                }
                
                //reset curr val
                curr->word = prefix;
                curr->value = value;
                curr->endOfWord = true;
                curr->edges[newKey->word[0]] = newKey;
                return;
            }
            
            //case 3: went through entire node, more input (car is already there, inputting carpet)
            else if(j == curr->word.size()) {
                //cout << "case 3" << endl;
                if(curr->edges[key[i]] == nullptr) {
                    //add a new node
                    Node* newKey = new Node();
                    newKey->word = key.substr(i);
                    newKey->value = value;
                    newKey->endOfWord = true;
                    curr->edges[key[i]] = newKey;
                    return;
                }
                else {
                    //incrememnt curr
                    curr = curr->edges[key[i]];
                }
            }
            
            //case 4: splitting
            else {
//                cout << "splitting" << endl;
//                cout << "curr word: " << curr->word << endl;
//                cout << "key: " << key << endl;
//                cout << "curr key: " << key.substr(i) << endl;
                Node* nextKey = new Node();
                //copy the children & wipe them out
                for(int x = 0; x < CHAR_SIZE; x++) {
                    nextKey->edges[x] = curr->edges[x];
                    curr->edges[x] = nullptr;
                }
                nextKey->value = curr->value;
                nextKey->endOfWord = curr->endOfWord;
                nextKey->word = curr->word.substr(j);
                //cout << "next: " << nextKey->word << endl;

                Node* newKey = new Node();
                newKey->value = value;
                newKey->endOfWord = true;
                //cout << "i: " << i << endl;
                //cout << "j: " << j << endl;
                //cout << "prefix: " << prefix << endl;
                newKey->word = key.substr(i);
                //cout << "new key word: " << newKey->word << endl;
                
                curr->word = prefix;
                curr->endOfWord = false;

                curr->edges[newKey->word[0]] = newKey;
                curr->edges[nextKey->word[0]] = nextKey;
                //cout << "done splitting: " << key << endl;
                return;
            }
               
        }
    }

    ValueType* search(std::string key) const {
        int i = 0;
        Node* curr = root;
        
        while(i < key.size()) {
            int index = key[i];
            if(curr->edges[index] != nullptr) {
                curr = curr->edges[index]; //set curr to child
                if(curr->word == key.substr(i, curr->word.size())) { //if word matches, then increment i
                    i += curr->word.size();
                }
            }
            else return nullptr;
        }
        
        if(i == key.size() && curr->endOfWord) return &curr->value;
        else return nullptr;

    }


private:
    struct Node {
    public:
        std::string word;
        bool endOfWord;
        Node* edges[CHAR_SIZE];
        ValueType value;

        Node() {
            word = "";
            endOfWord = false;
            for(int i = 0; i < CHAR_SIZE; i++) {
                edges[i] = nullptr;
            }
        }
    };

    Node* root;
    
};


#endif /* RadixTree_h */

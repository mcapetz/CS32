//
//  RadixTree.h
//  Project_4_
//
//  Created by Margaret Capetz on 3/4/22.
//

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
        root = nullptr;
    }
    ~RadixTree() {
        
    }
    void insert(std::string key, const ValueType& value) {
        cout << "beginning insert" << endl;
        // start from the root node
        Node* curr = root;
            
        //first node
        if(curr == nullptr) {
            root = new Node();
            root->word = key;
            root->value = value;
            root->endOfWord = true;
            cout << "added first node, curr word is " << root->word << endl;
            return;
        }
        
        //check if prefixes match
        int size = (int)curr->word.size();
        if(curr->word == key.substr(0, size)) {
            cout << "prefixes match" << endl;
            
            //???
            
            //words don't match so move to the next node
            curr = curr->edges[key[size-1]];
        }
        else cout << "prefixes don't match" << endl;
        
        for(int i = 0; i < key.size(); i++) {
            int currLetter = key[i] - 'a';
            
            //a path doesn't exist
            if (curr->edges[currLetter] == nullptr) {
                cout << "path doesn't exist" << endl;
                cout << "curr letter: " << key[i] - 'a' << endl;
                
                //add a new node
                Node* next = new Node();
                curr->edges[currLetter] = next;
                next->word = key.substr(1);
                cout << "next word is " << next->word;
                
                //factor the word
                curr->edges[curr->word[0]] = new Node();
                curr->edges[curr->word[0]]->word = curr->word.substr(1);
                curr->edges[curr->word[0]]->endOfWord = true;
                curr->word = "";
                
                //new node for new word
                curr->edges[key[i]] = new Node();
                curr->edges[key[i]]->word = curr->word.substr(1);
                curr->edges[key[i]]->endOfWord = true;
            }
            
            //go to next word
            curr = curr->edges[key[i]];
        }
        
    }
    
    ValueType* search(std::string key) const {
        cout << "beginning search" << endl;
        
//        Node* curr = root;
//        int firstLetter = key[0] - 'a';
//        string currWord = key;
//        while(currWord != "") {
//            int size = curr->word.size();
//            if(curr->word == currWord.substr(0, size)) {
//                //update curr
//                //update currWord
//            }
//            return false;
//        }
//
//        return curr->endOfWord;
        
        
        //return nullptr if RT is empty
        //if(root == nullptr) return nullptr;

        Node* curr = root;
        
        cout << "key: " << key << endl;
        cout << "curr word: " << curr->word << endl;
//        cout << "curr value: " << &(curr->value) << endl;
//        cout << "curr end of word: " << &(curr->endOfWord) << endl;
        
        //check if prefixes match
        int size = (int)curr->word.size();
        if(curr->word == key.substr(0, size)) {
            cout << "prefixes match" << endl;
            
            //words match
            if(curr->word == key) {
                if(curr->endOfWord) return &curr->value; //end of word so word is valid
                else return nullptr; //not end of word so not valid
            }
            
            //words don't match so move to the next node
            curr = curr->edges[key[size-1]];
        }
        else cout << "prefixes don't match" << endl;
        
        for(int i = 0; i < key.size(); i++) {
            //check if word matches
            std::string remainingWord = "";
            for(int j = i; j < key.size(); j++) {
                remainingWord += key[j];
            }
            if(remainingWord == curr->word && curr->endOfWord) return &curr->value;

            //go to the next node
            curr = curr->edges[key[i]];

            //if the key is not in the RT
            if(curr == nullptr) return nullptr;
        }

        //end of string is reached
        if(curr->endOfWord) return &curr->value;
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

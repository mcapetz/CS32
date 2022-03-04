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


template <typename ValueType>
class RadixTree {
public:
    RadixTree() {
        root = new Node();
    }
    ~RadixTree() {
        
    }
    void insert(std::string key, const ValueType& value) {
        // start from the root node
        Node* curr = this->root;
            
        //first node
        if(curr == nullptr) {
            curr->word = key;
            curr->endOfWord = true;
        }
        
        for(int i = 0; i < key.size(); i++) {
            
            //a path doesn't exist
            if (curr->edges[key[i]] == nullptr) {
            
                //factor the word
                curr->edges[curr->word[0]] = new Node();
                curr->edges[curr->word[0]]->word = curr->word.substr(1);
                curr->edges[curr->word[0]]->endOfWord = true;
                curr->word = "";
                
                //new node for new word
                curr->edges[key[i]] = new Node();
                curr->edges[key[i]]->word = curr->key.substr(1);
                curr->edges[key[i]]->endOfWord = true;
            }
            
            //go to next word
            curr = curr->edges[key[i]];
        }
        
    }
    
    ValueType* search(std::string key) const {
        //return nullptr if RT is empty
        if(this->root == nullptr) return nullptr;

        Node* curr = this->root;
        for(int i = 0; i < key.size(); i++) {
            //check if word matches
            std::string remainingWord = "";
            for(int j = i; j < key.size(); j++) {
                remainingWord += key[j];
            }
            if(remainingWord == curr->word && curr->endOfWord) return curr->value;
            
            //go to the next node
            curr = curr->edges[key[i]];
            
            //if the key is not in the RT
            if(curr == nullptr) return nullptr;
        }
        
        //end of string is reached
        if(curr->endOfWord) return curr->value;
        else return nullptr;
    }
    
    
private:
    struct Node {
        std::string key;
        std::string word;
        bool endOfWord;
        Node* edges[CHAR_SIZE];
        ValueType* value;
        
        Node() {
            this->endOfWord = false;
            for(int i = 0; i < CHAR_SIZE; i++) {
                this->edges[i] = nullptr;
            }
            this->value = nullptr;
        }
    };
    
    Node* root;
};

#endif /* RadixTree_h */

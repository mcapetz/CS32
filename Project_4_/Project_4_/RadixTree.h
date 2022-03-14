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
#include <vector>

#include <iostream>


template <typename ValueType>
class RadixTree {
public:
    RadixTree() {
        root = new Node();
        nodesToDelete.push_back(root); //add new Node* to vect to delete in destructor
    }
    ~RadixTree() {
        //std::cout << "del size: " << nodesToDelete.size() << std::endl;
        for(int i = 0; i < nodesToDelete.size(); i++) { //iterate through vector of pointers
            delete nodesToDelete[i]; //delete to avoid memory leak
        }
    }
    
    void insert(std::string key, const ValueType& value) {
        
        //insert first node
        if(root->edges[key[0]] == nullptr) {
            //root is nullptr so make a new node
            Node* newKey = new Node();
            newKey->word = key;
            newKey->value = value;
            newKey->endOfWord = true;
            root->edges[key[0]] = newKey;
            nodesToDelete.push_back(newKey); //add new Node* to vect to delete in destructor
            return;
        }

        Node* curr = root->edges[key[0]];
        
        int i = 0;
        
        while(i < key.size()) {
            int j = 0;
            
            //case 1: key and curr word are the same
            if(curr->word == key.substr(i)) {
                curr->value = value; //update value
                if(!curr->endOfWord) curr->endOfWord = true;
                return;
            }
            
            //prefix
            while(i < key.size() && j < curr -> word.size()) {
                if(key[i] == curr->word[j]) {
                    i++; //index for key
                    j++; //index for curr->word
                }
                else break;
            }
            std::string prefix = curr->word.substr(0,j);
            
            
            //case 2: all of child is in parent (carpet is already there, inputting car)
            if(i == key.size()) {
                //make a new node
                Node* newKey = new Node();
                newKey->word = curr->word.substr(prefix.size());
                newKey->value = curr->value;
                newKey->endOfWord = curr->endOfWord;
                
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
                
                nodesToDelete.push_back(newKey); //add new Node* to vect to delete in destructor
                return;
            }
            
            //case 3: went through entire node, more input (car is already there, inputting carpet)
            else if(j == curr->word.size()) {
                if(curr->edges[key[i]] == nullptr) {
                    //add a new node
                    Node* newKey = new Node();
                    newKey->word = key.substr(i);
                    newKey->value = value;
                    newKey->endOfWord = true;
                    curr->edges[key[i]] = newKey;
                    
                    nodesToDelete.push_back(newKey); //add new Node* to vect to delete in destructor
                    return;
                }
                else {
                    curr = curr->edges[key[i]]; //increment curr
                }
            }
            
            //case 4: splitting
            else {
                //make a new node for the old curr word
                Node* nextKey = new Node();
                //copy the children & wipe them out
                for(int x = 0; x < CHAR_SIZE; x++) {
                    nextKey->edges[x] = curr->edges[x];
                    curr->edges[x] = nullptr;
                }
                nextKey->value = curr->value;
                nextKey->endOfWord = curr->endOfWord;
                nextKey->word = curr->word.substr(j); //curr word excluding prefix

                //make a new node for the new key
                Node* newKey = new Node();
                newKey->value = value; //update value
                newKey->endOfWord = true;
                newKey->word = key.substr(i); //key excluding prefix
                
                curr->word = prefix;
                curr->endOfWord = false;
                
                //connect new nodes
                curr->edges[newKey->word[0]] = newKey;
                curr->edges[nextKey->word[0]] = nextKey;
                
                nodesToDelete.push_back(newKey); //add new Node* to vect to delete in destructor
                nodesToDelete.push_back(nextKey); //add new Node* to vect to delete in destructor
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
                    i += curr->word.size(); //increment i
                }
            }
            else return nullptr;
        }
        
        if(i == key.size() && curr->endOfWord) return &curr->value; //found!
        else return nullptr; //not found

    }


private:
    struct Node {
    public:
        std::string word;
        bool endOfWord;
        Node* edges[CHAR_SIZE];
        ValueType value;

        Node() { //constructor defaults edges to nullptr, endOfWord to false, word to be empty (does not have a default ValueType value)
            word = "";
            endOfWord = false;
            for(int i = 0; i < CHAR_SIZE; i++) {
                edges[i] = nullptr;
            }
        }
    };

    Node* root;
    std::vector<Node*> nodesToDelete;
    
};


#endif /* RadixTree_h */

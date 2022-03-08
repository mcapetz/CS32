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
#include <unordered_map>


using namespace std;

template <typename ValueType>
class RadixTree {
public:
    RadixTree() {
        root = new Node();
    }
    ~RadixTree() {

    }
    
    void insert(std::string key, const ValueType& value) {
        //cout << "beginning insert: " << key << endl;
        
        insertH(root, key, value);
        
    }

    ValueType* search(std::string key) const {
        //cout << "beginning search" << endl;
                
        return searchH(root, key);
        
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
    
    void insertH(Node* curr, string key, const ValueType& value) {
        //base case
        if(curr == nullptr) {
            //root is nullptr so make a new node
            curr = new Node();
            curr->word = key;
            curr->value = value;
            curr->endOfWord = true;
            return;
        }
        
        
        //case II: first letter matches
        //check for prefix
        int i = 0;
        int j = 0;
        int count = 0;
        while(i < curr->word.size() && j < key.size()) {
            //cout << curr->word[i] << " , " << key[j] << endl;
            if(curr->word[i] == key[j]) count++;
            if(curr->word[i] != key[j]) break;
            i++;
            j++;
        }
        string prefix = key.substr(0,count);
        //cout << "prefix is: " << prefix << endl;
        
        //case 0: no prefix
        if(prefix == "") {
            //cout << "case 0: no prefix" << endl;
            insertH(curr->edges[key[prefix.size()]], key, value);
        }
        
        //case a: all of child is in parent
        else if(curr->word == key.substr(0,prefix.size())) {
            //cout << "case a" << endl;
            //cout << "going to: " << key[prefix.size()] << endl;
            //cout << "new key is: " << key.substr(prefix.size()) << endl;
            insertH(curr->edges[key[prefix.size()]], key.substr(prefix.size()), value);
        }
        
        //case b: exact match and endOfWord is false
        else if(curr->word == key && !curr->endOfWord) {
            //cout << "case b" << endl;
            curr->value = value;
            curr->endOfWord = true;
            return;
        }
        
        //case c: partial prefix
        else {
            //cout << "case c" << endl;
            Node* nextKey = new Node();
            for(int i = 0; i < CHAR_SIZE; i++) {
                nextKey->edges[i] = curr->edges[i];
            }
            nextKey->value = curr->value;
            nextKey->endOfWord = curr->endOfWord;
            nextKey->word = curr->word.substr(prefix.size());
            //cout << "next key value: " << nextKey->value << endl;
            string nextKeyWord = curr->word.substr(prefix.size());
            //cout << "next key word: " << nextKeyWord << endl;
            
            //cout << "curr word: " << curr->word << endl;
            //cout << "prefix: " << prefix << endl;
            
            if(prefix == key) {
                //cout << "i got here" << endl;
                curr->endOfWord = true;
                curr->value = value;
                curr->word = prefix;
                //cout << "adding nexKey to: " << nextKeyWord[0] << endl;
                curr->edges[nextKeyWord[0]] = nextKey;
                return;
            }
            
            curr->word = prefix;
            for(int i = 0; i < CHAR_SIZE; i++) {
                curr->edges[i] = nullptr;
            }
            curr->endOfWord = false;
            
            Node* newKey = new Node();
            newKey->value = value;
            newKey->endOfWord = true;
            newKey->word = key.substr(prefix.size());
            //cout << "new key word: " << newKey->word << endl;
            
            curr->edges[key[prefix.size()]] = newKey;
            curr->edges[nextKeyWord[0]] = nextKey;
            return;
                
        }
        
        //case: word & first letter doesn't match
        if(curr->edges[key[0]] == nullptr) {
            //make a new node
            //cout << "made a new node base case" << endl;
            //cout << "prefix is: " << prefix << endl;
            //cout << "parent is: " << curr->word << endl;
            Node* newNode = new Node();
            newNode->word = key.substr(prefix.size());
            newNode->value = value;
            newNode->endOfWord = true;
            curr->edges[key[prefix.size()]] = newNode;
            //cout << "at " << key[prefix.size()] << endl;
            //cout << "key: " << newNode->word << endl;
            return;
        }
        
        
        return;
    }
    
    ValueType* searchH(Node* curr, string key) const {
        //base case
        if(key == curr->word && curr->endOfWord) return &curr->value;
        
        //case I: first letter matches
        //check for prefix
        int i = 0;
        int j = 0;
        int count = 0;
        while(i < curr->word.size() && j < key.size()) {
            //cout << curr->word[i] << " , " << key[j] << endl;
            if(curr->word[i] == key[j]) count++;
            if(curr->word[i] != key[j]) break;
            i++;
            j++;
        }
        string prefix = key.substr(0,count);
        //cout << "prefix is: " << prefix << endl;
        
        if(prefix == "" && curr->edges[key[0]] == nullptr) return nullptr;
        
        if(prefix != curr->word) return nullptr;
        if(curr->edges[key[prefix.size()]] == nullptr) return nullptr;
        //cout << "going to: " << key[prefix.size()] << endl;
        //cout << "new key substr: " << key.substr(prefix.size()) << endl;
        return searchH(curr->edges[key[prefix.size()]], key.substr(prefix.size()));
        
    }
};

#endif /* RadixTree_h */

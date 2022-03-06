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
        cout << "beginning insert: " << key << endl;
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
        
        
        if(curr->word != "") {
            cout << "first check" << endl;
            cout << "curr word: " << curr->word << endl;
            cout << "key word: " << key << endl;
            
            //find prefix
            int i = 0;
            int j = 0;
            int count = 0;
            while(i < curr->word.size() && j < key.size()) {
                cout << curr->word[i] << " , " << key[j] << endl;
                if(curr->word[i] == key[j]) count++;
                if(curr->word[i] != key[j]) break;
                i++;
                j++;
            }
            cout << "prefix is: " << key.substr(0,count) << endl;
        }
       
        
//        //check if prefixes match
//        int size = (int)curr->word.size();
//        if(curr->word != "" && curr->word == key.substr(0, size)) {
//            cout << "prefixes match" << endl;
//            cout << "prefix is: " << curr->word << endl;
//            //???
//
//            //words don't match so move to the next node
//            curr = curr->edges[key[size-1]];
//        }
//        else cout << "prefixes don't match" << endl;
        
        for(int i = 0; i < key.size(); i++) {
            cout << "curr letter: " << key[i] << endl;
            int currLetter = key[i] - 'a';
            string originalWord = "";
            if(curr) originalWord = curr->word;
            cout << "curr word is: " << curr->word << endl;
            cout << "key substr: " << key.substr(i, curr->word.size()) << endl;
            
            //check if curr->word is a prefix
            if(curr->word != "" && curr->word == key.substr(i, curr->word.size())) {
                cout << "prefixes match" << endl;
                i += curr->word.size();
                //curr = curr->edges[key[i]-'a'];
                currLetter = key[i] - 'a';
                cout << "curr letter: " << key[i] << endl;
                
                if (curr->edges[currLetter] == nullptr) {
                    //a path doesn't exist
                    //add a new node for new word
                    Node* next = new Node();
                    curr->edges[currLetter] = next;
                    next->word = key.substr(i+1);
                    cout << "next word is " << next->word << endl;
                    next->value = value;
                    next->endOfWord = true;
                    cout << "done" << endl;
                    return;
                }
            }
            
            //check if they share a common prefix
            if(curr->word != "") {
                cout << "curr word: " << curr->word << endl;
                cout << "key word: " << key.substr(i) << endl;
                //find prefix
                int k = 0;
                int j = 0;
                int count = 0;
                string currkey = key.substr(i);
                while(k < curr->word.size() && j < currkey.size()) {
                    if(curr->word[k] == currkey[j]) count++;
                    if(curr->word[k] != currkey[j]) break;
                    k++;
                    j++;
                }
                cout << "i: " << i << endl;
                cout << "count: " << count << endl;
                cout << "prefix is: " << key.substr(i,count) << endl;
                
                
                if(key.substr(i,count) != "") {
                    //prefix exists
                    cout << "prefix exists" << endl;
                    
                    //original is now next: onext
                    Node* onext = new Node();
                    for(int i = 0; i < CHAR_SIZE; i++) { //copy over child nodes
                        onext->edges[i] = curr->edges[i];
                    }
                    
                    //make connector if necessary
                    if(curr->word.substr(count).size() > 1) {
                        Node* connector = new Node();
                        connector->word = curr->word.substr(count, curr->word.size()-count-1);
                        connector->edges[curr->word.substr(curr->word.size()-1)[0] - 'a'] = onext;
                        cout << "connector word: " << connector->word << endl;
                    }
                    
                    //new key
                    Node* newKey = new Node();
                    newKey->word = key.substr(i+count+1);
                    cout << "newKey: " << newKey->word << endl;
                    newKey->value = value;
                    newKey->endOfWord = true;
                    
                    //change curr node
                    for(int i = 0; i < CHAR_SIZE; i++) { //reset pointers
                        curr->edges[i] = nullptr;
                    }
                    curr->word = key.substr(i,count); //set word to prefix
                    if(curr->word.substr(count).size() > 1) {
                        //connector exists
                        //TO DO !!!
                    }
                    //connector doesn't exist
                    else {
                        curr->edges[curr->word.substr(count)[0] - 'a'] = onext;
                    }
                    curr->edges[key.substr(i+count)[0] - 'a'] = newKey;
                    return;
                    
                }
            }
            
            //a path doesn't exist, need to make a leaf
            if (curr->edges[currLetter] == nullptr) {
                cout << "path doesn't exist" << endl;
                cout << "curr letter: " << key[i] << endl;
                
                //add a new node for new word
                Node* next = new Node();
                curr->edges[currLetter] = next;
                next->word = key.substr(i+1);
                cout << "next word is " << next->word << endl;
                next->value = value;
                next->endOfWord = true;
                
                //cancel original word
                curr->word = "";
                
                //add a new node for original word
                //check if path exists
                if(curr->edges[originalWord[0] - 'a'] == nullptr) {
                    //path does not exits
                    Node* onext = new Node();
                    curr->edges[originalWord[0] - 'a'] = onext;
                    onext->word = originalWord.substr(1);
                    cout << "original next word is " << onext->word << endl;
                    onext->value = curr->value;
                    onext->endOfWord = true;
                    return;
                }
                else cout << "path exists... now what" << endl;
                
//                //factor the word
//                curr->edges[curr->word[0]] = new Node();
//                curr->edges[curr->word[0]]->word = curr->word.substr(1);
//                curr->edges[curr->word[0]]->endOfWord = true;
//                curr->word = "";
//
//                //new node for new word
//                curr->edges[key[i]] = new Node();
//                curr->edges[key[i]]->word = curr->word.substr(1);
//                curr->edges[key[i]]->endOfWord = true;
            }
            
            //go to next word
            cout << "going to " << key[i] << endl;
            curr = curr->edges[key[i]-'a'];
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
        if(curr->word != "" && curr->word == key.substr(0, size)) {
            cout << "prefixes match" << endl;
            
            //words match
            if(curr->word == key) {
                if(curr->endOfWord) return &curr->value; //end of word so word is valid
                else return nullptr; //not end of word so not valid
            }
            
            //words don't match so move to the next node
            curr = curr->edges[key[size-1] - 'a'];
        }
        else cout << "prefixes don't match" << endl;
        
        for(int i = 0; i < key.size(); i++) {
            //check if word matches
            string remainingWord = key.substr(i);
            cout << "remaining word: " << remainingWord << endl;
            
            //see if words match
            if(curr->word != "" && remainingWord == curr->word && curr->endOfWord) {
                cout << "found!" << endl;
                //cout << "value: " << curr->value << endl;
                return &curr->value;
            }
            
            //see if curr->word is a prefix
            if(curr->word != "" && curr->word == key.substr(i, curr->word.size())) {
                cout << "prefixes match" << endl;
                cout << "curr word: " << curr->word << endl;
                i += curr->word.size();
            }
            
            
            //go to the next node
            curr = curr->edges[key[i] - 'a'];

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

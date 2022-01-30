//
//  main.cpp
//  eval
//
//  Created by Margaret Capetz on 1/27/22.
//

#include "Map.h"
        #include <iostream>
        #include <string>
        #include <stack>
        #include <cctype>
        #include <cassert>
        using namespace std;


using namespace std;

//declarations of any additional functions you might have written
//                to help you evaluate an expression

void clean(string& infix); //removes blanks
bool isInfixValid(string infix); //returns true if string is valid infix notation
bool infixContainsUnknownValue(string infix, const Map& values); //returns true if infix contains a value unknown to the map
void inToPostConversion(string infix, string& postfix);
int operatorPrecedence(const char ch);
bool postEval(const string& postfix, const Map& values, int& result);

int evaluate(string infix, const Map& values, string& postfix, int& result) {
    if(!isInfixValid(infix)) return 1;
    inToPostConversion(infix, postfix);
    if(infixContainsUnknownValue(infix, values)) return 2;
    
    if(postEval(postfix, values, result)) return 3;
    return 0;
}
          // Evaluates an integer arithmetic expression

          //   If infix is a syntactically valid infix integer expression whose
          //   only operands are single lower case letters (whether or not they
          //   appear in the values map)
                    //then postfix is set to the postfix form of the expression; otherwise postfix may or may not be changed, result is unchanged, and the function returns 1.

            //If infix is syntactically valid but contains at least one lower
          // case letter operand that does not appear in the values map
                    //then result is unchanged and the function returns 2.


        //      If infix is syntactically valid and all its lower case operand letters
          //   appear in the values map,

                    //then if evaluating the expression
                  //   (using for each letter in the expression the value in the map
                  //   that corresponds to it) attempts to divide by zero, then result
                  //   is unchanged and the function returns 3;

                    //otherwise, result is
          //        set to the value of the expression and the function returns 0.


//implementations of any additional functions you might have written
//                to help you evaluate an expression
//
//        a main routine to test your function

void clean(string& infix) {
    //remove the blanks
    //remove blanks from beginning
    if(infix.size() == 0) return;
    
    while(infix.size() != 0 && infix.at(0) == ' ') {
        infix = infix.substr(1);
    }
    
    while(infix.size() != 0 && infix.at(infix.size()-1) == ' ') {
        infix = infix.substr(0, infix.size()-1);
    }
    
    //remove blanks from middle
    for(int i = 0; i < infix.size(); i++) {
        while(infix.at(i) == ' ') {
            infix = infix.substr(0, i) + infix.substr(i+1);
        }
    }
}

bool isInfixValid(string infix) {
    //syntactically correct means all lower case letters or
    //+, -, *, and /, parentheses or blanks ' '
    
    clean(infix);
    if(infix.size() == 1 && isalpha(infix.at(0))) return true;
    if(infix.size() < 3) return false; //otherwise infix must have at least 3 chars
    
    int numOfParens = 0;
    int numOfAlpha = 0;
    int numOfOper = 0;
    
    for(int i = 0; i < infix.size(); i++) {
        char c = infix.at(i);
        if(isalpha(c)) { //is alphabetic
            if(!islower(c)) return false; //must be lower case
            if(i != infix.size()-1 && isalpha(infix.at(i+1))) return false; //must be followed by an operator
            numOfAlpha++;
        }
        else {
            //if c is a '('
            if(c == '(') {
                numOfParens++;
                if(i == infix.size()-1) return false; //cannot end with (
                if(i != 0) {
                    char a = infix.at(i-1);
                    if(a != '+' && a != '-' && a != '*' && a != '/' && a != '(') { //( or operator must procced (
                        return false;
                    }
                }
                char a = infix.at(i+1);
                if(a != '(' && !isalpha(a)) { //alpha or ( must follow (
                    return false;
                }
            }
            //if c is a ')'
            else if(c == ')') {
                numOfParens--;
                if(i == 0) return false; //cannot begin with )
                char a = infix.at(i-1);
                if(a != ')' && !isalpha(a)) { //alpha or ) must proceed )
                    return false;
                }
                if(i != infix.size()-1){
                    char a = infix.at(i+1);
                    if(a != '+' && a != '-' && a != '*' && a != '/' && a != ')') {
                        return false;
                    }
                }
            }
            
            else { //c is not a parantheses
                if(i == 0 || i == infix.size()-1) return false; //cannot begin or end with operator
                if(i != infix.size()-1 && infix.at(i+1) != '(' && !isalpha(infix.at(i+1))) return false; //must be followed by a ( or alpha
                numOfOper++;
            }
        }
    }
    
    if(numOfParens != 0) return false; //must have balanced number of parens
    if(numOfAlpha == 1 && numOfOper == 0) return true;
    if(numOfAlpha < 2 || numOfOper < 1) return false; //must have at least 2 alphas and 1 operator
    return true;
}


bool infixContainsUnknownValue(string infix, const Map& values) {
    for(int i = 0; i < infix.size(); i++) {
        char a = infix.at(i);
        if(a != '+' && a != '-' && a != '*' && a != '/' && a != ')' && a != '(' && a != ' ') {
            if(!values.contains(a)) {
                return true;
            }
        }
    }
    return false;
}

void inToPostConversion(string infix, string& postfix) {
    clean(infix);
    //Initialize postfix to empty
    postfix = "";
//    Initialize the operator stack to empty
    stack<char> myStack;
    for(int i = 0; i < infix.size(); i++) {
        char ch = infix.at(i);
        switch(ch) {
            case '(':
                myStack.push(ch);
                break;
            case ')':
                while(myStack.top() != '(') {
                    postfix += myStack.top();
                    myStack.pop();
                }
                myStack.pop();
                break;
            case '+':
            case '-':
            case '*':
            case '/':
                while(!myStack.empty() && myStack.top() != '(' && operatorPrecedence(ch) <= operatorPrecedence(myStack.top())) { //this has problems most likely
                    postfix += myStack.top();
                    myStack.pop();
                }
                myStack.push(ch);
                break;
            default:
                //case operand:
                postfix += ch;
                break;
        }
    }
    while(!myStack.empty()) {
        postfix += myStack.top();
        myStack.pop();
    }
}

int operatorPrecedence(const char ch) {
    switch(ch) {
        case '+':
        case '-':
            return 1;
            break;
        case '*':
        case '/':
            return 2;
            break;
    }
    return 0;
}


bool postEval(const string& postfix, const Map& values, int& result) {
    int originalResult = result;
    
    stack<int> myStack;
    for(int i = 0; i < postfix.size(); i++) {
        char ch = postfix.at(i);
        if(isalpha(ch)) {
            //ch is an operand
            int val;
            values.get(ch, val);
            myStack.push(val);
        }
        else {
            //ch is a binary operator
            int operand2 = myStack.top();
            myStack.pop();
            int operand1 = myStack.top();
            myStack.pop();
            int res;
            switch(ch) {
                case '+':
                    res = operand1 + operand2;
                    break;
                case '-':
                    res = operand1 - operand2;
                    break;
                case '*':
                    res = operand1 * operand2;
                    break;
                case '/':
                    if(operand2 == 0) {
                        //trying to divide by zero
                        result = originalResult;
                        return true;
                    }
                    res = operand1 / operand2;
                    break;
            }
            myStack.push(res);
        }
        result = myStack.top();
    }
    return false;
}



int main(int argc, const char * argv[]) {
    char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
                int  vals[] = {  3,  -9,   6,   2,   4,   1  };
                Map m;
                for (int k = 0; vars[k] != '#'; k++)
                    m.insert(vars[k], vals[k]);
                string pf;
                int answer;

    answer = 999;
    
                //testing isValidInfix()
//                assert(evaluate("", m, pf, answer) == 1  &&  answer == 999); //empty string
//                assert(evaluate("a+", m, pf, answer) == 1  &&  answer == 999); //operator at end
//                assert(evaluate("a i", m, pf, answer) == 1  &&  answer == 999); //alpha following alpha
//                assert(evaluate("ai", m, pf, answer) == 1  &&  answer == 999); //alpha following alpha
//                assert(evaluate("()", m, pf, answer) == 1  &&  answer == 999); //only 2 chars
//                assert(evaluate("()o", m, pf, answer) == 1  &&  answer == 999); //incorrect multiplication
//                assert(evaluate("y(o+u)", m, pf, answer) == 1  &&  answer == 999); //incorrect multiplication
//                assert(evaluate("y(*o)", m, pf, answer) == 1  &&  answer == 999); //incorrect multiplication
//                assert(evaluate("a+E", m, pf, answer) == 1  &&  answer == 999); //upper case not allowed
//                assert(evaluate("(a+(i-o)", m, pf, answer) == 1  &&  answer == 999); //unbalanced parentheses
//                assert(evaluate("(a+(i-o))", m, pf, answer) == -1  &&  answer == 999); //correct
//                assert(evaluate("a+(i-o))", m, pf, answer) == 1  &&  answer == 999); //unbalanced parenethese
//                assert(evaluate("(a)/(i+u*z-o)", m, pf, answer) == -1  &&  answer == 999); //correct
//                assert(evaluate("-a", m, pf, answer) == 1  &&  answer == 999); //unary opeators not allowed
//                assert(evaluate("b*-a", m, pf, answer) == 1  &&  answer == 999); //two operators next to each other
//                assert(evaluate("b*)-a", m, pf, answer) == 1  &&  answer == 999); //operator before )
//                assert(evaluate("((()))", m, pf, answer) == 1  &&  answer == 999); //no alpha or operators
//                assert(evaluate(")(a+b", m, pf, answer) == 1  &&  answer == 999); //cannot begin with )
//                assert(evaluate("y*(*o)", m, pf, answer) == 1  &&  answer == 999); //operator cannot follow (
//                assert(evaluate("((((a+b", m, pf, answer) == 1  &&  answer == 999); //unbalanced parantheses
    
    
                //testing infixToPostfix
                assert(evaluate("a*b", m, pf, answer) == 2  && pf == "ab*"  &&  answer == 999);
    
    assert(evaluate("a*b", m, pf, answer) == 2  &&
                                        pf == "ab*"  &&  answer == 999);
    assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0);
    assert(pf == "yoau-*+");
    assert(answer == -1);
                answer = 999;
                assert(evaluate("o/(y-y)", m, pf, answer) == 3  &&
                                        pf == "oyy-/"  &&  answer == 999);
                assert(evaluate(" a  ", m, pf, answer) == 0  &&
                                        pf == "a"  &&  answer == 3);
                assert(evaluate("((a))", m, pf, answer) == 0  &&
                                        pf == "a"  &&  answer == 3);
                assert(evaluate("(a)", m, pf, answer) == 0  &&
                                        pf == "a"  &&  answer == 3);
    
    //testing clean function
//    clean("   ");
//    clean("a *   3 sd f ");
//    clean("      a * ");
    
    
    cerr << "all tests passed" << endl;
}

#ifndef INTFIXTOPOSTIFX_H
#define INTFIXTOPOSTIFX_H


#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

class intfixToPostfix
{
private:
    /* data */
public:
    intfixToPostfix(/* args */);
    ~intfixToPostfix();
    bool is_valid_regex(const std::string& regex);
    std::string regex_to_postfix(const std::string& regex);
};

//constructor
intfixToPostfix::intfixToPostfix(/* args */)
{
}


//destructor
intfixToPostfix::~intfixToPostfix()
{
}


#endif
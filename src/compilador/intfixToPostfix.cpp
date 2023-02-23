#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

bool is_valid_regex(const std::string &regex)
{//verifica que la expresion sea valida
    std::stack<char> parens;
    for (char c : regex)
    {
        switch (c)
        {
        case '(':
            parens.push(c);
            break;
        case ')':
            if (parens.empty() || parens.top() != '(')
            {
                return false;
            }
            parens.pop();
            break;
        case '|':
        case '.':
        case '*':
            if (parens.empty() || parens.top() == '|')
            {
                return false;
            }
            break;
        default:
            break;
        }
    }
    return parens.empty();
}

std::string regex_to_postfix(const std::string &regex)
{//parsea la expresión
    if (!is_valid_regex(regex))
    {
        throw std::invalid_argument("Invalid regular expression");
    }
    std::stack<char> operators;
    std::string postfix;
    std::unordered_map<char, int> precedence = {
        {'|', 0},
        {'.', 1},
        {'*', 2}};
    for (char c : regex)
    {
        switch (c)
        {
        case '(':
            operators.push(c);
            break;
        case ')':
            while (!operators.empty() && operators.top() != '(')
            {
                postfix += operators.top();
                operators.pop();
            }
            if (operators.top() == '(')
            {
                operators.pop();
            }
            break;
        case '|':
        case '.':
        case '*':
            while (!operators.empty() && operators.top() != '(' && precedence[operators.top()] >= precedence[c])
            {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(c);
            break;
        default:
            postfix += c;
            break;
        }
    }
    while (!operators.empty())
    {
        postfix += operators.top();
        operators.pop();
    }
    return postfix;//cadena como postfix
}
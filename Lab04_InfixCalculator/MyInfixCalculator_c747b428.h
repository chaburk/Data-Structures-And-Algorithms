#ifndef __MYINFIXCALCULATOR_H__
#define __MYINFIXCALCULATOR_H__

#include <algorithm>
#include <string>
#include <sstream>

#include "MyStack_c747b428.h"
#include "MyVector_c747b428.h"

class MyInfixCalculator
{

public:
    MyInfixCalculator()
    {
    }

    ~MyInfixCalculator()
    {
    }

    double calculate(const std::string &s)
    {
        MyVector<std::string> v;
        MyVector<std::string> post;
        tokenize(s, v);
        infixToPostfix(v, post);
        return calPostfix(post);
    }

private:
    // returns operator precedance; the smaller the number the higher precedence
    // returns -1 if the operator is invalid
    // does not consider parenthesis
    int operatorPrec(const char c) const
    {
        switch (c)
        {
        case '*':
            return 2;
        case '/':
            return 2;
        case '+':
            return 3;
        case '-':
            return 3;
        default:
            return -1;
        }
    }

    // checks if a character corresponds to a valid parenthesis
    bool isValidParenthesis(const char c) const
    {
        switch (c)
        {
        case '(':
            return true;
        case ')':
            return true;
        default:
            return false;
        }
    }

    // checks if a character corresponds to a valid digit
    bool isDigit(const char c) const
    {
        if (c >= '0' && c <= '9')
            return true;
        return false;
    }

    // computes binary operation given the two operands and the operator in their string form
    double computeBinaryOperation(const std::string &ornd1, const std::string &ornd2, const std::string &opt) const
    {
        double o1 = std::stod(ornd1);
        double o2 = std::stod(ornd2);
        switch (opt[0])
        {
        case '+':
            return o1 + o2;
        case '-':
            return o1 - o2;
        case '*':
            return o1 * o2;
        case '/':
            return o1 / o2;
        default:
            std::cout << "Error: unrecognized operator: " << opt << std::endl;
            return 0.0;
        }
    }

    // tokenizes an infix string s into a set of tokens (operands or operators)
    void tokenize(const std::string &s, MyVector<std::string> &tokens)
    {
        std::string temp = "";
        char previous = ' ';
        for (char c : s)
        {
            if(previous == '-' && c == '-' || ((operatorPrec(previous) == 2 || operatorPrec(previous) == 3 || previous == '(') && c == '-')){
                temp += '-';
            }
            else if (previous == ' ' && c == '-'){
                temp += '-';
            }
            else if (operatorPrec(c) == 2 || operatorPrec(c) == 3 || isValidParenthesis(c))
            {
                if (temp != "")
                {
                    tokens.push_back(temp);
                    temp = "";
                }
                tokens.push_back(string(1, c));
            }
            else
            {
                temp += c;
            }
            previous = c;
        }
        tokens.push_back(temp);
    }

    // converts a set of infix tokens to a set of postfix tokens
    void infixToPostfix(MyVector<std::string> &infix_tokens, MyVector<std::string> &postfix_tokens)
    {
        MyStack<std::string> stack;
        for(auto &token : infix_tokens){
            if(token == ""){
                continue;
            }
            else if (token.length() > 1 || isDigit(token[0])){
                postfix_tokens.push_back(token);
            } 
            else{
                if (token[0] == '('){
                    stack.push("(");
                }
                else if (token[0] == ')'){
                    while(stack.top()[0] != '('){
                        postfix_tokens.push_back(stack.top());
                        stack.pop();
                    }
                    stack.pop();
                }
                else {
                    while(!stack.empty() && stack.top()[0] != '(' && (operatorPrec(stack.top()[0]) <= operatorPrec(token[0]))){
                        postfix_tokens.push_back(stack.top());
                        stack.pop();
                    }
                    stack.push(token);
                }
            }
        }
        while (!stack.empty()){
            postfix_tokens.push_back(stack.top());

            stack.pop();
        }
    }

    // calculates the final result from postfix tokens
    double calPostfix(const MyVector<std::string> &postfix_tokens) const
    {
        MyStack<std::string> stack;
        int i = 0;
        for(const std::string &token : postfix_tokens){
            if((token.length() > 1) || isDigit(token[0])){
                stack.push(token);
            }
            else if(token[0] == ' '){
                continue;
            }
            else{
                std::string n1 = stack.top();
                stack.pop(); 
                std::string n2 = stack.top();
                stack.pop();
                double result = computeBinaryOperation(n2, n1, token);
                stack.push(to_string(result));
            }
        }
        return std::stod(stack.top());
    }
};

#endif // __MYINFIXCALCULATOR_H__
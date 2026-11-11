#ifndef __EXPRESSION_H__
#define __EXPRESSION_H__
#include "stack.hpp"
#include "queue.hpp"

class Expression{
    private:
        Queue<char> infixQueue;
        bool isOperator(const char) const;
        bool isOperand(const char) const;
        int getPrecedence(const char) const;
    public:
        Expression();
        void receiveInFixed(const Queue<char>&);
        Queue<char> toPostfixNotation();
        
};
#endif // __EXPRESSION_H__
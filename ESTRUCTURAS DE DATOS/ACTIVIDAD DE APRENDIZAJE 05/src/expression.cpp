#include "expression.hpp"

bool Expression::isOperator(const char c) const{
    return (c == '/' or c == '+' or c == '-' or c == '*' or c == '^');  
}

bool Expression::isOperand(const char c) const{
    return (c >= 'A' and c <= 'Z') or (c >= 'a' and c <= 'z') or (c >= '0' and c <= '9'); 
}

int Expression::getPrecedence(const char c) const{
        if (c == '^') return 3;
        if (c == '*' or c == '/') return 2;
        if (c == '+' or c == '-') return 1;

        return 0;
}

Expression::Expression(){ }

void Expression::receiveInFixed(const Queue<char>& in){
    this->infixQueue = in;
}

Queue<char> Expression::toPostfixNotation(){
    Queue<char> result;
    Stack<char> opStack;
    while(!this->infixQueue.isEmpty()){
        char current = this->infixQueue.dequeue();

        if(isOperand(current)){
            result.enqueue(current);
        }
        else if(current == '('){
            opStack.push(current);
        }
        else if(current == ')'){

            while(!opStack.isEmpty())
                if (opStack.getTop() == '('){
                    opStack.pop();
                    break;

                } else {
                    result.enqueue(opStack.pop());
                }    
        }
        else if(isOperator(current)){
                    while(!opStack.isEmpty() and getPrecedence(opStack.getTop()) >= getPrecedence(current) and opStack.getTop() != '('){
                        result.enqueue(opStack.pop());
                    }
                        opStack.push(current);
             }
        }
        
        while(!opStack.isEmpty()){
            result.enqueue(opStack.pop());
        }

        return result;
}


#ifndef __STACK_H__
#define __STACK_H__

#include <exception>
#include <string>


//Definicion
template <class T, int ARRAYSIZE = 1024>
class Stack{
private:
    T data[ARRAYSIZE];
    int top = -1;

    void copyAll(const Stack<T, ARRAYSIZE>&);

public:

    class Exception : public std::exception {
    private:
        std::string msg;

    public:
        Exception() noexcept : msg("Error indefinido") { }
        Exception(const Exception& ex) noexcept : msg(ex.msg) { }
        Exception(const std::string& m) : msg(m) { }
        Exception& operator=(const Exception& ex) noexcept {
            msg = ex.msg;
            return *this;
        }
        virtual ~Exception() { }
        virtual const char* what() const noexcept {
            return msg.c_str();
        }
};

    Stack();

    Stack(const Stack<T, ARRAYSIZE>&);

    bool isEmpty() const;
    
    bool isFull() const;

    void push(const T&);

    T pop();

    T& getTop();

    Stack<T, ARRAYSIZE>& operator = (const Stack<T, ARRAYSIZE>&);

};

//Implementacion

template<class T, int ARRAYSIZE>
void Stack<T, ARRAYSIZE>::copyAll(const Stack<T, ARRAYSIZE>& other){
    this-> top = other.top;

    int i(0);

    while(i <= this->top){
        this->data[i] = other.data[i];

        i++;
        }
    }

template<class T, int ARRAYSIZE>
Stack<T, ARRAYSIZE>::Stack(){ }

template<class T, int ARRAYSIZE>
Stack<T, ARRAYSIZE>::Stack(const Stack<T, ARRAYSIZE>& other){
    this->copyAll(other);
}

template<class T, int ARRAYSIZE>
bool Stack<T, ARRAYSIZE>::isEmpty() const{
    return this->top == -1;
}

template<class T, int ARRAYSIZE>
bool Stack<T, ARRAYSIZE>::isFull() const{
    return this->top == ARRAYSIZE - 1;
}

template<class T, int ARRAYSIZE>
void Stack<T, ARRAYSIZE>::push(const T& e){
    if(this->isFull()){
        throw Exception("Desbordamiento de datos, push");   
        }
        
        this->top++;

        this->data[this->top] = e;
}

template<class T, int ARRAYSIZE>
T Stack<T, ARRAYSIZE>::pop(){
    if(this->isEmpty()){
        throw Exception("Insuficiencia de datos, pop");
        }

        T result = this->data[this->top];

        this->top--;

        return result;
}

template<class T, int ARRAYSIZE>
T& Stack<T, ARRAYSIZE>::getTop(){
    if(this->isEmpty()) {
        throw Exception("Insuficiencia de datos, getTop");
        }
    
        return this->data[this->top];
    }

template<class T, int ARRAYSIZE>
Stack<T, ARRAYSIZE>& Stack<T, ARRAYSIZE>::operator = (const Stack<T, ARRAYSIZE>& other){
    this->copyAll(other);

    return *this;
}





#endif // __STACK_H__
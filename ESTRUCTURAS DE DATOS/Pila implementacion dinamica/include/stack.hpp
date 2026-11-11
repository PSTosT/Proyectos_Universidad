#ifndef __STACK_H__
#define __STACK_H__

#include <exception>
#include <string>
//*Definicion

template<class T>
class Stack {


// Definicion del tipo Posicion y clase Excepcion.
public:

        //* Clase Excepcion de la pila
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

   

private:
    class Node; //* Forward declaration! (Declaracion adelantada)
    typedef Node* Position;
    //Clase NODO
    class Node{
    private:
        T data;
        Position next = nullptr;
    public:

    Node();

    Node(const T&);

    T& getData();

    void setData(const T&);

    Stack<T>::Position getNext();
    
    void setNext(Stack<T>::Position);
    };

    //Atributos y metodos privados del modelo de la lista

    Position anchor = nullptr;

    void copyAll(const Stack<T>&);
    
    void delAll();

public:

    Stack();

    Stack(const Stack<T>&);
    
    ~Stack();

    Stack<T>& operator = (const Stack<T>&);

    bool isEmpty() const;

    void push(const T&);

    T pop();

    T& getTop();
    
};

//*Implementacion del nodo

template<class T>
Stack<T>::Node::Node() { }

template<class T>
Stack<T>::Node::Node(const T& e) :data(e) { }

template<class T>
T& Stack<T>::Node::getData(){
    return this->data;
}

template<class T>
void Stack<T>::Node::setData(const T& e){
    this->data = e;
}

template<class T>
Stack<T>::Position Stack<T>::Node::getNext(){
    return this->next;
}

template<class T>
void Stack<T>::Node::setNext(Stack<T>::Position p){
    this->next = p;
}

//*Implementacion de la lista

template<class T>
void Stack<T>::copyAll(const Stack<T>& other){
    Position aux(other.anchor), lastInserted(nullptr), newNode;

    while(aux != nullptr){
        lastInserted = this->insNode(lastInserted, aux->getData());

        aux = aux->getNext();
    }
}

template<class T>
void Stack<T>::delAll(){
    Position aux;

    while(this->anchor != nullptr){
        aux = this->anchor;

        this->anchor = aux->getNext();
        delete aux;
    }

}


template<class T>
Stack<T>::Stack(){  }

template<class T>
Stack<T>::Stack(const Stack<T>& other){
    this->copyAll(other);
}

template<class T>
Stack<T>::~Stack(){
    this->delAll();    
}

template<class T>
Stack<T>& Stack<T>::operator = (const Stack<T>& other){
    this->delAll();

    this->copyAll(other);

    return *this;
}

template<class T>
bool Stack<T>::isEmpty() const{
    return this->anchor == nullptr;
}

template<class T>
void Stack<T>::push(const T& e){
    Position newNode;
    try{
        NewNode = new Node(e);
    }catch(const std::bad_alloc& ex){
        throw Exception("Memoria no disponible, push")
    }

    newNode->setNext(this->anchor);

    this->anchor = newNode;
}

template<class T>
T Stack<T>::pop(){
    if(this->isEmpty()){
        throw Exception("Insuficiencia de datos, pop")
    }

    Position aux(this->anchor);
    T result(aux->getData());

    this->anchor = aux->getNext();

    delete aux;

    return result;
}

template<class T>
T& Stack<T>::getTop(){
    if(this->isEmpty()){
        throw Exception("Insuficiencia de datos, getTop")
    }

    return this->anchor->getData();
}

// Stack 
#endif // __STACK_H__
#ifndef __QUEUE_H__
#define __QUEUE_H__
#include <exception>
#include <string>
#include <functional>
#include <sstream>

template<class T>
class Queue {
    class Node; // Declaracion adelantada

public:
    typedef Node* Position;

    // Clase Excepcion de la Queuea
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
    // Clase NODO
    class Node {
    private:
        T* dataPtr = nullptr;
        Position next = nullptr;
        Position prev = nullptr;

    public:
        class Exception : public Queue<T>::Exception {
        public:
            using Queue<T>::Exception::Exception;
        };

        Node();
        Node(const T&);
        ~Node(); 

        T* getDataPtr();
        T& getData();
        void setDataPtr(T*);
        void setData(const T&);

        Queue<T>::Position getNext();
        void setNext(Queue<T>::Position);

        Queue<T>::Position getPrev();
        void setPrev(Queue<T>::Position);
    };

    Position header = nullptr; 

    void copyAll(const Queue<T>&);

    void delAll();

public:

    Queue();
    Queue(const Queue<T>&);
    ~Queue();

    Queue<T>& operator=(const Queue<T>&);

    bool isEmpty() const;

    void enqueue(const T&);

    T dequeue();

    T& getFront();
};

//Implementacion del nodo!! 

template<class T>
Queue<T>::Node::Node() { } 
template<class T>
Queue<T>::Node::Node(const T& e) : dataPtr(new(std::nothrow) T(e)) { 
    if(this->dataPtr == nullptr){
        throw Exception("Memoria no disponible, Node");
    }
}

template<class T>
Queue<T>::Node::~Node() {
    delete this->dataPtr;
}

template<class T>
T* Queue<T>::Node::getDataPtr() {
    return this->dataPtr;
}

template<class T>
T& Queue<T>::Node::getData() {
    if(this->dataPtr == nullptr) {
        throw Exception("Dato inexistente");
    }
    return *this->dataPtr;
}

template<class T>
void Queue<T>::Node::setDataPtr(T* p) { 
    this->dataPtr = p;
}

template<class T>
void Queue<T>::Node::setData(const T& e) {
    if(this->dataPtr == nullptr) {
        try {
            this->dataPtr = new T(e);
        } catch (const std::bad_alloc& ex) {
            throw Exception("Memoria insuficiente");
        }
        return;
    }
    *this->dataPtr = e;
}

template<class T>
typename Queue<T>::Position Queue<T>::Node::getNext() {
    return this->next;
}

template<class T>
void Queue<T>::Node::setNext(Queue<T>::Position p) {
    this->next = p;
}

template<class T>
typename Queue<T>::Position Queue<T>::Node::getPrev() {
    return this->prev;
}

template<class T>
void Queue<T>::Node::setPrev(Queue<T>::Position p) {
    this->prev = p;
}

//Implementacion de la cola

template<class T>
void Queue<T>::copyAll(const Queue<T>& other) {
    Position aux(other.header->getNext()), newNode;
    while(aux != other.header) {
        try{
            newNode = new Node(aux->getData());
        } catch (const std::bad_alloc& ex){
            throw Exception("Memoria no disponible, copyAll");
        }

    newNode->setPrev(this->header->getPrev());
    newNode->setNext(this->header);

    this->header->getPrev()->setNext(newNode);
    this->header->setPrev(newNode);

    aux = aux->getNext();
    }
}

template<class T>
Queue<T>::Queue() : header(new(std::nothrow) Node) { 
    if(this->header == nullptr) {
        throw Exception("Memoria no disponible, Queue");
    }
    
    this->header->setPrev(this->header); 
    this->header->setNext(this->header); 
}

template<class T>
Queue<T>::Queue(const Queue<T>& other) : Queue() { 
    this->copyAll(other);
}

template<class T>
Queue<T>::~Queue() {
    this->delAll();    
    delete this->header; 
}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other) {
    this->delAll();
    this->copyAll(other);
    return *this;
}

template<class T>
bool Queue<T>::isEmpty() const {
    return this->header->getNext() == this->header; 
}

template<class T>
void Queue<T>::delAll() {
    Position aux(this->header->getNext());
    Position toDelete;

    while(aux != this->header){
        toDelete = aux;
        aux = aux->getNext();
        delete toDelete;
    }
    
    this->header->setNext(this->header);
    this->header->setPrev(this->header);
}

template<class T>
void Queue<T>::enqueue(const T& e){
    Position newNode;

    try{
        newNode = new Node(e);
    } catch (const std::bad_alloc& ex) {
        throw Exception("Memoria no disponible, enqueue");
    }

    newNode -> setPrev(this->header->getPrev());
    newNode-> setNext(this->header);

    this->header->getPrev()->setNext(newNode);
    this->header->setPrev(newNode);
}

template<class T>
T Queue<T>::dequeue(){
    if(this->isEmpty()){
        throw Exception("Insuficiencia de datos, dequeue");
    }

    Position aux(this->header->getNext());
    T result(aux->getData());

    aux->getPrev()->setNext(aux->getNext());
    aux->getNext()->setPrev(aux->getPrev());

    delete aux;
    return result;
}

template<class T>
T& Queue<T>::getFront(){
    if(this->isEmpty()){
        throw Exception("Insuficiencia de datos, getfront");
    }

    return this->header->getNext()->getData();
}


#endif // __QUEUE_H__
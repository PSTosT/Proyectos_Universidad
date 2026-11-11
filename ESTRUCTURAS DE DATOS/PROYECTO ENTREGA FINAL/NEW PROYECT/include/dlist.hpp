#ifndef __DLIST_H__
#define __DLIST_H__

#include <exception>
#include <string>
#include <functional>
#include <sstream>

template<class T>
class DList {
    class Node; // Declaracion adelantada

public:
    typedef Node* Position;

    // Clase Excepcion de la lista
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
        class Exception : public DList<T>::Exception {
        public:
            using DList<T>::Exception::Exception;
        };

        Node();
        Node(const T&);
        ~Node(); 

        T* getDataPtr();
        T& getData();
        void setDataPtr(T*);
        void setData(const T&);

        DList<T>::Position getNext();
        void setNext(DList<T>::Position);

        DList<T>::Position getPrev();
        void setPrev(DList<T>::Position);
    };

    Position header = nullptr; 

    bool isValidPos(const Position&) const;
    void copyAll(const DList<T>&);

public:
    DList();
    DList(const DList<T>&);
    ~DList();

    DList<T>& operator=(const DList<T>&);

    bool isEmpty() const;
    
    bool insData(const DList<T>::Position&, const T&);
    bool delData(const DList<T>::Position&);
    
    DList<T>::Position getFirstPos() const;
    DList<T>::Position getLastPos() const;
    DList<T>::Position getPrevPos(const DList<T>::Position&) const;
    DList<T>::Position getNextPos(const DList<T>::Position&) const;
    
    DList<T>::Position findDataL(const T&) const;
    DList<T>::Position findDataL(const T&, const std::function<int(const T&, const T&)>&) const;

    T& retrieve(const DList<T>::Position&) const;
    std::string toString() const;
    void delAll();

    template <class X>
    friend std::istream& operator>>(std::istream&, DList<X>&);

    template <class X>
    friend std::ostream& operator<<(std::ostream&, const DList<X>&);
};

//* Implementacion del nodo

template<class T>
DList<T>::Node::Node() { } 
template<class T>
DList<T>::Node::Node(const T& e) : dataPtr(new(std::nothrow) T(e)) { 
    if(this->dataPtr == nullptr){
        throw Exception("Memoria no disponible, Node");
    }
}

template<class T>
DList<T>::Node::~Node() {
    delete this->dataPtr;
}

template<class T>
T* DList<T>::Node::getDataPtr() {
    return this->dataPtr;
}

template<class T>
T& DList<T>::Node::getData() {
    if(this->dataPtr == nullptr) {
        throw Exception("Dato inexistente");
    }
    return *this->dataPtr;
}

template<class T>
void DList<T>::Node::setDataPtr(T* p) { 
    this->dataPtr = p;
}

template<class T>
void DList<T>::Node::setData(const T& e) {
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
typename DList<T>::Position DList<T>::Node::getNext() {
    return this->next;
}

template<class T>
void DList<T>::Node::setNext(DList<T>::Position p) {
    this->next = p;
}

template<class T>
typename DList<T>::Position DList<T>::Node::getPrev() {
    return this->prev;
}

template<class T>
void DList<T>::Node::setPrev(DList<T>::Position p) {
    this->prev = p;
}

//* Implementacion de la lista

template<class T>
bool DList<T>::isValidPos(const Position& p) const {
    Position aux(this->header->getNext()); 
    while (aux != this->header) { 
        if(aux == p){
            return true;
        }
        aux = aux->getNext();
    }
    return false;
}

template<class T>
void DList<T>::copyAll(const DList<T>& other) {
    Position aux(other.header->getNext());
    while(aux != other.header) {
        this->insData(this->getLastPos(), aux->getData());
        aux = aux->getNext();
    }
}

template<class T>
DList<T>::DList() : header(new(std::nothrow) Node) { 
    if(this->header == nullptr) {
        throw Exception("Memoria no disponible, DList");
    }
    
    this->header->setPrev(this->header); 
    this->header->setNext(this->header); 
}

template<class T>
DList<T>::DList(const DList<T>& other) : DList() { 
    this->copyAll(other);
}

template<class T>
DList<T>::~DList() {
    this->delAll();    
    delete this->header; 
}

template<class T>
DList<T>& DList<T>::operator=(const DList<T>& other) {
    this->delAll();
    this->copyAll(other);
    return *this;
}

template<class T>
bool DList<T>::isEmpty() const {
    return this->header->getNext() == this->header; 
}

template<class T>
bool DList<T>::insData(const DList<T>::Position& p, const T& e) {
    if(p != nullptr and !this->isValidPos(p)){
        throw DList<T>::Exception("Posicion invalida, insData");
    }
    try {
        Position insPos(p == nullptr ? this->header : p); 
        Position newNode(new Node(e));

        newNode->setPrev(insPos); 
        newNode->setNext(insPos->getNext()); 

        insPos->getNext()->setPrev(newNode);
        insPos->setNext(newNode);
        
        return true;
    } catch(const std::bad_alloc& ex) {
        throw Exception("Memoria no disponible, insData"); 
    }
}

template<class T>
bool DList<T>::delData(const DList<T>::Position& p) {
    if(this->isValidPos(p)) {
        // Puenteamos el nodo a eliminar
        p->getPrev()->setNext(p->getNext());
        p->getNext()->setPrev(p->getPrev());
        
        delete p;
        return true;
    } else {
        throw Exception("Posicion invalida, delData");
    }    
}

template<class T>
typename DList<T>::Position DList<T>::getFirstPos() const {
    return this->isEmpty() ? nullptr : this->header->getNext(); 
}

template<class T>
typename DList<T>::Position DList<T>::getLastPos() const {
    return this->isEmpty() ? nullptr : this->header->getPrev(); 
}

template<class T>
typename DList<T>::Position DList<T>::getPrevPos(const DList<T>::Position& p) const { 
    return (this->isValidPos(p) && p->getPrev() != this->header) ? p->getPrev() : nullptr;
}

template<class T>
typename DList<T>::Position DList<T>::getNextPos(const DList<T>::Position& p) const {
    return (this->isValidPos(p) && p->getNext() != this->header) ? p->getNext() : nullptr;
}

template<class T>
typename DList<T>::Position DList<T>::findDataL(const T& e) const {
    Position aux(this->header->getNext()); 
    
    while(aux != this->header and aux->getData() != e){
        aux = aux->getNext();
    }
    return aux == this->header ? nullptr : aux; 
}

template<class T>
typename DList<T>::Position DList<T>::findDataL(const T& e, const std::function<int(const T&, const T&)>& cmp) const {
    Position aux(this->header->getNext());
    
    while(aux != this->header and cmp(aux->getData(), e) != 0){
        aux = aux->getNext();
    }
    return aux == this->header ? nullptr : aux;
}

template<class T>
T& DList<T>::retrieve(const DList<T>::Position& p) const {
    if(this->isValidPos(p)){
        return p->getData();
    }
    throw Exception("Posicion invalida, retrieve");
}

template<class T>
std::string DList<T>::toString() const {
    std::string result;
    Position aux(this->header->getNext());

    while(aux != this->header){
        result += aux->getData().toString() + "\n";
        aux = aux->getNext();
    }
    return result;
}

template<class T>
void DList<T>::delAll() {
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

template<class X>
std::ostream& operator<<(std::ostream& os, const DList<X>& l) {
    typename DList<X>::Position pos = l.getFirstPos();
    while (pos != nullptr) {
        os << l.retrieve(pos) << std::endl;
        pos = l.getNextPos(pos);
    }
    return os;
}

template<class X>
std::istream& operator>>(std::istream& is, DList<X>& l) {
    X myObj;
    while (is >> myObj) {
        l.insData(l.getLastPos(), myObj); 
    }
    return is;
}

#endif // __DLIST_H__
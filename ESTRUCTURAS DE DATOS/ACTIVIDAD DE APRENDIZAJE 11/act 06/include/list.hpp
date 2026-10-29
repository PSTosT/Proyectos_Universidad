#ifndef __LIST_H__
#define __LIST_H__
#include <exception>
#include <string>
#include <functional>
#include <string>
#include <sstream>
//*Definicion

template<class T>
class List {
class Node; //* Forward declaration! (Declaracion adelantada)

// Definicion del tipo Posicion y clase Excepcion.
public:
    typedef Node* Position;

        //* Clase Excepcion de la lista
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
    
    //Clase NODO
    class Node{
    private:
        T data;
        Position next = nullptr;
        Position prev = nullptr;
    public:

    Node();

    Node(const T&);

    T& getData();

    void setData(const T&);

    List<T>::Position getNext();
    
    void setNext(List<T>::Position);

    List<T>::Position getPrev();
    
    void setPrev(List<T>::Position);
    };
    

    //Atributos y metodos privados del modelo de la lista

    Position anchor = nullptr;

    bool isValidPos(const Position&) const;

    void copyAll(const List<T>&);

public:

    List();

    List(const List<T>&);
    
    ~List();

    List<T>& operator = (const List<T>&);

    bool isEmpty() const;
    
    bool insData(const List<T>::Position&, const T&);

    bool delData(const List<T>::Position&);
    
    List<T>::Position getFirstPos() const;

    List<T>::Position getLastPos() const;

    List<T>::Position getPrevPos(const List<T>::Position&) const;

    List<T>::Position getNextPos(const List<T>::Position&) const;
    
    List<T>::Position findDataL(const T&) const;
    List<T>::Position findDataL(const T&, const std::function<int(const T&, const T&)>&) const;

    T& retrieve(const List<T>::Position&) const;

    std::string toString() const;
    
    void delAll();

    template <class X>
    friend std::istream& operator>>(std::istream&, List<X>&);

    template <class X>
    friend std::ostream& operator<<(std::ostream&, const List<X>&);
/*
    bool insertOrdered(const T&);

    std::string serialize(const char& delim = '*') const;
    void deserialize(const std::string&, const char& delim = '*');
    */
};

//*Implementacion del nodo

template<class T>
List<T>::Node::Node() { }

template<class T>
List<T>::Node::Node(const T& e) :data(e) { }

template<class T>
T& List<T>::Node::getData(){
    return this->data;
}

template<class T>
void List<T>::Node::setData(const T& e){
    this->data = e;
}

template<class T>
typename List<T>::Position List<T>::Node::getNext(){
    return this->next;
}

template<class T>
void List<T>::Node::setNext(List<T>::Position p){
    this->next = p;
}

template<class T>
typename List<T>::Position List<T>::Node::getPrev(){
    return this->prev;
}

template<class T>
void List<T>::Node::setPrev(List<T>::Position p){
    this->prev = p;
}

//*Implementacion de la lista

template<class T>
bool List<T>::isValidPos(const Position& p) const{
    Position aux(this->anchor);

    while (aux != nullptr) {
        if(aux == p){
            return true;
        }
        aux = aux->getNext();
    }
    return false;
}

template<class T>
void List<T>::copyAll(const List<T>& other){
    Position aux(other.anchor), lastInserted(nullptr), newNode;

    while(aux != nullptr){
        try{
            newNode = new Node(aux -> getData());
        } catch (const std::bad_alloc& ex){
            throw Exception("Memoria no disponible, copyAll");
        }

        if(lastInserted == nullptr){
            this->anchor = newNode;
        } else {
            lastInserted->setNext(newNode);
        }
        newNode->setPrev(lastInserted);

        lastInserted = newNode;

        aux = aux->getNext();
    }
}

template<class T>
List<T>::List(){
    
}

template<class T>
List<T>::List(const List<T>& other){
    this->copyAll(other);
}

template<class T>
List<T>::~List(){
    this->delAll();    
}

template<class T>
List<T>& List<T>::operator = (const List<T>& other){
    this->delAll();

    this->copyAll(other);

    return *this;
}

template<class T>
bool List<T>::isEmpty() const{
    return this->anchor == nullptr;
}

template<class T>
bool List<T>::insData(const List<T>::Position& p, const T& e){
    if(p != nullptr and !this->isValidPos(p)){
        throw List<T>::Exception("Posicion invalida, insData");
    }
    try{
        Position newNode (new Node(e));

        if(p == nullptr) { //Insertar al principio
            newNode->setPrev(nullptr);
            newNode->setNext(this->anchor);

            if(this->anchor != nullptr){
                this->anchor->setPrev(newNode);
            }

            this->anchor = newNode;
        }
        else{
            newNode->setPrev(p);
            newNode->setNext(p->getNext());

            if(p->getNext() != nullptr){
                p->getNext()->setPrev(newNode);
            }

            p->setNext(newNode);
        }
        return true;

    } catch(const std::bad_alloc& ex) {
        throw Exception("Memoria no disponible, insData");
    }
}

template<class T>
bool List<T>::delData(const List<T>::Position& p){
    if(this->isValidPos(p)){
        if(p->getPrev() != nullptr){
            p->getPrev()->setNext(p->getNext());
        }
        if(p->getNext() != nullptr) {
            p->getNext()->setPrev(p->getPrev());
        }
        if(p == this->anchor){
            this->anchor = p->getNext();
        }

        delete p;

        return true;
    }
    else {
        throw Exception("Posicion invalida, delData");
    }    
}

template<class T>
typename List<T>::Position List<T>::getFirstPos() const{
    return this->anchor;
}

template<class T>
typename List<T>::Position List<T>::getLastPos() const{
    if(this->isEmpty()){
        return nullptr;
    }

    Position aux(this->anchor);

    while(aux->getNext() != nullptr){
        aux = aux->getNext();
    }
    return aux;
}

template<class T>
typename List<T>::Position List<T>::getPrevPos(const List<T>::Position& p) const{ 
    return this->isValidPos(p) ? p->getPrev() : nullptr;
}

template<class T>
typename List<T>::Position List<T>::getNextPos(const List<T>::Position& p) const{
    return this->isValidPos(p) ? p->getNext() : nullptr;
}

template<class T>
typename List<T>::Position List<T>::findDataL(const T& e) const{
    Position aux(this->anchor);
    
    while(aux != nullptr and aux->getData() != e){
        aux = aux->getNext();
    }
    return aux;
}

template<class T>
typename List<T>::Position List<T>::findDataL(const T& e, const std::function<int(const T&, const T&)>& cmp) const{
    Position aux(this->anchor);
    
    while(aux != nullptr and cmp(aux->getData(), e) != 0){
        aux = aux->getNext();
    }
    return aux;
}

template<class T>
T& List<T>::retrieve(const List<T>::Position& p) const{
    if(this->isValidPos(p)){
        return p->getData();
    }

    throw Exception("Posicion invalida, retrieve");
    
    
}

template<class T>
std::string List<T>::toString() const{
    std::string result;

    Position aux(this->anchor);

    while(aux != nullptr){
        result += aux->getData().toString() + "\n";

        aux = aux->getNext();
    }

    return result;
}

template<class T>
void List<T>::delAll(){
    Position aux;

    while(this->anchor != nullptr){
        aux = this->anchor;

        this->anchor = aux->getNext();
        delete aux;
    }

}

template<class X>
std::ostream& operator<<(std::ostream& os, const List<X>& l){
    typename List<X>::Position pos = l.getFirstPos();
    while (pos != nullptr) {
        os << l.retrieve(pos) << std::endl;
        pos = l.getNextPos(pos);
    }
    return os;
}

template<class X>
std::istream& operator>>(std::istream& is, List<X>& l){
    X myObj;
    while (is >> myObj) {
        l.insData(l.getLastPos(), myObj); 
    }
    return is;
}


// List 
#endif // __LIST_H__
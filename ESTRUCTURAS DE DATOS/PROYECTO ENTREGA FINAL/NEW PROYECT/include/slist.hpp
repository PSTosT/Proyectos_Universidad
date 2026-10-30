#ifndef __SLIST_H__
#define __SLIST_H__
#include <exception>
#include <string>
#include <functional>
#include <string>
#include <sstream>
//*Definicion

template<class T>
class SList {
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
    public:

    Node();

    Node(const T&);

    T& getData();

    void setData(const T&);

    SList<T>::Position getNext();
    
    void setNext(SList<T>::Position);
    };

    //Atributos y metodos privados del modelo de la lista

    Position anchor = nullptr;

    bool isValidPos(const Position&) const;

    void copyAll(const SList<T>&);

    const Position insNode (const Position&, const T&);

public:

    SList();

    SList(const SList<T>&);
    
    ~SList();

    SList<T>& operator = (const SList<T>&);

    bool isEmpty() const;
    
    bool insData(const SList<T>::Position&, const T&);

    bool insertOrdered(const T&);

    bool delData(const SList<T>::Position&);
    
    SList<T>::Position getFirstPos() const;

    SList<T>::Position getLastPos() const;

    SList<T>::Position getPrevPos(const SList<T>::Position&) const;

    SList<T>::Position getNextPos(const SList<T>::Position&) const;
    
    SList<T>::Position findDataL(const T&) const;
    SList<T>::Position findDataL(const T&, const std::function<int(const T&, const T&)>&) const;

    T& retrieve(const SList<T>::Position&) const;

    std::string toString() const;
    
    void delAll();

    template <class X>
    friend std::istream& operator>>(std::istream&, SList<X>&);

    template <class X>
    friend std::ostream& operator<<(std::ostream&, const SList<X>&);

    std::string serialize(const char& delim = '*') const;
    void deserialize(const std::string&, const char& delim = '*');
    
};

//*Implementacion del nodo

template<class T>
SList<T>::Node::Node() { }

template<class T>
SList<T>::Node::Node(const T& e) :data(e) { }

template<class T>
T& SList<T>::Node::getData(){
    return this->data;
}

template<class T>
void SList<T>::Node::setData(const T& e){
    this->data = e;
}

template<class T>
SList<T>::Position SList<T>::Node::getNext(){
    return this->next;
}

template<class T>
void SList<T>::Node::setNext(SList<T>::Position p){
    this->next = p;
}

//*Implementacion de la lista

template<class T>
bool SList<T>::isValidPos(const Position& p) const{
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
void SList<T>::copyAll(const SList<T>& other){
    Position aux(other.anchor), lastInserted(nullptr), newNode;

    while(aux != nullptr){
        lastInserted = this->insNode(lastInserted, aux->getData());

        aux = aux->getNext();
    }
}

template<class T>
const SList<T>::Position SList<T>::insNode (const Position& p, const T& e){
    Position newNode;

    try{
        newNode= new Node(e);

        if(p == nullptr) { //Insertar al principio
            newNode->setNext(this->anchor);
            this->anchor = newNode;
        }
        else{
            newNode->setNext(p->getNext());
            p->setNext(newNode);
        }

        return newNode;

    } catch(const std::bad_alloc& ex) {
        throw Exception("Memoria no disponible, insData");
    }
}

template<class T>
SList<T>::SList(){
    
}

template<class T>
SList<T>::SList(const SList<T>& other){
    this->copyAll(other);
}

template<class T>
SList<T>::~SList(){
    this->delAll();    
}

template<class T>
SList<T>& SList<T>::operator = (const SList<T>& other){
    this->delAll();

    this->copyAll(other);

    return *this;
}

template<class T>
bool SList<T>::isEmpty() const{
    return this->anchor == nullptr;
}

template<class T>
bool SList<T>::insData(const SList<T>::Position& p, const T& e){
    if(p != nullptr and !this->isValidPos(p)){
        throw SList<T>::Exception("Posicion invalida, insData");
    }
    this->insNode(p,e);

    return true;
}
template<class T>
bool SList<T>::insertOrdered(const T& e){
    Position aux(this->anchor), pos(nullptr);

    while(aux != nullptr and e > aux->getData()) {
        pos = aux;

        aux = aux->getNext();
    }

    this->insNode(pos, e);

    return true;
}

template<class T>
bool SList<T>::delData(const SList<T>::Position& p){
    if(this->isValidPos(p)){
        if(p == this->anchor){ // El primero
        this->anchor = p->getNext();
        } else {
            this->getPrevPos(p)->setNext(p->getNext());
        }

        delete p;

        return true;
    }
    else {
        throw Exception("Posicion invalida, delData");
    }    
}

template<class T>
typename SList<T>::Position SList<T>::getFirstPos() const{
    return this->anchor;
}

template<class T>
typename SList<T>::Position SList<T>::getLastPos() const{
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
typename SList<T>::Position SList<T>::getPrevPos(const SList<T>::Position& p) const{ 
    Position aux(this->anchor);

    while(aux != nullptr and aux->getNext() != p){
        aux = aux->getNext();
    }
    return aux;
}

template<class T>
typename SList<T>::Position SList<T>::getNextPos(const SList<T>::Position& p) const{
    return this->isValidPos(p) ? p->getNext() : nullptr;
}

template<class T>
typename SList<T>::Position SList<T>::findDataL(const T& e) const{
    Position aux(this->anchor);
    
    while(aux != nullptr and aux->getData() != e){
        aux = aux->getNext();
    }
    return aux;
}

template<class T>
typename SList<T>::Position SList<T>::findDataL(const T& e, const std::function<int(const T&, const T&)>& cmp) const{
    Position aux(this->anchor);
    
    while(aux != nullptr and cmp(aux->getData(), e) != 0){
        aux = aux->getNext();
    }
    return aux;
}

template<class T>
T& SList<T>::retrieve(const SList<T>::Position& p) const{
    if(this->isValidPos(p)){
        return p->getData();
    }

    throw Exception("Posicion invalida, retrieve");
    
    
}

template<class T>
std::string SList<T>::toString() const{
    std::string result;

    Position aux(this->anchor);

    while(aux != nullptr){
        result += aux->getData().toString() + "\n";

        aux = aux->getNext();
    }

    return result;
}

template<class T>
void SList<T>::delAll(){
    Position aux;

    while(this->anchor != nullptr){
        aux = this->anchor;

        this->anchor = aux->getNext();
        delete aux;
    }

}

template<class X>
std::ostream& operator<<(std::ostream& os, const SList<X>& l){
    typename SList<X>::Position pos = l.getFirstPos();
    while (pos != nullptr) {
        os << l.retrieve(pos) << std::endl;
        pos = l.getNextPos(pos);
    }
    return os;
}

template<class X>
std::istream& operator>>(std::istream& is, SList<X>& l){
    X myObj;
    while (is >> myObj) {
        l.insData(l.getLastPos(), myObj); 
    }
    return is;
}
template<class T>
std::string SList<T>::serialize(const char& delim) const{
    std::string result;
    Position pos(this->anchor);

        while(pos != nullptr){
            result+= pos->getData().serialize() + delim;

            pos = pos->getNext;
            }
        return result;
}

template<class T>
void SList<T>::deserialize(const std::string& str, const char& delim){
    std::stringstream mySStream(str);
    std::string myStr;
    T myObj;

    this->delAll();
    Position lastInserted(nullptr);

    while(!mySStream.eof()) {
        getline(mySStream, myStr, delim);
        
        if(myStr.empty()){
            continue;
            }
        myObj.deserialize(myStr);

        lastInserted = this->insNode(lastInserted, myObj);
    }
}

// SList 
#endif // __LIST_H__
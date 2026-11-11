#ifndef __BTREE_H__
#define __BTREE_H__

#include <exception>
#include <string>
#include <functional>
#include <sstream>

template<class T>
class BTree {
class Node;


public:
    typedef Node* Position;

    // Clase Excepcion de la BTreea
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
        Position left = nullptr;
        Position right = nullptr;

    public:
        class Exception : public BTree<T>::Exception {
        public:
            using BTree<T>::Exception::Exception;
        };

        Node();
        Node(const T&);

        ~Node(); 

        T* getDataPtr();
        T& getData();
        void setDataPtr(T*);
        void setData(const T&);

        BTree<T>::Position& getLeft();
        void setLeft(BTree<T>::Position&);

        BTree<T>::Position& getRight();
        void setRight(BTree<T>::Position&);
    };
    Position root = nullptr;

    void copyAll(const BTree<T>::Position&, BTree<T>::Position&);

    void delAll(BTree<T>::Position&);

    void add(BTree<T>::Position&, const T&);

    void del(BTree<T>::Position&, const T&);

    BTree<T>::Position& find(const BTree<T>::Position&, const T&);

    BTree<T>::Position& getLowest(const BTree<T>::Position&);

    BTree<T>::Position& getHighest(const BTree<T>::Position&);

    unsigned getHeight(const BTree<T>::Position&);
    BTree<T>::Position& find(const BTree<T>::Position&, const T&);

    void parsePreorder(const BTree<T>::Position&);
    void parseInorder(const BTree<T>::Position&);
    void parsePostorder(const BTree<T>::Position&);

public:
    BTree();

    BTree(const BTree&);

    ~BTree();

    bool isEmpty() const;

    void add(const T&);

    void del(const T&);

    void delAll();

    bool isLeaf(const BTree<T>::Position&) const;

    BTree<T>::Position& getLowest();

    BTree<T>::Position& getHighest();

    unsigned getHeight();

    BTree<T>& operator = (const BTree<T>&);

    BTree<T>::Position& find(const T&);

    T& retrieve(const BTree<T>::Position&);

    std::string toString();

    void parsePreorder();
    void parseInorder();
    void parsePostorder();

};

template<class T>
BTree<T>::Node::Node() { } 
template<class T>
BTree<T>::Node::Node(const T& e) : dataPtr(new(std::nothrow) T(e)) { 
    if(this->dataPtr == nullptr){
        throw Exception("Memoria no disponible, Node");
    }
}

template<class T>
BTree<T>::Node::~Node() {
    delete this->dataPtr;
}

template<class T>
T* BTree<T>::Node::getDataPtr() {
    return this->dataPtr;
}

template<class T>
T& BTree<T>::Node::getData() {
    if(this->dataPtr == nullptr) {
        throw Exception("Dato inexistente");
    }
    return *this->dataPtr;
}

template<class T>
void BTree<T>::Node::setDataPtr(T* p) { 
    this->dataPtr = p;
}

template<class T>
void BTree<T>::Node::setData(const T& e) {
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
typename BTree<T>::Position& BTree<T>::Node::getLeft() {
    return this->left;
}

template<class T>
void BTree<T>::Node::setLeft(BTree<T>::Position& p) {
    this->left = p;
}

template<class T>
typename BTree<T>::Position& BTree<T>::Node::getRight() {
    return this->right;
}

template<class T>
void BTree<T>::Node::setRight(BTree<T>::Position& p) {
    this->right = p;
}

//Implementacion del arbol binario

//Hacer el copyAll
template<class T>
BTree<T>::BTree(){

}


template<class T>
void BTree<T>::add(BTree<T>::Position& r, const T& e){
    if(r == nullptr){
        try{
            r = new Node(e);
        } catch (const std::bad_alloc& ex) {
            throw Exception("Memoria no disponible, add");
        }

        return;
    }

    this->add(e < r->getData() ? r->getLeft() : r->getRight(), e)

    //Aqui regresa de la recursividad
}

template<class T>
void BTree<T>::del(BTree<T>::Position& r, const T& e){
    if(r == nullptr){
        return;
    }
    if(e == r->getData()){
        if(this->isLeaf(r)){ //Hoja
            delete r;

            r = nullptr;

            return;
        }

        if(r->getLeft() != nullptr and r->getRight != nullptr ){ //Cuando tiene dos hijos
            r->setData(this->getHighest(r->getLeft())->getData());

            this->del(r->getLeft(), r->getData());

            //Sale del ultimo llamado

            return;
        }

    Position aux(r);

    r = r->getLeft() == nullptr ? r->getRight() : r->getLeft();

    }

    this->del(e < r->getData() ? r->getLeft() : r->getRight(), e);

    //Sale de la recursividad
    
}

template<class T>
typename BTree<T>::Position& BTree<T>::getLowest(const Position& r){
    return (r == nullptr or r->getLeft() != nullptr) ? r : this->getLowest(r->getLeft());

}

template<class T>
typename BTree<T>::Position& BTree<T>::getHighest(const Position& r){
    return (r == nullptr or r->getRight() != nullptr) ? r : this->getHighest(r->getRight());

}

template<class T>
unsigned BTree<T>::getHeight(const Position& r){
    if(r == nullptr){
        return 0;
    }

    unsigned leftHeight(this->getHeight(r->getLeft()));
    unsigned rightHeight(this->getHeight(r->getRight()));

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

template<class T>
typename BTree<T>::Position& BTree<T>::find(const BTree<T>::Position& r, const T& e){
    if(r == nullptr or r->getData() == e){
        return r;
    }

    return this->find(e < r->getData() ? r->getLeft() : r->getRight(), e)

}

template<class T>
void BTree<T>::delAll(Position& r){
    //Pendiente
}
template<class T>
void BTree<T>::parsePreorder(){
    this->parsePreorder(this->root);
}

template<class T>
void BTree<T>::parsePreorder(const BTree<T>::Position& r){
    if(r == nullptr){
        return;
    }

    std::cout << r->getData().toString() << ", ";
    this->parsePreorder(r->getLeft());
    this->parsePreorder(r->getRight());
}

template<class T>
void BTree<T>::parseInorder(){
    this->parseInorder(this->root);
}

template<class T>
void BTree<T>::parseInorder(const BTree<T>::Position&){
    if(r==nullptr){
        return;
    }

    this->parseInorder(r->getLeft());
    std::cout << r->getData().toString() << ", ";
    this->parseInorder(r->getRight());
    
}

template<class T>
void BTree<T>::parsePostorder(){
    this->parsePostorder(this->root);
}

template<class T>
void BTree<T>::parsePostorder(const BTree<T>::Position&){
    if(r == nullptr){
        return;
    }

    this->parsePostorder(r->getLeft());
    this->parsePostorder(r->getRight());
    std::cout << r->getData().toString() << ", ";
}

//parte publica

template<class T>
BTree<T>::BTree(const BTree& other){
    this->copyAll(other.root, this->root);
}

template<class T>
BTree<T>::~BTree(){
    this->delAll();
}

template<class T>
bool BTree<T>::isEmpty() const{
    return this->root == nullptr;
}

template<class T>
void BTree<T>::add(const T& e){
    this->add(this->root, e);
}

template<class T>
void BTree<T>::del(const T& e){
    this->del(this->root, e);
}

template<class T>
void BTree<T>::delAll(){
    thos->delAll(this->root);
}

template<class T>
bool BTree<T>::isLeaf(const BTree<T>::Position&) const{
    return r->getLeft() == r->getRight();
}

template<class T>
typename BTree<T>::Position& getLowest(){
    return this->getLowest(this->root);
}

template<class T>
typename BTree<T>::Position& getHighest(){
    return this->getHighest(this->root);
}

template<class T>
unsigned BTree<T>::getHeight(){
    return this->getHeight(this->root);
}

template<class T>
BTree<T>& BTree<T>::operator = (const BTree<T>&){
    this->delAll();

    this->copyAll(other.root, this->root);

    return *this;
}

template<class T>
typename BTree<T>::Position& BTree<T>::find(const T& e){
    return this->find(this->root);
}

template<class T>
T& BTree<T>::retrieve(const BTree<T>::Position&){
    
}

std::string toString(){
    //Pendiente
}

#endif // __BTREE_H__
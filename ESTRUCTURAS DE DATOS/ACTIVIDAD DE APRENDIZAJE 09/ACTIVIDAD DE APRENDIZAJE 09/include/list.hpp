#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <functional>

// Definicion

template <class T, int ARRAYSIZE>
class List {
private:
    T** data = nullptr;
    int last = -1;

    bool isValidPos(const int& p) const;
    void copyAll(const List&);

    void swapData(T& a, T& b);

    // Metodos recursivos (reciben limites del arreglo)
    void sortDataMerge(const int&, const int&);
    void sortDataMerge(const int&, const int&, const std::function<int(const T&, const T&)>& cmp);
    void sortDataQuick(const int&, const int&);
    void sortDataQuick(const int&, const int&, const std::function<int(const T&, const T&)>& cmp);

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

    List();
    List(const List&);
    ~List(); 


    bool isEmpty() const;
    bool isFull() const;
    
    bool isSorted() const;
    bool isSorted(const std::function<int(const T&, const T&)>& cmp) const;

    bool insData(const int& p, const T& e);
    bool delData(const int& p);
    
    int getFirstPos() const;
    int getLastPos() const;

    int findData(const T&) const;
    T& retrieve(const int&);
    std::string toString() const;
    void delAll();
    List& operator = (const List&);

    template <class X, int Y>
    friend std::istream& operator>>(std::istream&, List<X, Y>&);

    template <class X, int Y>
    friend std::ostream& operator<<(std::ostream&, const List<X, Y>&);

    bool insertOrdered(const T&);

    int findDataL(const T& e) const;
    int findDataL(const T& e, const std::function<int(const T&, const T&)>& cmp) const;

    int findDataB(const T& e) const;
    int findDataB(const T& e, const std::function<int(const T&, const T&)>& cmp) const;

    void sortDataQuick();
    void sortDataQuick(const std::function<int(const T&, const T&)>& cmp);

    //Serializacion y deserializacion

    std::string serialize(const char& delim = '*') const;
    void deserialize(const std::string&, const char& delim = '*');
};

// Implementacion

template <class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>::isValidPos(const int& p) const {
    return p >= 0 and p <= this->last;
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::copyAll(const List<T, ARRAYSIZE>& other) {
    int i = 0;
    while (i <= other.last) {
        this->data[i] = other.data[i];
        i++;
    }
    this->last = other.last;
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::swapData(T& a, T& b) {
    T aux(a);
    a = b;
    b = aux;
}

template <class T, int ARRAYSIZE>
List<T, ARRAYSIZE>::List() : data(new(nothrow) T[ARRAYSIZE]) {
    if (data == nullptr) {
        throw Exception("Memoria no disponible, list");
        }
    for(int i(0); i < ARRAYSIZE; this->data[i++] = nullptr);
    }

template <class T, int ARRAYSIZE>
List<T, ARRAYSIZE>::List(const List<T, ARRAYSIZE>& other) : last(other.last) : List() {
    this->copyAll(other);
    }

~List(){
    a
}


template <class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>::isEmpty() const {
    return this->last == -1;
}

template <class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>::isFull() const {
    return this->last == ARRAYSIZE - 1;
}

template<class T, int ARRAYSIZE>
bool List<T,ARRAYSIZE>::isSorted() const{
        int i(0);

        while(i < this->last) {
            if(*this->data[i] > *this->data[i + 1]){
                return false;
                }

                i++;
            }
        return true;
    }

template<class T, int ARRAYSIZE>
bool List<T,ARRAYSIZE>::isSorted(const std::function<int(const T&, const T&)>& cmp) const{
        int i(0);

        while(i < this->last) {
            if(cmp(*this->data[i], *this->data[i + 1]) > 0){
                return false;
                }

                i++;
            }
        return true;
    }

template <class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>::insData(const int& p, const T& e) {
    if (isFull()) return false;
    if (p < 0 || p > last + 1) return false; 

    T* newElem(new(nothrow) T);
    
    if(newElem == nullptr){
        thorw Exception("Memoria no disponible, insData")
        }

    for (int i = last; i >= p; i--) {
        data[i + 1] = data[i];
    }
    data[p] = e;
    last++;
    return true;
}

template <class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>::delData(const int& p) {
    if (!isValidPos(p)) return false;
    for (int i = p; i < last; i++) {
        data[i] = data[i + 1];
    }
    last--;
    return true;
}

template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::getFirstPos() const {
    return isEmpty() ? -1 : 0;
}

template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::getLastPos() const {
    return this->last;
}

template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::findData(const T& elem) const {
    for (int i = 0; i <= last; i++) {
        if (data[i] == elem) return i;
    }
    return -1; 
}

template <class T, int ARRAYSIZE>
T& List<T, ARRAYSIZE>::retrieve(const int& pos) {
    if(!this->isValidPos(pos)){
        throw Exception("Posicion invalida, retrieve");
    }
    return this->data[pos];
}

template <class T, int ARRAYSIZE>
std::string List<T, ARRAYSIZE>::toString() const {
    std::stringstream ss;
    for (int i = 0; i <= last; i++) {
        ss << data[i].toString() << "\n";
    }
    return ss.str();
}


template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::delAll() {
    this->last = -1;
}

template <class T, int ARRAYSIZE>
List<T, ARRAYSIZE>& List<T, ARRAYSIZE>::operator = (const List<T, ARRAYSIZE>& other) {
    this->copyAll(other);
    return *this;
}

template <class X, int Y>
std::ostream& operator << (std::ostream& os, const List<X, Y>& l) {
    int i(0);
    while (i <= l.last) {
        os << l.data[i] << std::endl;
        i++;
    }
    return os;
}

template <class X, int Y>
std::istream& operator >> (std::istream& is, List<X, Y>& l) {
    X myObj;
    while (is >> myObj) {
        l.insData(l.getLastPos() + 1, myObj); 
    }
    return is;
}

template <class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>::insertOrdered(const T& e) {
    if (isFull()) return false;
    
    int i = last;
    
    while (i >= 0 and data[i] > e) {
        data[i + 1] = data[i]; 
        i--;
    }
    data[i + 1] = e; 
    last++;
    return true;
}

//Busqueda lineal implicita
template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::findDataL(const T& e) const {
    int i(0);
    while (i <= this->last) {
        if (this->data[i] == e) {
            return i;
        }
        i++;
    }
    return -1;
}

//Busqueda lineal explicita
template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::findDataL(const T& e, const std::function<int(const T&, const T&)>& cmp) const {
    int i(0);
    while (i <= this->last) {
        if (cmp(this->data[i], e) == 0) {
            return i;
        }
        i++;
    }
    return -1;
}

//Busqueda binaria implicita
template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::findDataB(const T& e) const {
    int i(0), j(this->last), m;

    while (i <= j) {
        m = (i + j) / 2;

        if (this->data[m] == e) {
            return m;
        }

        if (e < this->data[m]) {
            j = m - 1;
        } else {
            i = m + 1;
        }
    }
    return -1;
}

//Busqueda binaria explicita
template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::findDataB(const T& e, const std::function<int(const T&, const T&)>& cmp) const {
    int i(0), j(this->last), m;

    while (i <= j) {
        m = (i + j) / 2;

        if (cmp(this->data[m], e) == 0) { 
            return m;
        }

        if (cmp(e, this->data[m]) < 0) { 
            j = m - 1;
        } else {
            i = m + 1;
        }
    }
    return -1;
}

// QUICKSORT

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataQuick(){
    this->sortDataQuick(0, this->last);
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataQuick(const int& leftEdge, const int& rightEdge){
    if(leftEdge >= rightEdge){
        return;
    }

    int i(leftEdge), j(rightEdge);

    while(i < j) {
        while(i < j and this->data[i] <= this->data[rightEdge]){
            i++;
        }
        while(i < j and this->data[j] >= this->data[rightEdge]){
            j--;
        }
        if(i != j){
            this->swapData(this->data[i], this->data[j]);
        }
    }

    if(i != rightEdge){
        this->swapData(this->data[i], this->data[rightEdge]);
    }

    this->sortDataQuick(leftEdge, i - 1);
    this->sortDataQuick(i + 1, rightEdge);
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataQuick(const std::function<int(const T&, const T&)>& cmp){
    this->sortDataQuick(0, this->last, cmp);
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataQuick(const int& leftEdge, const int& rightEdge, const std::function<int(const T&, const T&)>& cmp){
    if(leftEdge >= rightEdge){
        return;
    }

    int i(leftEdge), j(rightEdge);

    while(i < j) {
        while(i < j and cmp(this->data[i], this->data[rightEdge]) <= 0){
            i++;
        }
        while(i < j and cmp(this->data[j], this->data[rightEdge]) >= 0){
            j--;
        }
        if(i != j){
            this->swapData(this->data[i], this->data[j]);
        }
    }

    if(i != rightEdge){
        this->swapData(this->data[i], this->data[rightEdge]);
    }

    this->sortDataQuick(leftEdge, i - 1, cmp);
    this->sortDataQuick(i + 1, rightEdge, cmp);
}

// Serializacion y deserializacion
    template <class T, int ARRAYSIZE>
    std::string List<T,ARRAYSIZE>::serialize(const char& delim) const{
        std::string result;

        int i(0);
        while(i <= this->last){
            result+= this->data[i].serialize() + delim;

            i++;
            }
        return result;
    }

    template <class T, int ARRAYSIZE>
    void List<T,ARRAYSIZE>::deserialize(const std::string& str, const char& delim){
        std::stringstream mySStream(str);
        std::string myStr;
        T myObj;

        this->delAll();

        while(!mySStream.eof()) {
            getline(mySStream, myStr, delim);
            
            if(myStr.empty()){
                continue;
                }
            myObj.deserialize(myStr);

            if(this->isFull()){
                throw Exception("Desbordamiento de datos, deserialize");
                }

            this->data[++this->last] = myObj;
        }
    }
#endif // __LIST_HPP__
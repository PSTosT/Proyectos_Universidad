#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <string>
#include <sstream>

// Definicion
template <class T>
class List {
private:
    T data[500]; //
    int last = -1; //

    bool isValidPos(const int& p) const; //
    void copyAll(const List&); //

public:
    List(); //[cite: 2]
    List(const List&); //[cite: 2]

    bool isEmpty() const; //[cite: 1]
    bool isFull() const; //[cite: 1]
    
    void insData(const int& p, const T& e); //[cite: 1, 2]
    void delData(const int& p); //[cite: 1]
    
    int getFirtsPos() const; //[cite: 1]
    int getLastPos() const;

    int findData(const T&) const; // elem[cite: 2]
    T& retrieve(const int&); // pos[cite: 2]
    std::string toString() const; //[cite: 2]
    void sortData(); //[cite: 2]
    void delAll(); //[cite: 2]
    List& operator = (const List&); //[cite: 2]
};

// Implementacion[cite: 2]

template <class T>
bool List<T>::isValidPos(const int& p) const {
    return p >= 0 and p <= this->last; //[cite: 1]
}

template <class T>
void List<T>::copyAll(const List<T>& other) {
    int i = 0;
    while (i <= other.last) {
        this->data[i] = other.data[i];
        i++;
    }
    this->last = other.last;
}

template <class T>
List<T>::List() {} //[cite: 1]

template <class T>
List<T>::List(const List<T>& other) : last(other.last) { //[cite: 1]
    this->copyAll(other);
}

template <class T>
bool List<T>::isEmpty() const {
    return this->last == -1; //[cite: 1]
}

template <class T>
bool List<T>::isFull() const {
    return this->last == 499; //[cite: 1]
}

template <class T>
void List<T>::insData(const int& p, const T& e) {
    if (isFull()) return;
    if (p < 0 || p > last + 1) return; 

    for (int i = last; i >= p; i--) {
        data[i + 1] = data[i];
    }
    data[p] = e;
    last++;
}

template <class T>
void List<T>::delData(const int& p) {
    if (!isValidPos(p)) return;
    for (int i = p; i < last; i++) {
        data[i] = data[i + 1];
    }
    last--;
}

template <class T>
int List<T>::getFirtsPos() const { //[cite: 1]
    return isEmpty() ? -1 : 0;
}

template <class T>
int List<T>::getLastPos() const {
    return this->last;
}

template <class T>
int List<T>::findData(const T& elem) const {
    for (int i = 0; i <= last; i++) {
        if (data[i] == elem) return i;
    }
    return -1; // Fixes the compiler warning: no return statement returning non-void[cite: 2]
}

template <class T>
T& List<T>::retrieve(const int& pos) {
    return data[pos];
}

template <class T>
std::string List<T>::toString() const {
    std::stringstream ss;
    for (int i = 0; i <= last; i++) {
        ss << data[i] << "\n";
    }
    return ss.str();
}

template <class T>
void List<T>::sortData() {
    for (int i = 0; i < last; i++) {
        for (int j = 0; j < last - i; j++) {
            if (data[j] > data[j + 1]) {
                T temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

template <class T>
void List<T>::delAll() {
    this->last = -1; //[cite: 2]
}

template <class T>
List<T>& List<T>::operator = (const List<T>& other) {
    this->copyAll(other); //[cite: 2]
    return *this; //[cite: 2]
}

#endif // __LIST_HPP__[cite: 2]
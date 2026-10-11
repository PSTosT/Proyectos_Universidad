#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <string>
#include <sstream>
#include <iostream>

// Definicion
template <class T, int ARRAYSIZE>
class List {
private:
    T data[ARRAYSIZE];
    int last = -1;

    bool isValidPos(const int& p) const;
    void copyAll(const List&);

public:
    List();
    List(const List&);

    bool isEmpty() const;
    bool isFull() const;
    
    void insData(const int& p, const T& e);
    void delData(const int& p);
    
    int getFirtsPos() const;
    int getLastPos() const;

    int findData(const T&) const;
    T& retrieve(const int&);
    std::string toString() const;
    void sortData();
    void delAll();
    List& operator = (const List&);

    template <class X, int Y>
    friend std::istream& operator>>(std::istream&, List<X, Y>&);

    template <class X, int Y>
    friend std::ostream& operator<<(std::ostream&, const List<X, Y>&);
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
List<T, ARRAYSIZE>::List() {}

template <class T, int ARRAYSIZE>
List<T, ARRAYSIZE>::List(const List<T, ARRAYSIZE>& other) : last(other.last) {
    this->copyAll(other);
}

template <class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>::isEmpty() const {
    return this->last == -1;
}

template <class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>::isFull() const {
    return this->last == ARRAYSIZE - 1;
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::insData(const int& p, const T& e) {
    if (isFull()) return;
    if (p < 0 || p > last + 1) return; 

    for (int i = last; i >= p; i--) {
        data[i + 1] = data[i];
    }
    data[p] = e;
    last++;
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::delData(const int& p) {
    if (!isValidPos(p)) return;
    for (int i = p; i < last; i++) {
        data[i] = data[i + 1];
    }
    last--;
}

template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::getFirtsPos() const {
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
    return data[pos];
}

template <class T, int ARRAYSIZE>
std::string List<T, ARRAYSIZE>::toString() const {
    std::stringstream ss;
    for (int i = 0; i <= last; i++) {
        ss << data[i] << "\n";
    }
    return ss.str();
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortData() {
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
    while (is >> myObj;) {
        l.insData(l.getLastPos() + 1, myObj); // Changed to append safely
    }
    return is;
}

#endif // __LIST_HPP__
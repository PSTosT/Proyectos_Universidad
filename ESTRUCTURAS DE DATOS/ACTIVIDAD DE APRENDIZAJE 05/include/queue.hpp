#ifndef __QUEUE_HPP__
#define __QUEUE_HPP__

#include <exception>
#include <string>

// Definición
template<class T, int ARRAYSIZE = 1024>
class Queue {
private:
    T data[ARRAYSIZE];
    int frontPos = 0;
    int endPos = ARRAYSIZE - 1;

    void copyAll(const Queue<T, ARRAYSIZE>&);

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

    Queue();
    Queue(const Queue<T, ARRAYSIZE>&);

    bool isEmpty() const;
    bool isFull() const;
    void enqueue(const T&);
    T dequeue();
    T& getfront();

    Queue<T, ARRAYSIZE>& operator = (const Queue<T, ARRAYSIZE>&);
};

// Implementación

template<class T, int ARRAYSIZE>
void Queue<T, ARRAYSIZE>::copyAll(const Queue<T, ARRAYSIZE>& other) {
    this->frontPos = other.frontPos;
    this->endPos = other.endPos;
    
    if (other.isEmpty()) {
        return;
    }

    int i = other.frontPos;
    while (i != other.endPos) {
        this->data[i] = other.data[i];
        i++;
        if (i == ARRAYSIZE) {
            i = 0;
        }
    }
    // Copiar el último elemento (donde i == endPos)
    this->data[other.endPos] = other.data[other.endPos];
}

template<class T, int ARRAYSIZE>
Queue<T, ARRAYSIZE>::Queue() { }

template<class T, int ARRAYSIZE>
Queue<T, ARRAYSIZE>::Queue(const Queue<T, ARRAYSIZE>& other) { 
    this->copyAll(other);
}

template<class T, int ARRAYSIZE>
bool Queue<T, ARRAYSIZE>::isEmpty() const {
    return this->frontPos == this->endPos + 1
        || (this->frontPos == 0 && this->endPos == ARRAYSIZE - 1);
}

template<class T, int ARRAYSIZE>
bool Queue<T, ARRAYSIZE>::isFull() const {
    return this->frontPos == this->endPos + 2
        || (this->frontPos == 0 && this->endPos == ARRAYSIZE - 2)
        || (this->frontPos == 1 && this->endPos == ARRAYSIZE - 1);
}

template<class T, int ARRAYSIZE>
void Queue<T, ARRAYSIZE>::enqueue(const T& e) {
    if (this->isFull()) {
        throw Exception("Desbordamiento de datos, enqueue");
    }
    
    this->endPos++;

    if (this->endPos == ARRAYSIZE) {
        this->endPos = 0;
    }
    this->data[this->endPos] = e;
}

template<class T, int ARRAYSIZE>
T Queue<T, ARRAYSIZE>::dequeue() {
    if (this->isEmpty()) {
         throw Exception("Insuficiencia de datos, dequeue");
    }
    
    T result = this->data[this->frontPos];

    this->frontPos++;

    if (this->frontPos == ARRAYSIZE) {
        this->frontPos = 0;
    }
    
    return result;
}

template<class T, int ARRAYSIZE>
T& Queue<T, ARRAYSIZE>::getfront() {
    if (this->isEmpty()) {
        throw Exception("Insuficiencia de datos, getfront");
    }
    return this->data[this->frontPos];
}

template<class T, int ARRAYSIZE>
Queue<T, ARRAYSIZE>& Queue<T, ARRAYSIZE>::operator = (const Queue<T, ARRAYSIZE>& other) {
    this->copyAll(other);
    return *this;
}

#endif // __QUEUE_HPP__
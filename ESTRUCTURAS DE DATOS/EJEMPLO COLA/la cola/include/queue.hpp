#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <exception>
#include <string>

template<class T,int ARRAYSIZE = 1024>
class Queue{
private:
    T data[ARRAYSIZE];
    int frontPos = 0;
    int endPos = ARRAYSIZE - 1;

    void copyAll (const Queue<T,ARRAYSIZE>&);
public:
// ADD EXCEPTIONS
    Queue();
    Queue(const Queue<T,ARRAYSIZE>&);

    bool isEmpty() const;
    bool isFull() const;
    void enqueue(const T&);
    T dequeue();
    T& getfront();

    Queue<T, ARRAYSIZE>& operator =(const Queue<T, ARRAYSIZE>&);

};

//Implementacion
template<class T, int ARRAYSIZE>
void Queue<T,ARRAYSIZE>::copyAll (const Queue<T,ARRAYSIZE>& o){

}

template<class T, int ARRAYSIZE>
Queue<T, ARRAYSIZE>::Queue(){ }

template<class T, int ARRAYSIZE>
Queue<T, ARRAYSIZE>::Queue(const Queue<T,ARRAYSIZE>& other) { 
    this->copyAll(other);
 }

template<class T, int ARRAYSIZE>
bool Queue<T, ARRAYSIZE>::isEmpty() const{
    return this->frontPos == this->endPos+1
        or (this->frontPos == 0 and this->endPos == ARRAYSIZE -1);
    }

template<class T, int ARRAYSIZE>
bool Queue<T, ARRAYSIZE>::isFull() const{
    return this->frontPos == this->endPos +2
        or (this->frontPos == 0 and this->endPos == ARRAYSIZE -2)
        or (this->frontPos == 1 and this->endPos == ARRAYSIZE -1);
}

template<class T, int ARRAYSIZE>
void Queue<T, ARRAYSIZE>::enqueue(const T& e){
    if (this->isFull)(){
        //throw Exception("Desbordamiento de datos, enqueue"); terminar
    }
    this->endPos ++;

    if(this->endPos == ARRAYSIZE) {
        this->endPos = 0;
        }
        this->data[this->endPos] = e;
    }

template<class T, int ARRAYSIZE>
T Queue<T, ARRAYSIZE>::dequeue(){
    if (this->isEmpty()){
         //throw Exception("Insuficiencia de datos, enqueue"); terminar
        }
        T result(this->data[this->frontPos]);

        this->frontPos++;

        if(this->frontPos == ARRAYSIZE){
            this->frontPos = 0;
            }
        return result;
    }

template<class T, int ARRAYSIZE>
T& Queue<T, ARRAYSIZE>::getfront(){
    if (this->isEmpty()){
        //throw Exception("Insuficiencia de datos, getfront"); terminar
    }
    return this->data[frontPos];
}

//Sobrecarga de operador de asignacion

#endif // __QUEUE_H__
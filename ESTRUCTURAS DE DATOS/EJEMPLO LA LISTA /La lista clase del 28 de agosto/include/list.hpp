#ifndef __LIST_H__
#define __LIST_H__
#include <string>
class List{
    private:
        int data[500];
        int last = -1;

        bool isValidPos(const int&) const;

        void copyAll(const List&);
    public:
        List();
        List(const List&);

        bool isEmpty();
        bool isFull();
        void insData(const int&, const int&); //la primera es la posicion y la segunda es el elemento
        
        void delData(const int&); //pos (no es constante debido a que realizara cambios dentro del objeto)

        int getFirstPos() const;

        int getLastPos() const;

        int getPrevPos(const int&) const; //pos

        int getNextPos(const int&) const; //pos

        int findData(const int&) const; //elem

        int& retrieve(const int&) const; //pos

        std::string toString() const;

        void sortData();

        void delAll();

        List& operator = (const List&);

        

};


#endif // __LIST_H__
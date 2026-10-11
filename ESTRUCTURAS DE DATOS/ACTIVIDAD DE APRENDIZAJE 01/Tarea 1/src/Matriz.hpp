#pragma once

class Matriz{
    private:
        int size;
        float data[10][10];
    public:
        Matriz(int n);
        void RellenarRandom();
        void Imprimir();
        Matriz operator +(Matriz& otro) ;
        Matriz operator *(Matriz& otro) ;
};
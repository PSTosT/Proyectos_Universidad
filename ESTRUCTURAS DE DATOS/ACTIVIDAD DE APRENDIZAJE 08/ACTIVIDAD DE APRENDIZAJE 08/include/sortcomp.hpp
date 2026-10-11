#ifndef __SORTCOMP_H__
#define __SORTCOMP_H__
#include "list.hpp"
#include <chrono>
#include <random>
class SortComp{
    private:
        List<int,100000> myListA;
        List<int,100000> myListB;
        void fillA(List<int,100000>&);
        void exBubble();
        void exInsert();
        void exSelect();
        void exShell();
        void exMerge();
        void exQuick();
    public:
        SortComp();
        void startComp();
};
#endif // __SORTCOMP_H__
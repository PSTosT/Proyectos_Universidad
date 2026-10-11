#ifndef __USERINTERFACE_H__
#define __USERINTERFACE_H__
#include "list.hpp"
#include <chrono>
#include <random>
#include <functional>
#include <iostream>

class UserInterface{
    private:
        List* myListRef;

    public:
        UserInterface(List&);
    };

#endif // __USERINTERFACE_H__
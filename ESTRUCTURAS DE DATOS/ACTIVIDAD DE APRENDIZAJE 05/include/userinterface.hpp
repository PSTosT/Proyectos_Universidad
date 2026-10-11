#ifndef __USERINTERFACE_H__
#define __USERINTERFACE_H__

#include "stack.hpp"
#include "queue.hpp"
#include "expression.hpp"
#include <iostream>
#include <string>

class UserInterface{
    public:
        UserInterface();
        void showUserInterface();
        void clearScreen();
        void pressEnter();
        Queue<char> stringToQueue(const std::string&) const;
};
#endif // __USERINTERFACE_H__
#ifndef __USERINTERFACE_HPP__
#define __USERINTERFACE_HPP__

#include <iostream>
#include <string>
#include "student.hpp"

class UserInterface {
private:
    Student myStudent; 
    void addSubjectMenu();
    void clearSubjectsMenu();
    void showSubjectsMenu();

public:
    UserInterface();
    void start();
    
    static void clearScreen();
    static void enterToContinue();
};

#endif

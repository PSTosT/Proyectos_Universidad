#ifndef __USERINTERFACE_HPP__
#define __USERINTERFACE_HPP__

#include <iostream>
#include <fstream>
#include <string>

#include "student.hpp"
#include "list.hpp"

class UserInterface {
private:
    // The exact array size (e.g., 500) must be explicitly passed here
    List<Student, 500>* myListRef;

public:
    UserInterface(List<Student, 500>&);
};

#endif // __USERINTERFACE_HPP__
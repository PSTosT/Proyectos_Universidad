#ifndef __USERINTERFACE_H__
#define __USERINTERFACE_H__
#include "collection.hpp"
#include "product.hpp"
#include "date.hpp"
#include <iostream>
#include <limits>
#include <string>

class Userinterface{
    public:
        Userinterface();
        void startInterface();
        void pauseAndClearScreen();
};
#endif // __USERINTERFACE_H__
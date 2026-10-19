#ifndef __PERSONA_H__
#define __PERSONA_H__
#include "name.hpp"
#include <string>

class Persona{
    private:
        Name nombre;
        int edad;
    public:
        Persona(Name&,int&);
        void showPersona();

};
#endif // __PERSONA_H__
#ifndef __USUARIOBANCO_H__
#define __USUARIOBANCO_H__
#include <string>
#include <iostream>
class UsuarioBanco{
    private:
    std::string nombre = "Empty";
    float dinero = 0;

    public:
    UsuarioBanco();
    ~UsuarioBanco();

    bool ingresarDinero(const float&);
    bool retirarDinero(const float&);
    bool transferirDinero(float&, UsuarioBanco&);
    bool transferirLegado(UsuarioBanco&, UsuarioBanco&);
    
    void setDinero(const float&);
    void setNombre(const std::string&);

    float getDinero();
    std::string getNombre();

    std::string toString();


};
#endif // __USUARIOBANCO_H__
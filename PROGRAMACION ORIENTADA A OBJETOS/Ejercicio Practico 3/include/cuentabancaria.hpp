#ifndef __CUENTABANCARIA_H__
#define __CUENTABANCARIA_H__
#include <string>

class CuentaBancaria{
    private:
    int numeroCuenta = 0000; //0000 Es un numero de cuenta invalido
    std::string titular = "noname"; // noname es un nombre de titular invalido (Espero que nadie se llame en verdad noname)
    float saldo = 0; //Un valor por defecto al no recibir este valor. 

    public:
    CuentaBancaria();
    CuentaBancaria(int&, std::string&, float&);
    std::string mostrarDatos();
    friend bool transferir(CuentaBancaria&, CuentaBancaria&, float);
    
};
#endif // __CUENTABANCARIA_H__
#include "cuentabancaria.hpp"


CuentaBancaria::CuentaBancaria(){ }

CuentaBancaria::CuentaBancaria(int& nc, std::string& t, float& s){
    this->numeroCuenta = nc;
    this->titular = t;
    this-> saldo = s;
}

std::string CuentaBancaria::mostrarDatos(){
    std::string resultado;
    resultado += "Numero de cuenta: " + std::to_string(this->numeroCuenta) + '|';
    resultado += "Titular: " + this->titular + '|';
    resultado += "Saldo: " + std::to_string(this->saldo);

    return resultado;
}

bool transferir(CuentaBancaria& a, CuentaBancaria& b, float din){
    if(din > 0){ //Validar si el dinero a transferir es mayor a 0
        if(a.numeroCuenta != b.numeroCuenta){ //Validar si se trata de cuentas diferentes
            if(din <= a.saldo){ //Validar que la cuenta de origen tenga el saldo suficiente
                a.saldo = a.saldo - din;
                b.saldo = b.saldo + din;
                return true;
            }
        }    
    }
    return false;
}

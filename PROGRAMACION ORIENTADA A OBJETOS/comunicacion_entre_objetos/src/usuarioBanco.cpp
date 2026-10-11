#include "usuarioBanco.hpp"


UsuarioBanco::UsuarioBanco() {    }
    

UsuarioBanco::~UsuarioBanco(){    }

bool UsuarioBanco::ingresarDinero(const float& din){
    if(din>0){
        this->dinero = this->dinero+din;
        return true;
    }
    return false;
}

bool UsuarioBanco::retirarDinero(const float& ret){
    if(ret>0){
        if(ret<=this->dinero){
            this->dinero = this->dinero - ret;
            return true;
        }
        return false;
    }
    return false;
}

bool UsuarioBanco::transferirDinero(float& din, UsuarioBanco& b){
    if(this->dinero >= din){
        b.ingresarDinero(din);
        this->dinero = this->dinero - din;
        return true;
    }
    return false;
}


void UsuarioBanco::setNombre(const std::string& n){
    this->nombre = n;
}

void UsuarioBanco::setDinero(const float& f){
    this->dinero = f;
}

float UsuarioBanco::getDinero(){
    return this->dinero;
}

std::string UsuarioBanco::getNombre(){
    return this->nombre;
}

std::string UsuarioBanco::toString(){
    std::string result;

    result += this->nombre += "\n";
    result += std::to_string(this->getDinero()) += "\n";

    return result;
}

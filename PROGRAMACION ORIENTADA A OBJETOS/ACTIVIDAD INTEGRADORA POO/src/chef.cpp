#include "chef.hpp"
using namespace std;

// ==================== Implementacion de Persona ====================

Persona::Persona() : nombre(), edad(18) { }

Persona::Persona(const Name& n, int e) : nombre(n), edad(e) { }

Persona::Persona(const Persona& other) : nombre(other.nombre), edad(other.edad) { }

Persona::~Persona() { }

Name Persona::getNombre() const {
    return this->nombre;
}

int Persona::getEdad() const {
    return this->edad;
}

void Persona::setNombre(const Name& n) {
    this->nombre = n;
}

void Persona::setEdad(int e) {
    this->edad = (e > 0) ? e : 18;
}

std::string Persona::obtenerRol() const {
    return "Persona General";
}

std::string Persona::obtenerFicha() const {
    stringstream ss;
    ss << "[" << obtenerRol() << "] Nombre: " << this->nombre.toString()
       << " | Edad: " << this->edad << " anios";
    return ss.str();
}

// ==================== Implementacion de Chef ====================

Chef::Chef() : Persona(), especialidad("Cocina General"), aniosExperiencia(1) { }

Chef::Chef(const Name& n, int e, const std::string& esp, int exp)
    : Persona(n, e), especialidad(esp), aniosExperiencia(exp) { }

Chef::Chef(const Chef& other)
    : Persona(other.nombre, other.edad),
      especialidad(other.especialidad),
      aniosExperiencia(other.aniosExperiencia) { }

Chef::~Chef() { }

std::string Chef::getEspecialidad() const {
    return this->especialidad;
}

int Chef::getAniosExperiencia() const {
    return this->aniosExperiencia;
}

void Chef::setEspecialidad(const std::string& esp) {
    this->especialidad = esp;
}

void Chef::setAniosExperiencia(int exp) {
    this->aniosExperiencia = (exp >= 0) ? exp : 0;
}

std::string Chef::obtenerRol() const {
    return "Chef Autor";
}

std::string Chef::obtenerFicha() const {
    stringstream ss;
    ss << "[" << obtenerRol() << "] " << this->nombre.toString()
       << " | Edad: " << this->edad
       << " | Especialidad: " << this->especialidad
       << " | Experiencia: " << this->aniosExperiencia << " anios";
    return ss.str();
}

std::string Chef::toString() const {
    return this->obtenerFicha();
}

Chef& Chef::operator=(const Chef& other) {
    this->nombre = other.nombre;
    this->edad = other.edad;
    this->especialidad = other.especialidad;
    this->aniosExperiencia = other.aniosExperiencia;
    return *this;
}

bool Chef::operator==(const Chef& other) const {
    return this->nombre == other.nombre;
}

std::string Chef::serialize(const char& delim) const {
    string result;
    result += this->nombre.serialize(',') + delim;
    result += to_string(this->edad) + delim;
    result += this->especialidad + delim;
    result += to_string(this->aniosExperiencia);
    return result;
}

void Chef::deserialize(const std::string& str, const char& delim) {
    stringstream mySStream(str);
    string myStr;

    getline(mySStream, myStr, delim);
    this->nombre.deserialize(myStr, ',');

    getline(mySStream, myStr, delim);
    try {
        this->edad = myStr.empty() ? 18 : stoi(myStr);
    } catch (...) {
        this->edad = 18;
    }

    getline(mySStream, this->especialidad, delim);

    getline(mySStream, myStr, delim);
    try {
        this->aniosExperiencia = myStr.empty() ? 1 : stoi(myStr);
    } catch (...) {
        this->aniosExperiencia = 1;
    }
}

std::string consultarAutorPolimorfico(const Persona& persona) {
    return persona.obtenerFicha();
}

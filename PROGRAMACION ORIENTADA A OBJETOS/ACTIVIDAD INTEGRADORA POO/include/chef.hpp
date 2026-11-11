#ifndef __CHEF_H__
#define __CHEF_H__

#include <string>
#include <sstream>
#include "name.hpp"

// Interfaz <<interface>> para demostrar Realizacion y Abstraccion pura
class IMostrable {
public:
    virtual std::string obtenerFicha() const = 0;
    virtual ~IMostrable() = default;
};

// Clase Base Persona (Demuestra Composicion con Name, Encapsulamiento y Herencia)
class Persona : public IMostrable {
protected:
    Name nombre;
    int edad;

public:
    Persona();
    Persona(const Name& n, int e);
    Persona(const Persona& other);
    virtual ~Persona();

    // Getters y Setters
    Name getNombre() const;
    int getEdad() const;

    void setNombre(const Name& n);
    void setEdad(int e);

    // Metodos virtuales para Polimorfismo
    virtual std::string obtenerRol() const;
    virtual std::string obtenerFicha() const override;
};

// Clase Derivada Chef : "Un Chef ES UNA Persona" (Herencia y Polimorfismo)
class Chef : public Persona {
private:
    std::string especialidad;
    int aniosExperiencia;

public:
    Chef();
    Chef(const Name& n, int e, const std::string& esp, int exp);
    Chef(const Chef& other);
    virtual ~Chef();

    // Getters
    std::string getEspecialidad() const;
    int getAniosExperiencia() const;

    // Setters
    void setEspecialidad(const std::string& esp);
    void setAniosExperiencia(int exp);

    // Sobrescritura polimorfica (override)
    std::string obtenerRol() const override;
    std::string obtenerFicha() const override;

    std::string toString() const;

    Chef& operator=(const Chef& other);
    bool operator==(const Chef& other) const;

    // Serializacion para persistencia en disco
    std::string serialize(const char& delim = '*') const;
    void deserialize(const std::string& str, const char& delim = '*');
};

// Funcion que demuestra polimorfismo por sustitucion (enlace dinamico)
std::string consultarAutorPolimorfico(const Persona& persona);

#endif // __CHEF_H__

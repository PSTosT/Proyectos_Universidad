#include <iostream>
#include <string>
class Persona {
    private:
        std::string nombre;
    public:
        Persona(const std::string& n) : nombre(n) {}
        std::string getNombre() const { return nombre; }
        void presentarse() const {
        std::cout << "Soy " << nombre << "\n";
        }
};
class Estudiante : public Persona {
    private:
        int semestre;
    public:
        Estudiante(const std::string& n, int s)
        : Persona(n), semestre(s) {}
        void mostrarFicha() const {
            std::cout << "Estudiante: " << getNombre()
            << ", semestre: " << semestre << "\n";
        }
};
int main() {
    Estudiante alumno("Diego Ruelas", 3);
    alumno.presentarse();
    alumno.mostrarFicha();

    Estudiante alumno1("Carlos", 5);
    alumno1.presentarse();
    alumno1.mostrarFicha();
    return 0;
}
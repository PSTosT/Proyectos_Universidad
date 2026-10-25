#include "userinterface.hpp"

using namespace std;

UserInterface::UserInterface() {}

void UserInterface::start() {
    string myStr; 
    
    clearScreen();
    cout << "Bienvenido al Sistema de Gestion Escolar\n";
    cout << "Por favor, ingresa tus datos para comenzar.\n\n";
    
    cout << "Nombre completo: >> ";
    getline(cin, myStr);
    this->myStudent.setName(myStr);

    cout << "Carrera : >> ";
    getline(cin, myStr);
    this->myStudent.setMajor(myStr);

    cout << "Codigo de estudiante: >> ";
    getline(cin, myStr);
    this->myStudent.setCode(myStr);
    
    int opc;
    do {
        clearScreen();
        cout << "=== Menu Principal ===\n";
        cout << "Estudiante activo: " << this->myStudent.getName() 
             << " (" << this->myStudent.getCode() << ")\n\n";
        cout << "1. Agregar materia\n";
        cout << "2. Eliminar TODAS las materias\n";
        cout << "3. Mostrar kardex de materias\n";
        cout << "4. Salir\n";
        cout << ">> ";
        cin >> opc;
        cin.ignore();

        switch (opc) {
            case 1: addSubjectMenu(); break;
            case 2: clearSubjectsMenu(); break;
            case 3: showSubjectsMenu(); break;
            case 4: 
                cout << "Cerrando sesion...\n"; 
                enterToContinue();
                break;
            default:
                cout << "Opcion invalida.\n";
                enterToContinue();
                break;
        }
    } while (opc != 4);
}

void UserInterface::addSubjectMenu() {
    string myStr;
    Subject tempSubject; 
    
    clearScreen();
    cout << "Inscribir Nueva Materia\n";
    
    cout << "Nombre de la materia: >> ";
    getline(cin, myStr);
    tempSubject.setName(myStr);

    cout << "Codigo de la materia >> ";
    getline(cin, myStr);
    tempSubject.setCode(myStr);

    cout << "Nombre del profesor: >> ";
    getline(cin, myStr);
    tempSubject.setProfessor(myStr);

    cout << "Horario Ej. L/M/V 1100-1300: >> ";
    getline(cin, myStr);
    tempSubject.setSchedule(myStr);

    this->myStudent.addSubject(tempSubject);
    
    cout << "\nMateria inscrita con exito.\n";
    enterToContinue();
}

void UserInterface::clearSubjectsMenu() {
    clearScreen();
    this->myStudent.clearSubjects();
    cout << "Todas las materias han sido dadas de baja.\n";
    enterToContinue();
}

void UserInterface::showSubjectsMenu() {
    clearScreen();
    cout << this->myStudent.toString();
    enterToContinue();
}

void UserInterface::clearScreen() {
    cout << "\x1B[2J\x1B[H";
}

void UserInterface::enterToContinue() {
    cout << "\nPresiona Enter para continuar...";
    cin.get();
}

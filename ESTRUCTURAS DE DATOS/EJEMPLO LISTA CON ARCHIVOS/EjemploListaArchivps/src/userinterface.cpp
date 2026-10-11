#include "userinterface.hpp"

using namespace std;

// The signature must match the explicitly sized List
UserInterface::UserInterface(List<Student, 500>& l) : myListRef(&l) {
    string myCadena;
    char op;

    // 1. Data Collection Loop
    do {
        Student tempStudent;
        string tempStr, first, last;
        int y, m, d;
        float grade;

        cout << "--- Ingresar Nuevo Estudiante ---" << endl;
        
        cout << "Codigo: ";
        getline(cin, tempStr);
        tempStudent.setCode(tempStr);

        cout << "Nombres: ";
        getline(cin, first);
        cout << "Apellidos: ";
        getline(cin, last);
        tempStudent.setName(Name(last, first));

        cout << "Fecha de Nacimiento (YYYY MM DD separados por espacio): ";
        cin >> y >> m >> d;
        tempStudent.setBirthDate(Date(y, m, d));
        cin.ignore(); 

        cout << "Carrera (ej. INCO): ";
        getline(cin, tempStr);
        tempStudent.setCareer(tempStr);

        cout << "Fecha de Ingreso (YYYY MM DD separados por espacio): ";
        cin >> y >> m >> d;
        tempStudent.setStartDate(Date(y, m, d));

        cout << "Promedio: ";
        cin >> grade;
        tempStudent.setGrade(grade);
        
        myListRef->insData(myListRef->getLastPos() + 1, tempStudent);

        cout << "Insertar otro? (S/N): ";
        do {
            cin >> op;
            cin.ignore(); 
            op = toupper(op);
        } while (op != 'N' and op != 'S');
        
    } while (op == 'S');

    cout << endl << endl;

    // 2. Display the list
    cout << "Contenido de la lista:" << endl;
    cout << myListRef->toString() << endl;
    cout << endl << endl;

    // 3. Write data to a file
    cout << "Guardar en archivo...: " << endl;
    getline(cin, myCadena);

    ofstream myArchivoOut(myCadena, ios_base::trunc);
    if(myArchivoOut.is_open()) {
        myArchivoOut << *myListRef;
        myArchivoOut.close();
    } else {
        cout << "No se pudo abrir el archivo" << endl;
    }

    cout << endl << endl;
    cout << "[ENTER] para continuar...";
    cin.get();

    // 4. Read data from a file
    cout << "Leyendo del archivo" << endl << endl;
    cout << "Nombre del archivo: ";
    getline(cin, myCadena);

    ifstream myArchivoIn(myCadena);
    if(myArchivoIn.is_open()) {
        myListRef->delAll(); 
        myArchivoIn >> *myListRef;
        myArchivoIn.close();
    } else {
        cout << "No se pudo abrir el archivo" << endl;
    }

    cout << endl << endl;
    cout << "Contenido de la lista:" << endl;
    cout << myListRef->toString();
    
    cout << "[ENTER] para continuar...";
    cin.get();
}
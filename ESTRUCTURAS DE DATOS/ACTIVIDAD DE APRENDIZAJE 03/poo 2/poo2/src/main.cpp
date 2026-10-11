#include <iostream>
#include "car.hpp"
using namespace std;

void cleanAndPause();

int main()
{
    Car myCar;
    string myStr;
    int opc;

    cout << "Bienvenido al sistema Car Status" << endl;
    cleanAndPause();

    do
    {
        cout << "Estado actual del coche" << endl;
        cout << "(Marca | Modelo | Color | Velocidad | Combustible | Estado del motor)" << endl;
        cout << myCar.toString() << endl << endl;

        cout << "Selecciona una opcion para realizar con tu coche: " << endl;

        cout << "1. Definir marca " << endl;
        cout << "2. Definir modelo " << endl;
        cout << "3. Definir color " << endl;
        cout << "4. Encender " << endl;
        cout << "5. Apagar " << endl;
        cout << "6. Acelerar " << endl;
        cout << "7. Frenar " << endl;
        cout << "8. Añadir combustible " << endl;
        cout << "9. Salir " << endl;

        cin >> opc;
        cin.ignore();

        switch (opc)
        {
        case 1:{
            cout << "Escribe la marca de tu coche >> ";
            getline(cin, myStr);

            myCar.setBrand(myStr);
        }
            break;
        case 2:{
            cout << "Escribe el modelo de tu coche >> ";
            getline(cin, myStr);

            myCar.setModel(myStr);
        }
            break;
        case 3:{
            cout << "Escribe el color de tu coche >> ";
            getline(cin, myStr);

            myCar.setColor(myStr);
        }
            break;
        case 4:{
            if(myCar.startEngine()){
                cout << "El coche encendio" << endl;
            } else {
                cout << "Imposible encender" << endl;
            }
        }
            break;
        case 5:{
            if(myCar.startEngine()){
                cout << "El coche se apago" << endl;
            } else {
                cout << "Imposible apagar" << endl;
            }
        }
            break;
        case 6:{
            if(myCar.accelerate()){
                cout << "El coche aumento su velocidad 10 km/h y gasto 5 de combustible" << endl;
            } else {
                cout << "Imposible acelerar" << endl;
            }
        }
            break;
        case 7:{
            if(myCar.brake()){
                cout << "El coche disminuyo su velocidad 10 km/h" << endl;
            } else {
                cout << "Imposible frenar" << endl;
            }
        }
            break;
        case 8:{
            if(myCar.addFuel()){
                cout << "Se le añadio con exito 5 de combustible" << endl;
            } else {
                cout << "Imposible añadir combustible" << endl;
            }
        }
            break;
        case 9:{
            cout << "Saliendo del sistema...";
        }
            break;
        
        
        default:
            cout << "Selecciona una opcion valida..." << endl;
            break;
        }
        cleanAndPause();
    } while (opc != 9);
    
}

void cleanAndPause(){
    cout << "\nPresiona Enter para continuar...";
    cin.ignore(10000, '\n'); 
    cin.get();
    cout << "\x1B[2J\x1B[H";
}
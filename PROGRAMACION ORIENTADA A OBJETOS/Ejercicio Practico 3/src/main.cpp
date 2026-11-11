#include <iostream>
#include "cuentabancaria.hpp"
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    vector<CuentaBancaria> misCuentas;
    int tempInt, origen, destino;
    float tempFloat;
    string tempStr;
    char sel;

    cout << "Bienvenido al gestor de cuentas bancarias" << endl;
    
    do {
        cout << "\nAgrega una cuenta bancaria!" << endl;
        cout << "Ingresa el numero de cuenta (ej. 1001): ";
        cin >> tempInt;
        cin.ignore(10000, '\n');

        cout << "Ingresa el nombre del titular: ";
        getline(cin, tempStr);

        cout << "Ingresa un saldo inicial: ";
        cin >> tempFloat;
        cin.ignore(10000, '\n');

        CuentaBancaria nuevaCuenta(tempInt, tempStr, tempFloat);
        misCuentas.push_back(nuevaCuenta);

        cout << "\nDeseas agregar otra cuenta? (S/N): ";
        cin >> sel;
        cin.ignore(10000, '\n');
        sel = toupper(sel);

    } while (sel != 'N');
    do {
        cout << "Tus cuentas actuales son las siguientes :" << endl;
        for(size_t i = 0; i < misCuentas.size(); i++){
            cout << "[" << i << "] " << misCuentas[i].mostrarDatos() << endl;
        }
        cout << "OPERACION DE TRANSFERENCIA" << endl;
        cout << "Selecciona el indice de la cuenta ORIGEN: ";
        cin >> origen;
        cout << "Selecciona el indice de la cuenta DESTINO: ";
        cin >> destino;
        cout << "Ingresa la CANTIDAD a transferir: ";
        cin >> tempFloat;
        cin.ignore(10000, '\n');

        if(origen >= 0 && origen < misCuentas.size() && destino >= 0 && destino < misCuentas.size()) {
            
            cout << "\nProcesando transferencia." << endl;
            if(transferir(misCuentas[origen], misCuentas[destino], tempFloat)){
                cout << "Transferencia realizada correctamente." << endl;
            } else {
                cout << "Transferencia rechazada." << endl;
            }

        } else {
            cout << "Selecciono un indice de cuenta que no existe." << endl;
        }

        cout << "\nDeseas realizar otra operacion? (S/N): ";
        cin >> sel;
        cin.ignore(10000, '\n');
        sel = toupper(sel);

    } while (sel != 'N');

    cout << "Saliendo del sistema bancario..." << endl;
    return 0;
}

#include "userinterface.hpp"
using namespace std;
Userinterface::Userinterface(){}

void Userinterface::pauseAndClearScreen()
{
    
}

void Userinterface::startInterface(){

    int selection;
    Collection myCollection;
    Product newProduct;
    Date myDate;

    string myString;
    int myInt;
    float myFloat;
    int cond;

    do {

    cout << "Bienvenido al inventario de tu tienda" << endl;
    cout << "Selecciona una opcion a realizar" << endl;
    cout << "1. Añadir producto" << endl;
    cout << "2. Eliminar producto" << endl;
    cout << "3. Imprimir inventario (Codigo de barras | Nombre | Peso | Fecha de Entrada | Precio de mayoreo (mxn)| Precio de menudeo (mxn) | stock )" << endl;
    cout << "4. Terminar sesion" << endl;
    cout << ">>";

        cin >> selection;
        cin.ignore();
        switch (selection)
        {
        case 1: 
            do
            {
                cond = 0;

                cout << "Introduce el codigo de barras (13 digitos): >> ";
                getline(cin, myString);
                newProduct.setBarcode(myString);

                if(newProduct.getBarcode()=="notValid"){
                    cout << "Error, intenta de nuevo con un codigo de barras valido (13 digitos) \n";
                    cond = -1;
                }

            } while (cond == -1);

            if (myCollection.exists(myString)){
                myCollection.add(newProduct);
                cout << "Producto ya existente, stock agregado!" << endl;

                break;
            }

            cout << "Introduce el nombre del objeto >>";
                
                getline(cin, myString);
                newProduct.setName(myString);
            
            cout << endl << "Introduce el peso del objeto (Kg) >>";

                cin >> myFloat;
                newProduct.setWeight(myFloat);
                cin.ignore();

            cout << endl << "Introduce la fecha de entrada del objeto >>";

                cout << endl << "Fecha de ingreso (DD/MM/AAAA): >>";

                    getline(cin, myString, '/');
                    myDate.setDay(stoi(myString));
                    getline(cin, myString, '/');
                    myDate.setMonth(stoi(myString));
                    getline(cin, myString);
                    myDate.setYear(stoi(myString));

                    newProduct.setIncomeDate(myDate);

            cout << endl << "Introduce el precio de mayoreo del objeto (mxn) >>";

                cin >> myFloat;
                newProduct.setWholePrice(myFloat);

            cout << endl << "Introduce el precio de menudeo del objeto (mxn) >>";

                cin >> myFloat;
                newProduct.setRetailPrice(myFloat);
            
            myCollection.add(newProduct);
            cout << "Producto nuevo, agregado al inventario!" << endl;

            pauseAndClearScreen();

            break;

        case 2: 
            
            cout << "Introduce el codigo de barras (13 digitos): ";
                getline(cin, myString);
                if(myCollection.del(myString)==true){
                    cout << "Existencia de producto eliminada" << endl;
                }
                else {cout << "Producto inexistente" << endl;}
                
                pauseAndClearScreen();

            break;
        case 3:     
            cout << myCollection.printCollection() << endl;
            pauseAndClearScreen();
            break;
        case 4:     
            cout << "Terminando sesion..." << endl;
            
            break;
        default:
            cout << "Selecciona una opcion valida" << endl;
            pauseAndClearScreen();
            break;
        }
    } while (selection !=4);
    
        
}


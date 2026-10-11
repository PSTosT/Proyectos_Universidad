#include <iostream>
#include "usuarioBanco.hpp"

using namespace std;
int main(int argc, char *argv[]){
    UsuarioBanco MisUsuarios[1];
   
    string myStr;
    float myfloat;
    int opc;

    cout << "Define tu usuario 1: " << endl;
    cout << "Escribe su nombre >> ";
    getline(cin,myStr);
    MisUsuarios[0].setNombre(myStr);
    cout << endl << "Ingresa dinero >> " << endl;
    cin >> myfloat;
    MisUsuarios[0].setDinero(myfloat);
    cin.ignore();

    cout << "Define tu usuario 2: " << endl;
    cout << "Escribe su nombre >> ";
    getline(cin,myStr);
    MisUsuarios[1].setNombre(myStr);
    cout << endl << "Ingresa dinero >> " << endl;
    cin >> myfloat;
    MisUsuarios[1].setDinero(myfloat);
    cin.ignore();

    do{
        int select;
        int subselect;
        int subopc;

        cout << "Informacion de tus usuarios" << endl;
        for(int i=0 ; i<=1 ; i++){
            cout << MisUsuarios[i].toString() << endl;
        }

        cout << "Selecciona una opcion" << endl;
        cout << "1. Operar usuario 1" << endl;  
        cout << "2. Operar usuario 2" << endl;  
        cout << ">> ";
        cin >> opc;
        cin.ignore();
        cout << endl;
        do{
            if(opc == 1 or opc == 2){
                select = opc -1;
                if (select == 1){
                    subselect = 0;
                } else {
                    subselect = 1;
                }

                cout << "Selecciona una opcion a realizar" << endl;
                cout << "1. Transferir dinero a Usuario " << subselect << endl;
                cout << "2. Ingresar dinero " << endl;
                cout << "3. Retirar dinero " << endl;
                cout << ">> ";
                cin >> subopc;
                cin.ignore();

                switch (subopc)
                {
                case 1:
                    cout << " Cuanto dinero quieres transferir..." << endl;
                    cout << ">> ";
                    cin >> myfloat;
                    cin.ignore();
                    cout << endl;
                    if(MisUsuarios[select].transferirDinero(myfloat,MisUsuarios[subselect])){
                        cout << "Transferencia exitosa..." << endl;
                    }
                    break;
                case 2:
                    
                    break;
                case 3:
                    
                    break;
                
                default:
                    break;
                }
            }
        }while(subopc < 1 or subopc >3) ;
    } while (opc != 3);
    
    

}

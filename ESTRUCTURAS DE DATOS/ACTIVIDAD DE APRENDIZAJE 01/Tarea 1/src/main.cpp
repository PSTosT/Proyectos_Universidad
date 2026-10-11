//ACTIVIDAD DE APRENDIZAJE 01 
//TIPOS DE DATO PRIMITIVOS Y TIPOS DE DATO ESTRUCTURADOS
//Diego Ruelas Buenrostro

#include "Matriz.hpp"
#include "TipoDatoPrimitivo.hpp"
#include <iostream>
using namespace std;

void PausarLimpiar() {
    cout << "\nPresiona Enter para continuar...";
    cin.ignore(10000, '\n'); 
    cin.get();
    //codigo ANSI que limpia la terminal
    cout << "\x1B[2J\x1B[H";

}
void EjecutarA(){
    TipoDatoPrimitivo a;
    a.ImpresionPrimitivos();
}
void EjecutarB(){
            int tam;
            cout<<"Suma y multiplicacion de matrices con datos aleatorios"
            << endl << "Escribe un valor del 3 al 10 para el tamaño de la matriz"<<endl
            <<">> ";

            cin>>tam;

            while (tam<3 || tam>10){
              
                    cout<<"Error, escribe un dato valido"<<endl<<">> ";
                    cin>>tam;
   
            }
                Matriz MatrizA(tam);
                    MatrizA.RellenarRandom();
                Matriz MatrizB(tam);
                    MatrizB.RellenarRandom();
                Matriz MatrizC = MatrizA*MatrizB;
                Matriz MatrizD = MatrizA+MatrizB;

                cout<<endl<<"Matriz A (generada con datos aleatorios):"<<endl<<endl;
                MatrizA.Imprimir();

                cout<<endl<<"Matriz B (generada con datos aleatorios):"<<endl<<endl;
                MatrizB.Imprimir();

                cout<<endl<<"Matriz C (Matriz A por Matriz B):"<<endl<<endl;
                MatrizC.Imprimir();

                cout<<endl<<"Matriz D (Matriz A mas Matriz B):"<<endl<<endl;
                MatrizD.Imprimir();

        }

int main(int argc, char *argv[])
{
    int opcion;

    do {
        cout << "Bienvenido, selecciona una opcion:\n"
             << "1. Tamaño y rangos de los Tipos de Dato Primitivos\n"
             << "2. Ejemplo de uso de Tipo de dato Estructurado\n"
             << "3. Salir\n"
             << ">> ";
        cin >> opcion;

        switch (opcion)
        {
            case 1:
                {
                    EjecutarA();
                    PausarLimpiar();
                }
                break;

            case 2:
                {
                    EjecutarB();
                    PausarLimpiar();
                }
                break;

            case 3:
                {
                cout << "Saliendo...\n";
                }
                break;

            default:
                {
                cout << "Opcion no valida\n";
                }
                break;
        }

    } while (opcion != 3);
    

}

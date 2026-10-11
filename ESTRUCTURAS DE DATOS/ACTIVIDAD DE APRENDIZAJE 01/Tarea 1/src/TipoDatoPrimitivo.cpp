#include "TipoDatoPrimitivo.hpp"
#include <iostream>
#include <limits>
#include <iomanip>

using namespace std;

void TipoDatoPrimitivo::ImpresionPrimitivos(){

    //constantes para definir el ancho de cada columna
    //y darle formato de tablña

    const int ANCHO_TIPO = 35;
    const int ANCHO_BITS = 15;
    const int ANCHO_MIN = 25;
    const int ANCHO_MAX =25;

            cout << endl << "-----------------------------------------------";
            cout << endl << "Tamaño y rango de los tipos de Dato Primitivo";
            cout << endl << "-----------------------------------------------" << endl << endl;

            cout << left 
                << setw(ANCHO_TIPO) << "Tipo de dato" 
                << setw(ANCHO_BITS) << "Bits" 
                << setw(ANCHO_MIN)  << "Valor minimo"
                << setw(ANCHO_MAX)  << "Valor maximo" << endl;

            cout << left 
                << setw(ANCHO_TIPO) << "Caracter CON signo" 
                << setw(ANCHO_BITS) << +(sizeof(char) * 8) 
                << setw(ANCHO_MIN)  << +numeric_limits<char>::min() 
                << setw(ANCHO_MAX)  << +numeric_limits<char>::max() << endl;

            cout << left 
                << setw(ANCHO_TIPO) << "Caracter SIN signo" 
                << setw(ANCHO_BITS) << +(sizeof(unsigned char) * 8) 
                << setw(ANCHO_MIN)  << +numeric_limits<unsigned char>::min() 
                << setw(ANCHO_MAX)  << +numeric_limits<unsigned char>::max() << endl;

            cout << left 
                << setw(ANCHO_TIPO) << "Entero corto CON signo" 
                << setw(ANCHO_BITS) << (sizeof(short int) * 8) 
                << setw(ANCHO_MIN)  << numeric_limits<short int>::min() 
                << setw(ANCHO_MAX)  << numeric_limits<short int>::max() << endl;

            cout << left 
                << setw(ANCHO_TIPO) << "Entero corto SIN signo" 
                << setw(ANCHO_BITS) << (sizeof(unsigned short int) * 8) 
                << setw(ANCHO_MIN)  << numeric_limits<unsigned short int>::min() 
                << setw(ANCHO_MAX)  << numeric_limits<unsigned short int>::max() << endl;

            cout << left 
                << setw(ANCHO_TIPO) << "Entero largo CON signo" 
                << setw(ANCHO_BITS) << (sizeof(long int) * 8) 
                << setw(ANCHO_MIN)  << numeric_limits<long int>::min() 
                << setw(ANCHO_MAX)  << numeric_limits<long int>::max() << endl;

            cout << left 
                << setw(ANCHO_TIPO) << "Entero largo SIN signo" 
                << setw(ANCHO_BITS) << (sizeof(unsigned long int) * 8) 
                << setw(ANCHO_MIN)  << numeric_limits<unsigned long int>::min() 
                << setw(ANCHO_MAX)  << numeric_limits<unsigned long int>::max() << endl;

            cout << left 
                << setw(ANCHO_TIPO) << "Real de precision simple" 
                << setw(ANCHO_BITS) << (sizeof(float) * 8) 
                << setw(ANCHO_MIN)  << numeric_limits<float>::min() 
                << setw(ANCHO_MAX)  << numeric_limits<float>::max() << endl;

            cout << left 
                << setw(ANCHO_TIPO) << "Real de doble precision" 
                << setw(ANCHO_BITS) << (sizeof(double) * 8) 
                << setw(ANCHO_MIN)  << numeric_limits<double>::min() 
                << setw(ANCHO_MAX)  << numeric_limits<double>::max() << endl;
}
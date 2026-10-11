#include "Matriz.hpp"
#include <iostream>
#include <iomanip>
#include <random>
#include <chrono>
#include <functional>

using namespace std;
        //Constructor.
        Matriz::Matriz(int n){
        size=n;
            for (int x = 0; x < 10; x++)
            {
                for (int y = 0; y < 10; y++)
                {
                    data[x][y]=0.0;
                }     
            }
        }   

        //Rellenar los datos de la matriz con numeros reales random.
        void Matriz::RellenarRandom(){

            unsigned seed = chrono::system_clock::now().time_since_epoch().count();
            default_random_engine generator(seed);
            uniform_real_distribution<float> distribution(-100.0, 100.0);
            auto randomFloatGenerator = bind(distribution, generator);

                for (int x = 0; x < size; x++)
                {
                    for (int y = 0; y < size; y++)
                    {
                        data[x][y]=randomFloatGenerator();
                    } 
                }
        }
        //Metodo para imprimir la matriz.
        void Matriz::Imprimir(){
            for (int x = 0; x < size; x++)
            {
                for (int y = 0; y < size; y++)
                {
                    cout << fixed <<setprecision(2) <<setw(10) << data[x][y] <<"\t";
                }    
                cout << endl;
            }

        }

        //Sobrecarga de operador +
        Matriz Matriz::operator +( Matriz& otro) {
            Matriz resultado(size);
            for (int x = 0; x < size; x++)
            {
                for (int y = 0; y < size; y++)
                {
                    resultado.data[x][y] = data[x][y] + otro.data[x][y];
                }
                
            }
            return resultado;

        }
        //Sobrecarga de operador *
        Matriz Matriz::operator *( Matriz& otro) {
            Matriz resultado(size);
            for (int x = 0; x < size; x++)
            {
                for (int y = 0; y < size; y++)
                {
                        for (int z = 0; z < size; z++)
                    {
                        resultado.data[x][y] += data[x][z] * otro.data[z][y];
                    }
                }
            }
            return resultado;

        }


        ;

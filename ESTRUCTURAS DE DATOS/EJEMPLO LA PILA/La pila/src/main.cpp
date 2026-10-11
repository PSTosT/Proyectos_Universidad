#include <iostream>
#include <random>
#include <chrono>
#include <functional>
#include "stack.hpp"

using namespace std;
using namespace chrono;

int main(){
    //Aqui va el default random engine generator para numeros random

    
    int myInt;

    Stack<int> myPila;

    for(int i(0); i < 20; i++){
        myInt = 78; //el numero random

        cout << "Apilando: " << myInt << endl;

        myPila.push(myInt);
        }

    Stack<int> myOtherStack(myPila);

    cout << "Volcado de pila: " << endl;

    while(!myPila.isEmpty()){
        cout << myPila.getTop() << ", ";

        myPila.pop();
        }

    cout << endl << endl;

    cout << "Volcado de pila: " << endl;

    while(!myOtherStack.isEmpty()) {
        cout << myOtherStack.pop() << ", ";
        }

    
    cout << endl << endl;

    cout << "Enter para continuar" << endl;
    cin.get();
}

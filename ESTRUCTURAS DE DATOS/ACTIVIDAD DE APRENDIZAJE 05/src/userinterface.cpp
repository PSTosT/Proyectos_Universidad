#include "userinterface.hpp"
using namespace std;

UserInterface::UserInterface(){ }

void UserInterface::showUserInterface(){
    string myStr;
    Expression myConvertor;
    Queue <char> tempQueue;
    char op;

    cout << "Bienvenido al convertor de expresiones FIJAS a POSFIJAS" << endl; 
    
    do{
        pressEnter();
        clearScreen();

        cout << "Escribe una expresion INFIJA" << endl;
        getline(cin, myStr);
        cout << "Tu expresion INFIJA es: " << myStr << endl;

            myConvertor.receiveInFixed(stringToQueue(myStr));
            tempQueue = myConvertor.toPostfixNotation();
        
        cout << "Tu expresion POSFIJA es: ";
        
            while(!tempQueue.isEmpty()){
                cout << tempQueue.dequeue();
            }

        cout << endl;

        cout << "¿Deseas ingresar otra expresion?(S/N) >> ";
        cin >> op;
        cin.ignore();
        op = toupper(op);
    }while(op != 'N');
    
}
 

void UserInterface::clearScreen(){
    cout << "\x1B[2J\x1B[H";
}

void UserInterface::pressEnter(){
    cout << "\nPresiona Enter para continuar...";
    cin.ignore(10000, '\n'); 
    cin.get();
}

Queue<char> UserInterface::stringToQueue(const string& s) const{
    Queue<char> result;

    for (char c : s){
        if (c != ' ') {
        result.enqueue(c);
    }
    }
    return result;
    
}

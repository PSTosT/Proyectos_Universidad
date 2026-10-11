#include "sortcomp.hpp"
using namespace std;

SortComp::SortComp(){ }

void SortComp::fillA(List<int,100000>& l){
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(0, 1000000);
    auto randomIntGenerator = bind(distribution, generator);
        
        int i(0);
        while (!this->myListA.isFull()){
            
            this->myListA.insData(i+1,randomIntGenerator());
            i++;
        }
}

void SortComp::exBubble(){
    this->myListB = this->myListA;
    auto startTime = chrono::steady_clock::now();

    this->myListB.sortDataBubble();

    auto endTime = chrono::steady_clock::now();
    auto exTime = chrono::duration_cast<chrono::microseconds>(endTime - startTime);

    if(this->myListB.isSorted()) {
        cout << "Ordenado con exito, tiempo de ejecucion Burbuja: " << exTime.count() << " Microsegundos" << endl;
    } else {
        cout << "La lista no fue ordenada..." << endl;
    }
}

void SortComp::exInsert(){
    this->myListB = this->myListA;
    auto startTime = chrono::steady_clock::now();

    this->myListB.sortDataInsert();

    auto endTime = chrono::steady_clock::now();
    auto exTime = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
    
    if(this->myListB.isSorted()) {
        cout << "Ordenado con exito, tiempo de ejecucion Insercion: " << exTime.count() << " Microsegundos" << endl;
    } else {
        cout << "La lista no fue ordenada..." << endl;
    }
}

void SortComp::exSelect(){
    this->myListB = this->myListA;
    auto startTime = chrono::steady_clock::now();

    this->myListB.sortDataSelect();

    auto endTime = chrono::steady_clock::now();
    auto exTime = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
    
    if(this->myListB.isSorted()) {
        cout << "Ordenado con exito, tiempo de ejecucion Seleccion: " << exTime.count() << " Microsegundos" << endl;
    } else {
        cout << "La lista no fue ordenada..." << endl;
    }
}

void SortComp::exShell(){
    this->myListB = this->myListA;
    auto startTime = chrono::steady_clock::now();

    this->myListB.sortDataShell();

    auto endTime = chrono::steady_clock::now();
    auto exTime = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
    
    if(this->myListB.isSorted()) {
        cout << "Ordenado con exito, tiempo de ejecucion Shell: " << exTime.count() << " Microsegundos" << endl;
    } else {
        cout << "La lista no fue ordenada..." << endl;
    }
}

void SortComp::exMerge(){
    this->myListB = this->myListA;
    auto startTime = chrono::steady_clock::now();

    this->myListB.sortDataMerge();

    auto endTime = chrono::steady_clock::now();
    auto exTime = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
    
    if(this->myListB.isSorted()) {
        cout << "Ordenado con exito, tiempo de ejecucion Mezcla: " << exTime.count() << " Microsegundos" << endl;
    } else {
        cout << "La lista no fue ordenada..." << endl;
    }
}

void SortComp::exQuick(){
    this->myListB = this->myListA;
    auto startTime = chrono::steady_clock::now();

    this->myListB.sortDataQuick();

    auto endTime = chrono::steady_clock::now();
    auto exTime = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
    
    if(this->myListB.isSorted()) {
        cout << "Ordenado con exito, tiempo de ejecucion Quick: " << exTime.count() << " Microsegundos" << endl;
    } else {
        cout << "La lista no fue ordenada..." << endl;
    }
}



void SortComp::startComp(){
    cout << "\nPresiona Enter para ORDENAR...";
    cin.ignore();
    cin.get();

    cout << "Ordenando, espera un momento..." << endl;

    this->fillA(this->myListA);

    exBubble();
    exInsert();
    exSelect();
    exShell();
    exMerge();
    exQuick();    

    cout << "\nPresiona Enter para SALIR...";
    cin.ignore();
    cin.get();

}

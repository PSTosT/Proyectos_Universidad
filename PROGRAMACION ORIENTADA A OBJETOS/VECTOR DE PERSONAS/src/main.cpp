#include <iostream>
#include <vector>
#include "student.hpp"
#include <fstream>
#include <sstream>

using namespace std;

//Funciones para la interfaz... (Despues las voy a mover a su propia clase...)
//Hacer una funcion para que puedas actualizar el numero de telefono, donde tengas que poner el telefono una vez para confirmar solamente con 3 intentos 
void clearScreen();
void enterToContinue();
void addPhoneNumber();
void addPhoneNumber(Student&);
void EnviarMSG(const Student &p, string msg);
void clearScreen(){
	cout << "\x1B[2J\x1B[H";
}

void enterToContinue(){
	cout << "\nPresiona Enter para continuar...";
    cin.ignore();
    cin.get();
}

void addPhoneNumber(Student& other){
	string myStr;
	int intento = 0;
	clearScreen();

	cout << "Agregar numero de telefono..." << endl;
	if(other.getPhoneNumber() == "NullPhoneNumber"){
		cout << "No cuenta con numero de telefono" << endl;
		cout << "Escribe el numero de telefono >> ";
		getline(cin, myStr);
		cout << endl;
		other.setPhoneNumber(myStr);
		cout << "El numero de telefono fue actualizado..." << endl;
	} else {
		while(intento < 3){
			cout << "Escribe el numero de telefono anterior para poder actualizarlo" << endl;
			getline(cin,myStr);
			if(other.getPhoneNumber() == myStr){
				cout << "Es correcto!" << endl;
				cout << "Escribe el nuevo numero de telefono >> ";
				getline(cin,myStr);
				cout << endl;
				other.setPhoneNumber(myStr);
				cout << "El numero fue actualizado" << endl;
				break;
			}
			else{
				intento ++;
				
				if (intento <3){
					cout << "El numero es incorrecto, tienes solo 3 intentos. Intento actual = " << intento << endl;
				} else{
					cout << "Sobrepasaste el numero de intentos" << endl;
					break;
				}
				
			} 
		}
	}
	enterToContinue();
}

void EnviarMSG(Student &p, string msg){
	p.RecibeMSG(msg);
}

int main()
{
	Student pruebaNum;
	Student pruebaMsg;
	vector<Student> myStudent;
	int opc;
	string myStr;

	cout << "Bienvenido a tu administrador de estudiantes con vector" << endl;
	enterToContinue();

	do{
	clearScreen();
	cout << "Selecciona una opcion a realizar" << endl;
		
	cout << "1. Agregar estudiante al vector" << endl;
	cout << "2. Mostrar estudiantes actuales" << endl;
	cout << "3. Guardar en disco" << endl;
	cout << "4. Actualizar numero de telefono..." << endl;
	cout << "5. Leer del disco" << endl;  
	cout << "6. Salir del programa" << endl;
	cin >> opc;
	cin.ignore();
	
	switch (opc){
		case 1:{
			clearScreen();
			Student tempStudent;

			cout << "Escribe el nombre del estudiante que deseas agregar" << endl;
			getline(cin, myStr);
            tempStudent.setName(myStr);

			cout << "Escribe el curp del estudiante que deseas agregar" << endl;
			getline(cin, myStr);
            tempStudent.setCurp(myStr);

			cout << "Escribe el numero de telefono del estudiante que deseas agregar" << endl;
			getline(cin, myStr);
            tempStudent.setPhoneNumber(myStr);

            int d, m, y;
            cout << "Escribe el dia de nacimiento (numero)" << endl;
            cin >> d;
            cout << "Escribe el mes de nacimiento (numero)" << endl;
            cin >> m;
            cout << "Escribe el año de nacimiento (numero)" << endl;
            cin >> y;
            cin.ignore();
            tempStudent.setBirthDate(d, m, y);

			myStudent.push_back(tempStudent);
			cout << "Estudiante agregado con exito" << endl;
			}
			enterToContinue();
		break;
		
		case 2: {
			clearScreen();
			cout << "Lista actual: " << endl;
			
			for(int i = 0 ; i < myStudent.size() ; i++){
				cout << myStudent[i].toString() << endl;
				}
			}
			enterToContinue();
		break;
		case 3: {
			clearScreen();
			cout << "Guardar lista en un archivo..." << endl;
			
			cout << "Escribe el nombre del archivo" << endl;
			getline(cin,myStr);

			ofstream myArchivoOut(myStr);
			if(myArchivoOut.is_open()){

			for(auto n : myStudent){
				myArchivoOut << n.getName() << "," << n.getCurp() << "," << n.getPhoneNumber() << "," << n.getBDay() << "," << n.getBMonth() << "," << n.getBYear() << endl;
			}
				myArchivoOut.close();
				cout << "Archivo guardado con exito" << endl;
			}
			else {
				cout << "fue imposible guardar el archivo" << endl;
			}
			enterToContinue();

		}
		break;
		case 4: {
			clearScreen();
			cout << "Tu numero actual es " << pruebaNum.getPhoneNumber() << endl;
			cout << "Actualizar numero de telefono..." << endl;
			addPhoneNumber(pruebaNum);
			cout << "El numero actualizado es" << pruebaNum.getPhoneNumber() << endl;
		}
		break;
		case 5: {
			clearScreen();
			cout << "Leyendo del archivo" << endl << endl;
            cout << "Nombre del archivo: ";
            getline(cin, myStr);

            ifstream myArchivoIn(myStr);
            if(myArchivoIn.is_open()) {
                myStudent.clear();
					string line;
					Student tempStudent;

					while (getline(myArchivoIn, line)){
                        
                        if(line != ""){
                            stringstream ss(line);

                            getline(ss, myStr, ',');
                            tempStudent.setName(myStr);

                            getline(ss, myStr, ',');
                            tempStudent.setCurp(myStr);

                            getline(ss, myStr, ',');
                            tempStudent.setPhoneNumber(myStr);

                            getline(ss, myStr, ',');
                            int d = stoi(myStr);

                            getline(ss, myStr, ',');
                            int m = stoi(myStr);

                            getline(ss, myStr, ',');
                            int y = stoi(myStr);

                            tempStudent.setBirthDate(d, m, y);

						    myStudent.push_back(tempStudent);
                        }
					}
					myArchivoIn.close();
					cout << "Archivo leido con exito" << endl;
					
			} else {
                cout << "No se pudo abrir el archivo" << endl;
            }
			enterToContinue();
		}
		break;
		
		case 6: {
			cout << "Saliendo..." << endl << endl;
            }
		break;
		
		default: {
			clearScreen();
			cout << "Selecciona una opcion correcta..." << endl;
			enterToContinue();
			}
		break;
		
		}
		
		
	}while(opc != 6);

	return 0;
}
#include "userinterface.hpp"
using namespace std;

UserInterface::UserInterface (List<Song, 4000>& l) : myListRef(&l) { 
    int opc;

    cout << "Bienvenido a tu sistema de almacenamiento de lista de exitos de canciones" << endl;
    cleanAndPauseScreen();
    do{  
        cout << "Lista de canciones actual:  " << endl;
        if (myListRef->isEmpty()){
            cout << "La lista de canciones se encuentra vacia... " << endl << endl;
        }
        else {
            cout << myListRef->toString() << endl;
            cout << endl;
        }
        cout << "Selecciona una opcion a realizar sobre la lista de canciones: " << endl;
        cout << "1. Añadir nueva cancion" << endl;
        cout << "2. Eliminar cancion" << endl;
        cout << "3. Guardar lista en un nuevo archivo" << endl;
        cout << "4. Leer lista de un archivo" << endl;
        cout << "5. Buscar una cancion" << endl;
        cout << "6. Ordenar lista de canciones" << endl;
        cout << "7. Salir" << endl;
        cout << ">> ";
        cin >> opc;
        cin.ignore();

        switch (opc)
        {
        case 1: {
            addNewSong();
        }
        break;
        case 2: {
            deleteSong();
        }
            break;
        case 3:{
            writeToDisk();
        }
        break;
        case 4: {
            readFromDisk();
        }
        break;
        case 5: {
            searchSong();
        }
        break;
        case 6: {
            orderSongList();
        }
        break;
        case 7: {
            cout << "Saliendo del programa..." << endl;
        }
        break;
        default: {
            cout << "Opcion invalida..." << endl;
            cleanAndPauseScreen();
        }
            break;
        }
    } while(opc != 7);
}

void UserInterface::cleanAndPauseScreen(){
    cout << "\nPresiona Enter para continuar...";
    cin.ignore(10000, '\n'); 
    cin.get();
    cout << "\x1B[2J\x1B[H";
}

void UserInterface::addNewSong(){
    Song tempSong;
    int tempInt;
    string myStr;
    char op;

    do{
            cout << "Añadir nueva cancion" << endl;
            cleanAndPauseScreen();

            cout << "Nombre de la cancion: >> ";
            getline(cin, myStr);
            tempSong.setSongName(myStr);

            cout << "Nombre del autor: >> ";
            getline(cin, myStr);
            tempSong.setAuthorName(myStr);
           
            cout << "Nombre del cantante: >> ";
            getline(cin, myStr);
            tempSong.setSingerName(myStr);

            cout << "Posicion en el Billboard ranking: >> ";
            cin >> tempInt;
            cin.ignore();
            tempSong.setRankingPos(tempInt);
            
            cout << "Nombre del archivo mp3 (No incluyas la extension): >> ";
            getline(cin, myStr);
            tempSong.setMp3FileName(myStr);

            cout << "En que posicion de la lista deseas insertar la cancion? >> ";
            cin >> tempInt;
            cin.ignore();

            if (myListRef->insData(tempInt - 1, tempSong)){
                cout << "Cancion insertada correctamente" << endl;
            } else {
                cout << "Posicion invalida" << endl;
            }
  
            cleanAndPauseScreen();
            cout << "Cancion agregada... ";
            cout << "Deseas ingresar otra cancion? (S/N) >> ";
            do {
                cin >> op;
                cin.ignore();
                op = toupper(op);
            } while (op != 'N' and op!= 'S');   
            
            cout << "\x1B[2J\x1B[H";
        } while (op == 'S');
}

void UserInterface::deleteSong(){
    int tempInt;
    char op;
    
    do{ 
                cout << "Eliminar cancion de la lista" << endl;
                cleanAndPauseScreen();

                cout << "Que posicion deseas eliminar? >> ";
                cin >> tempInt;
                if (myListRef->delData(tempInt - 1)){
                    cout << "Cancion eliminada con exito" << endl;
                }
                else {
                    cout << "Posicion invalida" << endl;
                }

                cout << "Deseas eliminar otra cancion? (S/N) >> ";

                do {
                    cin >> op;
                    cin.ignore();
                    op = toupper(op);
                } while (op != 'N' and op!= 'S');   
                
                cout << "\x1B[2J\x1B[H";

            } while(op == 'S');
}

void UserInterface::writeToDisk(){
    string myStr;
    cout << "Guardar en archivo " << endl;
            cleanAndPauseScreen();
            cout << "Escribe el nombre del archivo >> ";

            getline(cin, myStr);

            ofstream myArchivoOut(myStr, ios_base::trunc);
            if(myArchivoOut.is_open()) {
                myArchivoOut << *myListRef;
                myArchivoOut.close();
                cout << "Archivo guardado con exito" << endl;
            } else {
                cout << "No se pudo abrir el archivo" << endl;
            }

            cleanAndPauseScreen();
}

void UserInterface::readFromDisk(){
    string myStr;
    cout << "Leyendo del archivo" << endl << endl;
            cout << "Nombre del archivo: ";
            getline(cin, myStr);

            ifstream myArchivoIn(myStr);
            if(myArchivoIn.is_open()) {
                myListRef->delAll(); 
                myArchivoIn >> *myListRef;
                myArchivoIn.close();
                cout << "Archivo leido con exito" << endl;
            } else {
                cout << "No se pudo abrir el archivo" << endl;
            }

            cleanAndPauseScreen();
}

void UserInterface::searchSong(){
    Song tempSong;
    string myStr;

    int subOpc, searchMethod, pos = -1;
            cout << "Buscando una cancion..." << endl;
            cout << "1. Buscar por nombre de la cancion" << endl;
            cout << "2. Buscar por nombre del interprete" << endl;
            cout << ">> ";
            cin >> subOpc;
            cin.ignore();

            if (subOpc == 1 || subOpc == 2) {
                if (subOpc == 1) {
                    cout << "Ingrese el nombre de la cancion a buscar: ";
                    getline(cin, myStr);
                    tempSong.setSongName(myStr);
                } else {
                    cout << "Ingrese el nombre del interprete a buscar: ";
                    getline(cin, myStr);
                    tempSong.setSingerName(myStr);
                }

                cout << "Seleccione el metodo de busqueda:" << endl;
                cout << "1. Busqueda Lineal" << endl;
                cout << "2. Busqueda Binaria" << endl;
                cout << ">> ";
                cin >> searchMethod;
                cin.ignore();

                if (subOpc == 1) {
                    if (searchMethod == 1) {
                        pos = myListRef->findDataL(tempSong, Song::compareByName);
                    } else if (searchMethod == 2) {
                        pos = myListRef->findDataB(tempSong, Song::compareByName);
                    }
                } else {
                    if (searchMethod == 1) {
                        pos = myListRef->findDataL(tempSong, Song::compareBySinger);
                    } else if (searchMethod == 2) {
                        pos = myListRef->findDataB(tempSong, Song::compareBySinger);
                    }
                }

                if (pos != -1) {
                    cout << "\nCancion encontrada en la posicion: " << pos + 1 << endl;
                    cout << "El archivo MP3 es: " << myListRef->retrieve(pos).getMp3FileName() << endl;
                } else {
                    cout << "\nNo se encontro ninguna coincidencia con la busqueda." << endl;
                }
            } else {
                cout << "Opcion invalida..." << endl;
            }
            cleanAndPauseScreen();
}

void UserInterface::orderSongList(){
    int opc;
    int criteria = 0;
    //criteria == 1 es el criterio nombre de cancion
    //criteria == 2 es el criterio nombre de autor
    cout << "Ordenar lista de canciones..." << endl;
    cleanAndPauseScreen();

    do{
        cout << "Selecciona un criterio de ordenamiento" << endl;
        cout << "1. Nombre de la cancion" << endl;
        cout << "2. Nombre del autor" << endl;
        cin >> opc;
        cin.ignore();

        switch (opc)
        {
        case 1:
            criteria = 1; 
            break;
        case 2:
            criteria = 2;
            break;
        
        default:
            cout << "Selecciona una opcion correcta...(1 o 2)" << endl;
            break;
        }
    }while(opc < 1 or opc > 2);

    do{
        cout << "Selecciona un metodo de ordenamiento para la lista!" << endl;

        cout << "1. BubbleSort" << endl;
        cout << "2. InsertSort" << endl;
        cout << "3. SelectSort" << endl;
        cout << "4. ShellSort" << endl;

        cin >> opc;
        cin.ignore();

        switch (opc)
        {
        case 1:{
            if(criteria == 1){
                this->myListRef->sortDataBubble(Song::compareByName);
            } else if (criteria == 2){
                this->myListRef->sortDataBubble(Song::compareBySinger);
            }
            cout << "Se ordeno la lista..." << endl;
        }
            break;
        case 2:{
            if(criteria == 1){
                this->myListRef->sortDataInsert(Song::compareByName);
            } else if (criteria == 2){
                this->myListRef->sortDataInsert(Song::compareBySinger);
            }
            cout << "Se ordeno la lista..." << endl;
        }
            break;
        case 3:{
            if(criteria == 1){
                this->myListRef->sortDataSelect(Song::compareByName);
            } else if (criteria == 2){
                this->myListRef->sortDataSelect(Song::compareBySinger);
            }
            cout << "Se ordeno la lista..." << endl;
        }
            break;
        case 4:{
            if(criteria == 1){
                this->myListRef->sortDataShell(Song::compareByName);
            } else if (criteria == 2){
                this->myListRef->sortDataShell(Song::compareBySinger);
            }
            cout << "Se ordeno la lista..." << endl;
        }
            break;
        
        default:
            cout << "Selecciona una opcion correcta..." << endl;
            break;
        }
    }while(opc < 1 or opc > 4);

    cleanAndPauseScreen();
}

#include "ingredientui.hpp"
using namespace std;

IngredientUI::IngredientUI(List<Ingredient, 1024>& list) : ingredientListRef(list){ }

void IngredientUI::manageIngredient(){
    cout << " --- Gestion de ingredientes --- " << endl << endl;
    int opc(0);

    do{
        clearScreen();

        cout << "Selecciona una opcion a realizar" << endl << endl;
        cout << "1. Agregar ingrediente" << endl;
        cout << "2. Eliminar ingrediente" << endl;
        cout << "3. Modificar cantidad de un ingrediente" << endl;
        cout << "4. Borrar todos los ingredientes" << endl;
        cout << "5. Mostrar ingredientes" << endl;
        cout << "6. Salir..." << endl;

        cout << ">> ";
        cin >> opc;
        cin.ignore();

        switch (opc)
        {
        case 1:{
            addIngredient();
            break;
        }
        case 2:{
            deleteIngredient();
            break;
        }
        case 3:{
            modifyQuantity();
            break;
        }
        case 4:{
            deleteAllIngredients();
            break;
        }
        case 5:{
            showIngredients();
            break;
        }
        case 6:{
            cout << "Saliendo..." << endl;
            enterToContinue();
            break;
        }
        default:
            cout << "Selecciona una de las opciones indicadas..." << endl;
            break;
        }

    } while(opc!=6);
}


void IngredientUI::enterToContinue(){
    std::cout << "\nPresiona Enter para continuar...";
    std::cin.ignore();
    std::cin.get();
}

void IngredientUI::clearScreen(){
    cout << "\033[2J\033[H"; 
}

void IngredientUI::addIngredient(){
    Ingredient tempIng;
    string myStr;
    float myReal;

    clearScreen();
    
    cout << "Escribe el nombre del ingrediente que deseas agregar " << endl;
    cout << ">> ";
    getline(cin, myStr);
    cout << endl;
    tempIng.setName(myStr);

    cout << "Escribe la unidad para este ingrediente (Kg, Lt, Gr, Etc...) " << endl;
    cout << ">> ";
    getline(cin, myStr);
    cout << endl;
    tempIng.setUnit(myStr);

    cout << "Escribe la cantidad de este ingrediente " << endl;
    cout << ">> ";
    cin >> myReal;
    cin.ignore();
    cout << endl;
    tempIng.setQuantity(myReal);

    if(this->ingredientListRef.insertOrdered(tempIng)){
        cout << "Ingrediente agregado con exito!" << endl;
    } else {
        cout << "Imposible agregar el ingrediente..." << endl;
    }

    enterToContinue();

}

void IngredientUI::deleteIngredient(){

    Ingredient tempIng;
    string myStr;
    char myChar;

    clearScreen();
    cout << "Eliminar un ingrediente..." << endl;
    cout << "Escribe el nombre del ingrediente a eliminar >> ";
    getline(cin, myStr);
    tempIng.setName(myStr);

    int pos = (this->ingredientListRef.findDataB(tempIng, Ingredient::compareByName));
        if(pos == -1){
            cout << "No fue posible encontrar el ingrediente..." << endl;
        } else {
            cout << "El ingrediente fue encontrado en la posicion: " << pos << endl;
            
            do{
                cout << "Deseas eliminarlo? (S/N) >> " << endl;
                cin >> myChar;
                cin.ignore();
                myChar = toupper(myChar);

                if(myChar == 'S'){
                    if(this->ingredientListRef.delData(pos)){
                        cout << "Ingrediente eliminado con exito! " << endl;
                    } else {
                        cout << "No fue posible guardar el ingrediente..." << endl;
                    }
                enterToContinue();
                break;

                }
            }while(myChar != 'N');
        }
}

void IngredientUI::modifyQuantity(){
    
    Ingredient tempIng, tempIngQuantity;
    string myStr;
    char myChar;
    float myReal;

    clearScreen();
    cout << "Modificar cantidad de un ingrediente..." << endl;
    cout << "Escribe el nombre del ingrediente a modificar su cantidad >> ";
    getline(cin, myStr);
    tempIng.setName(myStr);

    int pos = (this->ingredientListRef.findDataB(tempIng, Ingredient::compareByName));
        if(pos == -1){
            cout << "No fue posible encontrar el ingrediente..." << endl;
            enterToContinue();
        } else {
            cout << "El ingrediente fue encontrado en la posicion: " << pos << endl;
            
            do{
                cout << "Deseas cambiar su cantidad? (S/N) >> " << endl;
                cin >> myChar;
                cin.ignore();
                myChar = toupper(myChar);

                if(myChar == 'S'){

                    cout << "Escribe la cantidad nueva >> ";
                    cin >> myReal;
                    cin.ignore();
                    
                    this->ingredientListRef.retrieve(pos).setQuantity(myReal);
                
                    cout << "Cantidad modificada con exito! " << endl;
                break;
                
                }
            }while(myChar != 'N');
            enterToContinue();
        }
}

void IngredientUI::deleteAllIngredients(){
    char myChar;
    clearScreen();
    cout << "Eliminar todos los ingredientes..." << endl;
    do{
        cout << "Estas seguro de eliminar todos los ingredientes? (S/N) >> ";
        cin >> myChar;
        cout << endl;
        cin.ignore();
        myChar = toupper(myChar);

        if(myChar == 'S'){
            this->ingredientListRef.delAll();
            cout << "TODOS los ingredientes fueron eliminados con exito, no hay vuelta atras..." << endl;
            break;
        }
    } while(myChar != 'N');

    enterToContinue();
}

void IngredientUI::showIngredients(){
    clearScreen();
    cout << "lista de ingredientes" << endl;
    cout << this->ingredientListRef.toString();
    enterToContinue();
}




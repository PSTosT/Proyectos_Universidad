
#include "recipeui.hpp"
using namespace std;

RecipeUI::RecipeUI(List<Recipe, 1024>& list) : recipeListRef(list) { }

void RecipeUI::manageRecipes(){
    clearScreen();
    cout << "===========================================" << endl;
    cout << "     Bienvenido a tu Recetario Digital    " << endl;
    cout << "===========================================" << endl;
    cout << R"(
            )
       __..---..__
   ,-='  /  |  \  `=-.
  :--..___________..--;
   \.,_____________,./
)"
     << endl;
    enterToContinue();
    int opc(0);
    
    do{
        clearScreen();

        cout << "Selecciona una opcion" << endl;
        cout << "1. Agregar una receta" << endl;
        cout << "2. Buscar una receta" << endl;
        cout << "3. Modificar una receta" << endl;
        cout << "4. Eliminar una receta" << endl;
        cout << "5. Eliminar todas las recetas" << endl;
        cout << "6. Ordenar lista de recetas" << endl;
        cout << "7. Mostrar recetas" << endl;
        cout << "8. Escribir recetas al disco" << endl;
        cout << "9. Leer recetas del disco" << endl;
        cout << "10. Salir" << endl;

        cin >> opc;
        cin.ignore();

        switch(opc){
            case 1:{
                addRecipe();
            }
            break;

            case 2:{
                findRecipe();
            }
            break;

            case 3:{
                modifyRecipe();
            }
            break;

            case 4:{
                deleteRecipe();
            }
            break;

            case 5:{
                deleteAllRecipes();
            }
            break;

            case 6:{
                sortRecipe();
            }
            break;

            case 7:{
                showRecipe();
            }
            break;

            case 8:{
                writeToDisk();
            }
            break;

            case 9:{
                readFromDisk();
            }
            break;

            case 10:{
                cout << "Saliendo..." << endl;
            }
            break;

            default:{

            }
            break;
        }

    }while(opc != 10);
}


void RecipeUI::enterToContinue(){
    std::cout << "\nPresiona Enter para continuar...";
    std::cin.ignore();
    std::cin.get();
}

void RecipeUI::clearScreen(){
    cout << "\033[2J\033[H"; 
}

void RecipeUI::addRecipe(){
    string myStr;
    Recipe myRecipe;
    float myReal;
    int sel;
    char choice;

    clearScreen();
    cout << "Agregar una receta..." << endl;
    cout << "Escribe el nombre de la receta" << endl;
    getline(cin, myStr);
    myRecipe.setName(myStr);

    Name tempName;
    cout << "Escribe el nombre de el autor la receta" << endl;
    getline(cin, myStr);
    tempName.setFirst(myStr);

    cout << "Escribe el apellido de el autor la receta" << endl;
    getline(cin, myStr);
    tempName.setLast(myStr);

    myRecipe.setAuthor(tempName);

    cout << "Escribe el tiempo de preparacion (Minutos) de la receta" << endl;
    cin >> myReal;
    cin.ignore();
    myRecipe.setPrepTime(myReal);

    cout << "Escribe el procedimiento de la receta" << endl;
    getline(cin, myStr);
    myRecipe.setProcedure(myStr);
    
        do{
            cout << "Selecciona la categoria de la receta" << endl;
            cout << "1. Desayuno" << endl;
            cout << "2. Comida" << endl;
            cout << "3. Cena" << endl;
            cout << "4. Navideno" << endl << ">> ";

            cin >> sel;
            cin.ignore();

            switch (sel)
            {
            case 1:
                myRecipe.setCategory("Desayuno");
                break;
            
            case 2:
                myRecipe.setCategory("Comida");
                break;

            case 3:
                myRecipe.setCategory("Cena");
                break;
            
            case 4:
                myRecipe.setCategory("Navideno");
                break;

            default:
                cout << "Selecciona una opcion correcta" << endl;
                break;
            }
        }while(sel < 1 or sel > 4);

    cout << "¿Deseas administrar sus ingredientes? (S/N)" << endl;
    cin >> choice;
    cin.ignore();
    choice = toupper(choice);
    if(choice == 'S'){
        IngredientUI myIngredientUI(myRecipe.getIngredientList());
        myIngredientUI.manageIngredient();
    }

    this->recipeListRef.insData(this->recipeListRef.getLastPos() + 1, myRecipe);
    cout << "Receta agregada..." << endl;
}

void RecipeUI::showRecipe(){
    char opc;
    string category = "";
    int sel;
    Recipe myRecipe;
    bool myBool = false;
    bool entradas = false;

    clearScreen();
    cout << "Mostrar lista de recetas..." << endl;
    cout << "Deseas filtrar la lista por categoria (S/N)" << endl;
    cin >> opc;
    cin.ignore();
    opc = toupper(opc);
    if(opc == 'S'){
        do{
        cout << "Selecciona la categoria" << endl;
        cout << "1. Desayuno" << endl;
        cout << "2. Comida" << endl;
        cout << "3. Cena" << endl;
        cout << "4. Navideno" << endl;
        cout << ">>";
        cin >> sel;
        cin.ignore();
        cout << endl;

        switch (sel)
        {
        case 1:
            category = "Desayuno";
            break;
        case 2:
            category = "Comida";
            break;
        case 3:
            category = "Cena";
            break;
        case 4:
            category = "Navideno";
            break;

        default:
            cout << "Selecciona una opcion correcta" << endl;
            break;
        }

        myRecipe.setCategory(category);
        }while(sel < 1 or sel > 4);

    }

    cout << "¿Deseas mostrar los ingredientes?(S/N)" << endl;
        cin >> opc;
        cin.ignore();
        opc = toupper(opc);
        if(opc == 'S'){
            myBool = true;
        }
        clearScreen();

        cout << "Lista de Recetas:" << endl;
        
        
        for(int i(0); i <= this->recipeListRef.getLastPos(); i++){
            
            Recipe& tempRecipe = this->recipeListRef.retrieve(i);
            if(category == "" or tempRecipe.getCategory() == category){

                cout << " | " << left << setw(wRecipeName) << "NOMBRE DE LA RECETA";
                cout << " | " << left << setw(wAuthorName) << "AUTOR";
                cout << " | " << left << setw(wPrepTime) << "MINUTOS DE PREPARACION";
                cout << " | " << left << setw(wCategory) << "CATEGORIA" << " | " << endl;
                
                cout << tempRecipe.toString(myBool) << endl;
                entradas = true;
                }
            }
        if(entradas == false){
                cout << "Sin elementos" << endl;
            }
    enterToContinue();
    
}

void RecipeUI::findRecipe(){
    int opc;
    string myStr;

    clearScreen();
    cout << "Buscar una receta..." << endl;
    enterToContinue();
    do{
        clearScreen();
        cout << "Selecciona el criterio de busqueda" << endl;
        cout << "1. Nombre del platillo" << endl;
        cout << "2. Nombre del autor" << endl;
        cout << ">> ";

        cin >> opc;
        cin.ignore();

        switch (opc)
        {
        case 1:{
            int pos;

            cout << "Escribe el nombre del platillo >> ";
            getline(cin, myStr);
            Recipe tempRecipe;
            tempRecipe.setName(myStr);

            if(this->recipeListRef.isSorted(Recipe::compareByName)){
            pos = this->recipeListRef.findDataB(tempRecipe, Recipe::compareByName);
            } else {
                pos = this->recipeListRef.findDataL(tempRecipe, Recipe::compareByName);
            }

            if(pos == -1){
                cout << "La receta no fue encontrada..." << endl;
                } else{
                cout << "La receta fue encontrada" << endl;
                cout << this->recipeListRef.retrieve(pos).toString() << endl;
                }
        
        }
        break;

        case 2:{
            int pos;
            Recipe tempRecipe;
            Name tempName;

            cout << "Escribe el nombre del autor >> ";
            getline(cin, myStr);
            tempName.setFirst(myStr);

            cout << "Escribe el apellido del autor >> ";
            getline(cin, myStr);
            tempName.setLast(myStr);
            tempRecipe.setAuthor(tempName);

            if(this->recipeListRef.isSorted(Recipe::compareByName)){
                pos = this->recipeListRef.findDataB(tempRecipe, Recipe::compareByAuthor);
            } else {
                pos = this->recipeListRef.findDataL(tempRecipe, Recipe::compareByAuthor);
            }


            if(pos == -1){
                cout << "La receta no fue encontrada..." << endl;
                } else{
                cout << "La primer receta es la siguiente:" << endl;
                cout << this->recipeListRef.retrieve(pos).toString() << endl;
                }
        }
        break;
        
        default:
        cout << "Selecciona una opcion correcta" << endl;
        break;
        }
    }while(opc < 1 or opc > 2);
    enterToContinue();
}

void RecipeUI::deleteRecipe(){
    string myStr;
    char opc;
    int pos;

    clearScreen();
    cout << "Eliminar una receta..." << endl;
    cout << "Escribe el nombre de la receta que deseas eliminar >> ";
    getline(cin,myStr); 

    Recipe tempRecipe;
    tempRecipe.setName(myStr);

    if(this->recipeListRef.isSorted(Recipe::compareByName)){
        pos = this->recipeListRef.findDataB(tempRecipe, Recipe::compareByName);
    } else {
        pos = this->recipeListRef.findDataL(tempRecipe, Recipe::compareByName);
    }

    if(pos == -1){
        cout << "Receta no encontrada..." << endl;
    } else{
        cout << "Receta encontrada:" << endl;
        cout << this->recipeListRef.retrieve(pos).toString() << endl;
        cout << "Estas seguro de que deseas eliminarla?(S/N)" << endl;
        do{
            cin >> opc;
            cin.ignore();
            opc = toupper(opc);

            if(opc == 'S'){
                this->recipeListRef.delData(pos);
                cout << "Receta exterminada..." << endl;
            } 
            else if(opc == 'N'){
                cout << "Cancelando..." << endl;
            }
            else{
                cout << "opcion invalida" << endl;
            }
        }while(opc != 'N' and opc != 'S'); 
    }
    enterToContinue();
}

void RecipeUI::deleteAllRecipes(){
    char opc;

    clearScreen();
    cout << "Eliminar todas las recetas..." << endl;  
    cout << "Estas seguro de eliminar TODAS LAS RECETAS? (S/N) >> ";
    do{
        cin >> opc;
        cin.ignore();
        opc = toupper(opc);

        if(opc == 'S'){
                this->recipeListRef.delAll();
                cout << "TODAS LAS RECETAS FUERON ELIMINADAS" << endl;
            } else if (opc == 'N'){
                cout << "Cancelando..." << endl;
            } else {
                cout << "Selecciona una opcion correcta (N/S)..." << endl;
        }
    }while(opc != 'N' and opc != 'S');
    enterToContinue();
}

void RecipeUI::modifyRecipe(){
    string myStr;
    int opc;
    int tempTime;
    int pos;
    clearScreen();
    cout << "Modificar receta..." << endl;
    cout << "Escribe el nombre de la receta que deseas modificar >> ";
    getline(cin,myStr);
    cout << endl;

    Recipe tempRecipe;
    tempRecipe.setName(myStr);
    
    if(this->recipeListRef.isSorted(Recipe::compareByName)){
        pos = this->recipeListRef.findDataB(tempRecipe, Recipe::compareByName);
    } else {
        pos = this->recipeListRef.findDataL(tempRecipe, Recipe::compareByName);
    }

    if(pos == -1){
        cout << "Receta no encontrada..." << endl;
    } else{
        cout << "Receta encontrada:" << endl;
        cout << this->recipeListRef.retrieve(pos).toString() << endl;
        do{
            cout << "Selecciona una opcion" << endl;
            cout << "1. Cambiar procedimiento" << endl;
            cout << "2. Cambiar tiempo de preparacion" << endl;
            cout << "3. Modificar ingredientes" << endl;
            cin >> opc;
            cin.ignore();

            switch (opc)
            {
            case 1:{
                cout << "Escribe el nuevo procedimiento" << endl << ">> ";
                getline(cin,myStr);
                this->recipeListRef.retrieve(pos).setProcedure(myStr);
                cout << "Proceso actualizado..." << endl;
                break;
                }
            case 2:{
                cout << "Escribe el nuevo tiempo de preparacion (minutos)" << endl;
                cin >> tempTime;
                cin.ignore();
                this->recipeListRef.retrieve(pos).setPrepTime(tempTime);
                cout << "Tiempo de preparacion actualizado..." << endl;
                break;
                }
            case 3: {
                cout << "Modificar ingredientes..." << endl;
                enterToContinue();
                IngredientUI myIngredientUI(this->recipeListRef.retrieve(pos).getIngredientList());
                myIngredientUI.manageIngredient();
                break;
                }
            default:
                cout << "Selecciona una opcion correcta..." << endl;
            break;
            }
        }while(opc < 1 or opc > 3);
    }
    enterToContinue();
}

void RecipeUI::sortRecipe(){
    clearScreen();

    int opc;

    cout << "Ordenar las recetas" << endl;

    cout << "Selecciona una opcion: " << endl;
    cout << "1. Ordenar por nombre de la receta" << endl;
    cout << "2. Ordenar por tiempo de preparacion" << endl;
    do{
        cin >> opc;
        cin.ignore();

        switch(opc){

        case 1: {
            cout << "Ordenando por nombre de la receta..." << endl;
            this->recipeListRef.sortDataQuick(Recipe::compareByName);
            cout << "La lista fue ordenada por nombre!" << endl;
        }
        break;
        
        case 2: {
            cout << "Ordenando por tiempo de preparacion..." << endl;
            this->recipeListRef.sortDataQuick(Recipe::compareByPrepTime);
            cout << "La lista fue ordenada por tiempo de preparacion!" << endl;
        }
        break;
        
        default: {
            cout << "Selecciona una opcion correcta..." << endl;
        }
        break;
        }
    }while(opc < 1 or opc > 2);
    enterToContinue();
}

void RecipeUI::writeToDisk(){
    ofstream myFile;
    string myStr;

    clearScreen();

    cout << "Escribir el recetario al disco..." << endl;

    cout << "Con que nombre deseas guardar el archivo?" << endl;
    getline(cin,myStr);

    myFile.open(myStr, ios_base::trunc);

    if(myFile.is_open()){
        myFile << recipeListRef.serialize('|');

        myFile.close();

        cout << "El recetario se guardo correctamente..." << endl;

    } else {
        cout << "Fue imposible abrir el archivo" << endl;
    }

    enterToContinue();
}

void RecipeUI::readFromDisk(){
    ifstream myFile;
    string myStr;

    clearScreen();

    cout << "Nombre del archivo que deseas leer (incluye la extension)" << endl;
    getline(cin,myStr);

    myFile.open(myStr);

    if(myFile.is_open()){
        getline(myFile, myStr);

        recipeListRef.deserialize(myStr,'|');

        cout << "Recetario recuperado!" << endl;
    } else {
        cout << "Fue imposible abrir el archivo" << endl;
    }

    enterToContinue();
}



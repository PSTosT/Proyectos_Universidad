
#include "recipeui.hpp"



using namespace std;

int main(void){
    DList<Recipe>* miDListaDeRecetas = new DList<Recipe>();
    
    RecipeUI ui(*miDListaDeRecetas);
    ui.manageRecipes();
    delete miDListaDeRecetas;
    
    return 0;
}

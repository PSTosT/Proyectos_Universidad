
#include "list.hpp"
#include "recipe.hpp"
#include "recipeui.hpp"

using namespace std;

int main(void){
    List<Recipe, 1024>* miListaDeRecetas = new List<Recipe, 1024>();
    
    RecipeUI ui(*miListaDeRecetas);
    ui.manageRecipes();
    delete miListaDeRecetas;
    
    return 0;
}

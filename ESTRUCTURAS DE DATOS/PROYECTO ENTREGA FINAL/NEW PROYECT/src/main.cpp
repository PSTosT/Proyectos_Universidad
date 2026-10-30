
#include "slist.hpp"
#include "ingredientui.hpp"

using namespace std;

int main(void){
    SList<Ingredient>* miSListaDeIngredientes = new SList<Ingredient>();
    
    IngredientUI ui(*miSListaDeIngredientes);
    ui.manageIngredient();
    delete miSListaDeIngredientes;
    
    return 0;
}

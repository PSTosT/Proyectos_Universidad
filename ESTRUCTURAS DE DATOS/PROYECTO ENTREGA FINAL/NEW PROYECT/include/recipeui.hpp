#ifndef __RECIPEUI_H__
#define __RECIPEUI_H__

#include "recipe.hpp"
#include "list"
#include "ingredient.hpp"
#include "ingredientui.hpp"
#include "name.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip> 

class RecipeUI{
    private:
        DList<Recipe>& recipeListRef;
        void enterToContinue();
        void clearScreen();
        void addRecipe();
        void showRecipe();
        void findRecipe();
        void deleteRecipe();
        void deleteAllRecipes();
        void modifyRecipe();
        void sortRecipe();
        void writeToDisk();
        void readFromDisk();       
    public:
        RecipeUI(DList<Recipe>& list);
        void manageRecipes();
        
};
#endif // __RECIPEUI_H__R
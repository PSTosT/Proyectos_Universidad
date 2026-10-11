#ifndef __INGREDIENTUI_H__
#define __INGREDIENTUI_H__

#include "ingredient.hpp"
#include "list.hpp"
#include <iostream>
#include <string>
#include <sstream>

class IngredientUI{
    private:
        List<Ingredient, 1024>& ingredientListRef;

        void enterToContinue();
        void clearScreen();
        void addIngredient();
        void deleteIngredient();
        void modifyQuantity();
        void deleteAllIngredients();
        void showIngredients();
    public:
        IngredientUI (List<Ingredient, 1024>& list);
        void manageIngredient();
};
#endif // __INGREDIENTUI_H__
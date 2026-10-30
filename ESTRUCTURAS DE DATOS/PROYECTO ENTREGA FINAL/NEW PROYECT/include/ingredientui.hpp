#ifndef __INGREDIENTUI_H__
#define __INGREDIENTUI_H__

#include "ingredient.hpp"
#include "slist.hpp"
#include <iostream>
#include <string>
#include <sstream>

class IngredientUI{
    private:
        SList<Ingredient>& ingredientSListRef;

        void enterToContinue();
        void clearScreen();
        void addIngredient();
        void deleteIngredient();
        void modifyQuantity();
        void deleteAllIngredients();
        void showIngredients();
    public:
        IngredientUI (SList<Ingredient>& list);
        void manageIngredient();
};
#endif // __INGREDIENTUI_H__
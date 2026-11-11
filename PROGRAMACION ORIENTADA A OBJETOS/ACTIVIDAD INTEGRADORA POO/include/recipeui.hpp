#ifndef __RECIPEUI_H__
#define __RECIPEUI_H__

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/notebook.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "recipe.hpp"
#include "ingredient.hpp"
#include "ingredientui.hpp"
#include "name.hpp"
#include "chef.hpp"

class RecipeUI : public wxFrame {
private:
    std::vector<Recipe>& recipeListRef;
    std::vector<Chef> chefList;
    std::vector<int> displayedIndices; // Indices reales en recipeListRef mostrados en la tabla
    int selectedRecipePos;             // Posicion real dentro de recipeListRef
    int selectedChefPos;               // Posicion real dentro de chefList

    // Controles de la pestaña de Recetas
    wxNotebook* notebook;
    wxListCtrl* recipeTable;
    wxChoice* choiceFilterCategory;
    wxChoice* choiceSearchCriteria;
    wxTextCtrl* txtSearch;

    // Formulario de creacion/edicion de Receta
    wxTextCtrl* txtRecipeName;
    wxTextCtrl* txtAuthorFirst;
    wxTextCtrl* txtAuthorLast;
    wxChoice* choiceChefSelector;
    wxTextCtrl* txtPrepTime;
    wxChoice* choiceCategory;
    wxTextCtrl* txtProcedure;
    std::vector<Ingredient> tempIngredients; // Ingredientes temporales para nueva receta

    // Visor de detalle de receta seleccionada
    wxTextCtrl* txtRecipeDetail;

    // Controles de la pestaña de Chefs (Herencia Persona -> Chef)
    wxListCtrl* chefTable;
    wxTextCtrl* txtChefFirst;
    wxTextCtrl* txtChefLast;
    wxTextCtrl* txtChefAge;
    wxTextCtrl* txtChefSpecialty;
    wxTextCtrl* txtChefExp;
    wxTextCtrl* txtPolymorphismOutput;

    // Metodos internos de inicializacion y refresco
    void initDefaultChefs();
    wxPanel* createRecipesPage(wxWindow* parent);
    wxPanel* createChefsPage(wxWindow* parent);

    void refreshRecipeTable(const std::string& filterCategory = "Todas");
    void refreshChefTable();
    void updateChefChoiceSelector();
    void showRecipeDetails(int realIndex);

    // Eventos de Recetas (equivalentes a los metodos de RecipeUI en EDD)
    void onSelectRecipe(wxListEvent& event);
    void onAddRecipe(wxCommandEvent& event);
    void onModifyRecipe(wxCommandEvent& event);
    void onDeleteRecipe(wxCommandEvent& event);
    void onDeleteAllRecipes(wxCommandEvent& event);
    void onManageIngredients(wxCommandEvent& event);
    void onFindRecipe(wxCommandEvent& event);
    void onFilterCategory(wxCommandEvent& event);
    void onSortByName(wxCommandEvent& event);
    void onSortByPrepTime(wxCommandEvent& event);
    void onWriteToDisk(wxCommandEvent& event);
    void onReadFromDisk(wxCommandEvent& event);
    void onChefSelectedForRecipe(wxCommandEvent& event);
    void onClearRecipeForm(wxCommandEvent& event);

    // Eventos de Chefs (CRUD de clase Chef + Demostracion de Polimorfismo)
    void onSelectChef(wxListEvent& event);
    void onAddChef(wxCommandEvent& event);
    void onModifyChef(wxCommandEvent& event);
    void onDeleteChef(wxCommandEvent& event);
    void onDemonstratePolymorphism(wxCommandEvent& event);

public:
    RecipeUI(std::vector<Recipe>& list);
    void loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename);
};

#endif // __RECIPEUI_H__

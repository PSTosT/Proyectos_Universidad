#ifndef __INGREDIENTUI_H__
#define __INGREDIENTUI_H__

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <vector>
#include <string>
#include <algorithm>
#include "ingredient.hpp"

class IngredientUI : public wxDialog {
private:
    std::vector<Ingredient>& ingredientListRef;
    int selectedIndex;

    wxListCtrl* listCtrl;
    wxTextCtrl* txtName;
    wxTextCtrl* txtQuantity;
    wxTextCtrl* txtUnit;

    void refreshTable();
    void onSelectIngredient(wxListEvent& event);
    void onAddIngredient(wxCommandEvent& event);
    void onModifyQuantity(wxCommandEvent& event);
    void onDeleteIngredient(wxCommandEvent& event);
    void onDeleteAllIngredients(wxCommandEvent& event);
    void onCloseDialog(wxCommandEvent& event);

public:
    IngredientUI(wxWindow* parent, std::vector<Ingredient>& list, const std::string& recipeTitle = "");
    void manageIngredient();
};

#endif // __INGREDIENTUI_H__

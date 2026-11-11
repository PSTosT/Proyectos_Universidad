#include <wx/wx.h>
#include <vector>
#include "recipe.hpp"
#include "recipeui.hpp"

using namespace std;

class RecetarioApp : public wxApp {
private:
    std::vector<Recipe> miListaDeRecetas;

public:
    virtual bool OnInit() override {
        RecipeUI* ui = new RecipeUI(miListaDeRecetas);
        ui->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(RecetarioApp);

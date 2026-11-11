#include "ingredientui.hpp"
#include <sstream>
#include <iomanip>

using namespace std;

IngredientUI::IngredientUI(wxWindow* parent, std::vector<Ingredient>& list, const std::string& recipeTitle)
    : wxDialog(parent, wxID_ANY,
               wxString::FromUTF8(recipeTitle.empty()
                   ? "Gestion de Ingredientes"
                   : "Gestion de Ingredientes - " + recipeTitle),
               wxDefaultPosition, wxSize(640, 480),
               wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER),
      ingredientListRef(list),
      selectedIndex(-1) {

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Encabezado
    wxStaticText* lblHeader = new wxStaticText(
        this, wxID_ANY,
        wxString::FromUTF8("Administracion de Ingredientes de la Receta (std::vector<Ingredient>)"));
    wxFont headerFont = lblHeader->GetFont();
    headerFont.SetPointSize(12);
    headerFont.SetWeight(wxFONTWEIGHT_BOLD);
    lblHeader->SetFont(headerFont);
    mainSizer->Add(lblHeader, 0, wxALL, 10);

    // Tabla de ingredientes
    listCtrl = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxSize(-1, 200),
                              wxLC_REPORT | wxLC_SINGLE_SEL | wxBORDER_SUNKEN);
    listCtrl->InsertColumn(0, "Pos", wxLIST_FORMAT_LEFT, 55);
    listCtrl->InsertColumn(1, "Ingrediente", wxLIST_FORMAT_LEFT, 240);
    listCtrl->InsertColumn(2, "Cantidad", wxLIST_FORMAT_LEFT, 130);
    listCtrl->InsertColumn(3, "Unidad", wxLIST_FORMAT_LEFT, 160);
    mainSizer->Add(listCtrl, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);

    // Formulario de captura / edicion
    wxStaticBoxSizer* formBox = new wxStaticBoxSizer(wxVERTICAL, this, "Datos del Ingrediente");
    wxFlexGridSizer* grid = new wxFlexGridSizer(3, 2, 8, 12);
    grid->AddGrowableCol(1, 1);

    grid->Add(new wxStaticText(this, wxID_ANY, "Nombre del ingrediente:"), 0, wxALIGN_CENTER_VERTICAL);
    txtName = new wxTextCtrl(this, wxID_ANY);
    grid->Add(txtName, 1, wxEXPAND);

    grid->Add(new wxStaticText(this, wxID_ANY, "Cantidad:"), 0, wxALIGN_CENTER_VERTICAL);
    txtQuantity = new wxTextCtrl(this, wxID_ANY);
    grid->Add(txtQuantity, 1, wxEXPAND);

    grid->Add(new wxStaticText(this, wxID_ANY, "Unidad (Gramos, Kg, Lt, Piezas...):"), 0, wxALIGN_CENTER_VERTICAL);
    txtUnit = new wxTextCtrl(this, wxID_ANY);
    grid->Add(txtUnit, 1, wxEXPAND);

    formBox->Add(grid, 1, wxEXPAND | wxALL, 8);
    mainSizer->Add(formBox, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);

    // Botones de accion (mismas opciones que el menu original de IngredientUI)
    wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton* btnAdd = new wxButton(this, wxID_ANY, "1. Agregar");
    wxButton* btnModify = new wxButton(this, wxID_ANY, "2. Modificar Cantidad");
    wxButton* btnDelete = new wxButton(this, wxID_ANY, "3. Eliminar");
    wxButton* btnDeleteAll = new wxButton(this, wxID_ANY, "4. Borrar Todos");
    wxButton* btnClose = new wxButton(this, wxID_OK, "5. Guardar y Salir");

    btnSizer->Add(btnAdd, 0, wxRIGHT, 6);
    btnSizer->Add(btnModify, 0, wxRIGHT, 6);
    btnSizer->Add(btnDelete, 0, wxRIGHT, 6);
    btnSizer->Add(btnDeleteAll, 0, wxRIGHT, 6);
    btnSizer->AddStretchSpacer(1);
    btnSizer->Add(btnClose, 0);

    mainSizer->Add(btnSizer, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);

    SetSizer(mainSizer);
    CentreOnParent();

    // Eventos
    listCtrl->Bind(wxEVT_LIST_ITEM_SELECTED, &IngredientUI::onSelectIngredient, this);
    btnAdd->Bind(wxEVT_BUTTON, &IngredientUI::onAddIngredient, this);
    btnModify->Bind(wxEVT_BUTTON, &IngredientUI::onModifyQuantity, this);
    btnDelete->Bind(wxEVT_BUTTON, &IngredientUI::onDeleteIngredient, this);
    btnDeleteAll->Bind(wxEVT_BUTTON, &IngredientUI::onDeleteAllIngredients, this);
    btnClose->Bind(wxEVT_BUTTON, &IngredientUI::onCloseDialog, this);

    refreshTable();
    if (!this->ingredientListRef.empty()) {
        selectedIndex = 0;
        const Ingredient& ing = this->ingredientListRef[0];
        txtName->SetValue(wxString::FromUTF8(ing.getName()));
        stringstream ss;
        ss << fixed << setprecision(2) << ing.getQuantity();
        txtQuantity->SetValue(ss.str());
        txtUnit->SetValue(wxString::FromUTF8(ing.getUnit()));
    }
}

void IngredientUI::manageIngredient() {
    ShowModal();
}

void IngredientUI::refreshTable() {
    listCtrl->DeleteAllItems();
    for (size_t i = 0; i < this->ingredientListRef.size(); i++) {
        const Ingredient& ing = this->ingredientListRef[i];
        long idx = listCtrl->InsertItem(i, to_string(i));
        listCtrl->SetItem(idx, 1, wxString::FromUTF8(ing.getName()));

        stringstream ss;
        ss << fixed << setprecision(2) << ing.getQuantity();
        listCtrl->SetItem(idx, 2, ss.str());
        listCtrl->SetItem(idx, 3, wxString::FromUTF8(ing.getUnit()));
    }
    listCtrl->Refresh();
    listCtrl->Update();
}

void IngredientUI::onSelectIngredient(wxListEvent& event) {
    selectedIndex = event.GetIndex();
    if (selectedIndex >= 0 && selectedIndex < static_cast<int>(this->ingredientListRef.size())) {
        const Ingredient& ing = this->ingredientListRef[selectedIndex];
        txtName->SetValue(wxString::FromUTF8(ing.getName()));
        stringstream ss;
        ss << fixed << setprecision(2) << ing.getQuantity();
        txtQuantity->SetValue(ss.str());
        txtUnit->SetValue(wxString::FromUTF8(ing.getUnit()));
    }
}

void IngredientUI::onAddIngredient(wxCommandEvent&) {
    string nameStr = txtName->GetValue().ToUTF8().data();
    string qtyStr = txtQuantity->GetValue().ToUTF8().data();
    string unitStr = txtUnit->GetValue().ToUTF8().data();

    if (nameStr.empty() || qtyStr.empty() || unitStr.empty()) {
        wxMessageBox("Por favor llena el nombre, la cantidad y la unidad del ingrediente.",
                     "Campos incompletos", wxOK | wxICON_WARNING, this);
        return;
    }

    float qty = 0.0f;
    try {
        qty = stof(qtyStr);
    } catch (...) {
        wxMessageBox("La cantidad debe ser un numero valido.", "Error", wxOK | wxICON_ERROR, this);
        return;
    }

    Ingredient tempIng;
    tempIng.setName(nameStr);
    tempIng.setQuantity(qty);
    tempIng.setUnit(unitStr);

    this->ingredientListRef.push_back(tempIng);
    std::sort(this->ingredientListRef.begin(), this->ingredientListRef.end());

    txtName->Clear();
    txtQuantity->Clear();
    txtUnit->Clear();
    selectedIndex = -1;
    refreshTable();
    if (!this->ingredientListRef.empty()) {
        selectedIndex = 0;
        const Ingredient& ing = this->ingredientListRef[0];
        txtName->SetValue(wxString::FromUTF8(ing.getName()));
        stringstream ss;
        ss << fixed << setprecision(2) << ing.getQuantity();
        txtQuantity->SetValue(ss.str());
        txtUnit->SetValue(wxString::FromUTF8(ing.getUnit()));
    }
}

void IngredientUI::onModifyQuantity(wxCommandEvent&) {
    string nameStr = txtName->GetValue().ToUTF8().data();
    string qtyStr = txtQuantity->GetValue().ToUTF8().data();
    string unitStr = txtUnit->GetValue().ToUTF8().data();

    int pos = selectedIndex;
    if (pos < 0 || pos >= static_cast<int>(this->ingredientListRef.size())) {
        // Buscar por nombre si no selecciono con clic
        for (size_t i = 0; i < this->ingredientListRef.size(); i++) {
            if (this->ingredientListRef[i].getName() == nameStr) {
                pos = static_cast<int>(i);
                break;
            }
        }
    }

    if (pos < 0 || pos >= static_cast<int>(this->ingredientListRef.size())) {
        wxMessageBox("Selecciona un ingrediente de la tabla o escribe su nombre exacto para modificarlo.",
                     "Ingrediente no encontrado", wxOK | wxICON_WARNING, this);
        return;
    }

    float qty = 0.0f;
    try {
        qty = stof(qtyStr);
    } catch (...) {
        wxMessageBox("Escribe una cantidad numerica valida.", "Error", wxOK | wxICON_ERROR, this);
        return;
    }

    if (!nameStr.empty()) {
        this->ingredientListRef[pos].setName(nameStr);
    }
    this->ingredientListRef[pos].setQuantity(qty);
    if (!unitStr.empty()) {
        this->ingredientListRef[pos].setUnit(unitStr);
    }

    refreshTable();
    wxMessageBox("Ingrediente modificado con exito!", "Actualizado", wxOK | wxICON_INFORMATION, this);
}

void IngredientUI::onDeleteIngredient(wxCommandEvent&) {
    string nameStr = txtName->GetValue().ToUTF8().data();
    int pos = selectedIndex;

    if (pos < 0 || pos >= static_cast<int>(this->ingredientListRef.size())) {
        for (size_t i = 0; i < this->ingredientListRef.size(); i++) {
            if (this->ingredientListRef[i].getName() == nameStr) {
                pos = static_cast<int>(i);
                break;
            }
        }
    }

    if (pos < 0 || pos >= static_cast<int>(this->ingredientListRef.size())) {
        wxMessageBox("Selecciona un ingrediente de la tabla para eliminarlo.",
                     "Sin seleccion", wxOK | wxICON_WARNING, this);
        return;
    }

    string targetName = this->ingredientListRef[pos].getName();
    int resp = wxMessageBox(
        wxString::FromUTF8("¿Deseas eliminar el ingrediente '" + targetName + "'?"),
        "Confirmar eliminacion", wxYES_NO | wxICON_QUESTION, this);

    if (resp == wxYES) {
        this->ingredientListRef.erase(this->ingredientListRef.begin() + pos);
        selectedIndex = -1;
        txtName->Clear();
        txtQuantity->Clear();
        txtUnit->Clear();
        refreshTable();
    }
}

void IngredientUI::onDeleteAllIngredients(wxCommandEvent&) {
    if (this->ingredientListRef.empty()) {
        wxMessageBox("La lista de ingredientes ya esta vacia.", "Aviso", wxOK | wxICON_INFORMATION, this);
        return;
    }

    int resp = wxMessageBox("¿Estas seguro de eliminar TODOS los ingredientes de esta receta?",
                            "Confirmar", wxYES_NO | wxICON_WARNING, this);
    if (resp == wxYES) {
        this->ingredientListRef.clear();
        selectedIndex = -1;
        refreshTable();
    }
}

void IngredientUI::onCloseDialog(wxCommandEvent&) {
    EndModal(wxID_OK);
}

#include "recipeui.hpp"

using namespace std;

RecipeUI::RecipeUI(std::vector<Recipe>& list)
    : wxFrame(nullptr, wxID_ANY,
              wxString::FromUTF8("Recetario Digital POO - CUCEI (wxWidgets + std::vector)"),
              wxDefaultPosition, wxSize(1120, 740)),
      recipeListRef(list),
      selectedRecipePos(-1),
      selectedChefPos(-1) {

    CreateStatusBar();
    SetStatusText(wxString::FromUTF8("Bienvenido a tu Recetario Digital - Actividad Integradora POO"));

    initDefaultChefs();

    wxBoxSizer* rootSizer = new wxBoxSizer(wxVERTICAL);
    notebook = new wxNotebook(this, wxID_ANY);

    notebook->AddPage(createRecipesPage(notebook), wxString::FromUTF8("1. Recetario Digital (Recetas e Ingredientes)"), true);
    notebook->AddPage(createChefsPage(notebook), wxString::FromUTF8("2. Autores / Chefs (Herencia y Polimorfismo)"), false);

    rootSizer->Add(notebook, 1, wxEXPAND | wxALL, 6);
    SetSizer(rootSizer);
    Centre();

    // Intentar cargar recetas.txt automaticamente al iniciar
    ifstream checkFile("recetas.txt");
    if (checkFile.is_open()) {
        checkFile.close();
        loadFromFile("recetas.txt");
    } else {
        refreshRecipeTable();
    }
    refreshChefTable();
    updateChefChoiceSelector();
}

void RecipeUI::initDefaultChefs() {
    chefList.push_back(Chef(Name("Ana", "Garcia"), 34, "Cocina Navidena y Tradicional", 12));
    chefList.push_back(Chef(Name("Luis", "Martinez"), 41, "Carnes y Horno", 18));
    chefList.push_back(Chef(Name("Carlos", "Hernandez"), 29, "Desayunos Mexicanos", 7));
    chefList.push_back(Chef(Name("Juan", "Perez"), 38, "Cocina Ligera y Cenas", 14));
    chefList.push_back(Chef(Name("Maria", "Lopez"), 45, "Gastronomia Rustica", 20));
    chefList.push_back(Chef(Name("Laura", "Ramirez"), 31, "Ensaladas y Sopas", 9));
    chefList.push_back(Chef(Name("Jose", "Sanchez"), 50, "Reposteria y Platillos Tipicos", 25));
    chefList.push_back(Chef(Name("David", "Torres"), 36, "Cocina Gourmet", 11));
    chefList.push_back(Chef(Name("Elena", "Flores"), 33, "Cocina Casera", 10));
}

wxPanel* RecipeUI::createRecipesPage(wxWindow* parent) {
    wxPanel* panel = new wxPanel(parent, wxID_ANY);
    wxBoxSizer* pageSizer = new wxBoxSizer(wxVERTICAL);

    // Barra superior: Busqueda, Filtro por categoria, Ordenamiento y Disco (en 2 filas para mejor ajuste)
    wxStaticBoxSizer* topBar = new wxStaticBoxSizer(wxVERTICAL, panel, "Busqueda, Filtrado, Ordenamiento y Archivo");

    wxBoxSizer* row1 = new wxBoxSizer(wxHORIZONTAL);
    row1->Add(new wxStaticText(panel, wxID_ANY, "Buscar por:"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 6);
    wxArrayString searchChoices;
    searchChoices.Add("1. Nombre del platillo");
    searchChoices.Add("2. Nombre del autor");
    choiceSearchCriteria = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, searchChoices);
    choiceSearchCriteria->SetSelection(0);
    row1->Add(choiceSearchCriteria, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 6);

    txtSearch = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));
    row1->Add(txtSearch, 1, wxALIGN_CENTER_VERTICAL | wxRIGHT, 6);

    wxButton* btnSearch = new wxButton(panel, wxID_ANY, "2. Buscar Receta");
    row1->Add(btnSearch, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 16);

    row1->Add(new wxStaticText(panel, wxID_ANY, "Filtrar Categoria:"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 6);
    wxArrayString filterCats;
    filterCats.Add("Todas");
    filterCats.Add("Desayuno");
    filterCats.Add("Comida");
    filterCats.Add("Cena");
    filterCats.Add("Navideno");
    choiceFilterCategory = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, filterCats);
    choiceFilterCategory->SetSelection(0);
    row1->Add(choiceFilterCategory, 0, wxALIGN_CENTER_VERTICAL);

    wxBoxSizer* row2 = new wxBoxSizer(wxHORIZONTAL);
    wxButton* btnSortName = new wxButton(panel, wxID_ANY, "6a. Ordenar por Nombre");
    wxButton* btnSortTime = new wxButton(panel, wxID_ANY, "6b. Ordenar por Tiempo");
    wxButton* btnSaveDisk = new wxButton(panel, wxID_ANY, "8. Escribir al Disco");
    wxButton* btnLoadDisk = new wxButton(panel, wxID_ANY, "9. Leer del Disco");

    row2->Add(btnSortName, 1, wxEXPAND | wxRIGHT, 6);
    row2->Add(btnSortTime, 1, wxEXPAND | wxRIGHT, 6);
    row2->Add(btnSaveDisk, 1, wxEXPAND | wxRIGHT, 6);
    row2->Add(btnLoadDisk, 1, wxEXPAND);

    topBar->Add(row1, 0, wxEXPAND | wxALL, 4);
    topBar->Add(row2, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 4);

    pageSizer->Add(topBar, 0, wxEXPAND | wxALL, 6);

    // Zona central dividida: Izquierda (Tabla + Detalle) | Derecha (Formulario de captura/modificacion)
    wxBoxSizer* centerSizer = new wxBoxSizer(wxHORIZONTAL);

    // Columna izquierda: Tabla de recetas y visor completo
    wxBoxSizer* leftCol = new wxBoxSizer(wxVERTICAL);
    recipeTable = new wxListCtrl(panel, wxID_ANY, wxDefaultPosition, wxSize(600, 260),
                                 wxLC_REPORT | wxLC_SINGLE_SEL | wxBORDER_SUNKEN);
    recipeTable->InsertColumn(0, "#", wxLIST_FORMAT_LEFT, 40);
    recipeTable->InsertColumn(1, "Nombre de la Receta", wxLIST_FORMAT_LEFT, 210);
    recipeTable->InsertColumn(2, "Autor (Name)", wxLIST_FORMAT_LEFT, 145);
    recipeTable->InsertColumn(3, "Tiempo (min)", wxLIST_FORMAT_LEFT, 95);
    recipeTable->InsertColumn(4, "Categoria", wxLIST_FORMAT_LEFT, 95);
    recipeTable->InsertColumn(5, "Ingredientes", wxLIST_FORMAT_LEFT, 85);

    leftCol->Add(recipeTable, 1, wxEXPAND | wxBOTTOM, 6);

    wxStaticBoxSizer* detailBox = new wxStaticBoxSizer(
        wxVERTICAL, panel, "7. Detalle Completo de la Receta Seleccionada (Ingredientes y Procedimiento)");
    txtRecipeDetail = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(-1, 210),
                                     wxTE_MULTILINE | wxTE_READONLY);
    wxFont monoFont(10, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    txtRecipeDetail->SetFont(monoFont);
    detailBox->Add(txtRecipeDetail, 1, wxEXPAND | wxALL, 4);
    leftCol->Add(detailBox, 1, wxEXPAND);

    centerSizer->Add(leftCol, 3, wxEXPAND | wxRIGHT, 8);

    // Columna derecha: Formulario de Receta y Botones CRUD
    wxStaticBoxSizer* rightBox = new wxStaticBoxSizer(wxVERTICAL, panel, "Datos de la Receta (Crear / Modificar)");
    wxFlexGridSizer* formGrid = new wxFlexGridSizer(6, 2, 8, 8);
    formGrid->AddGrowableCol(1, 1);

    formGrid->Add(new wxStaticText(panel, wxID_ANY, "Nombre del Platillo:"), 0, wxALIGN_CENTER_VERTICAL);
    txtRecipeName = new wxTextCtrl(panel, wxID_ANY);
    formGrid->Add(txtRecipeName, 1, wxEXPAND);

    formGrid->Add(new wxStaticText(panel, wxID_ANY, "Elegir Chef Autor:"), 0, wxALIGN_CENTER_VERTICAL);
    choiceChefSelector = new wxChoice(panel, wxID_ANY);
    formGrid->Add(choiceChefSelector, 1, wxEXPAND);

    formGrid->Add(new wxStaticText(panel, wxID_ANY, "Nombre Autor:"), 0, wxALIGN_CENTER_VERTICAL);
    txtAuthorFirst = new wxTextCtrl(panel, wxID_ANY);
    formGrid->Add(txtAuthorFirst, 1, wxEXPAND);

    formGrid->Add(new wxStaticText(panel, wxID_ANY, "Apellido Autor:"), 0, wxALIGN_CENTER_VERTICAL);
    txtAuthorLast = new wxTextCtrl(panel, wxID_ANY);
    formGrid->Add(txtAuthorLast, 1, wxEXPAND);

    formGrid->Add(new wxStaticText(panel, wxID_ANY, "Tiempo Prep. (min):"), 0, wxALIGN_CENTER_VERTICAL);
    txtPrepTime = new wxTextCtrl(panel, wxID_ANY, "30");
    formGrid->Add(txtPrepTime, 1, wxEXPAND);

    formGrid->Add(new wxStaticText(panel, wxID_ANY, "Categoria:"), 0, wxALIGN_CENTER_VERTICAL);
    wxArrayString catOptions;
    catOptions.Add("Desayuno");
    catOptions.Add("Comida");
    catOptions.Add("Cena");
    catOptions.Add("Navideno");
    choiceCategory = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, catOptions);
    choiceCategory->SetSelection(1);
    formGrid->Add(choiceCategory, 1, wxEXPAND);

    rightBox->Add(formGrid, 0, wxEXPAND | wxALL, 6);

    rightBox->Add(new wxStaticText(panel, wxID_ANY, "Procedimiento de la Receta:"), 0, wxLEFT | wxTOP, 6);
    txtProcedure = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(-1, 95), wxTE_MULTILINE);
    rightBox->Add(txtProcedure, 1, wxEXPAND | wxALL, 6);

    wxButton* btnIngredients = new wxButton(panel, wxID_ANY, "Administrar Ingredientes de la Receta...");
    rightBox->Add(btnIngredients, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 6);

    // Botones principales CRUD de Recetas
    wxGridSizer* crudGrid = new wxGridSizer(3, 2, 6, 6);
    wxButton* btnAdd = new wxButton(panel, wxID_ANY, "1. Agregar Receta");
    wxButton* btnModify = new wxButton(panel, wxID_ANY, "3. Modificar Receta");
    wxButton* btnDelete = new wxButton(panel, wxID_ANY, "4. Eliminar Receta");
    wxButton* btnDeleteAll = new wxButton(panel, wxID_ANY, "5. Eliminar Todas");
    wxButton* btnClearForm = new wxButton(panel, wxID_ANY, "Limpiar Formulario");
    wxButton* btnExit = new wxButton(panel, wxID_EXIT, "10. Salir");

    crudGrid->Add(btnAdd, 1, wxEXPAND);
    crudGrid->Add(btnModify, 1, wxEXPAND);
    crudGrid->Add(btnDelete, 1, wxEXPAND);
    crudGrid->Add(btnDeleteAll, 1, wxEXPAND);
    crudGrid->Add(btnClearForm, 1, wxEXPAND);
    crudGrid->Add(btnExit, 1, wxEXPAND);

    rightBox->Add(crudGrid, 0, wxEXPAND | wxALL, 6);
    centerSizer->Add(rightBox, 2, wxEXPAND);

    pageSizer->Add(centerSizer, 1, wxEXPAND | wxALL, 6);
    panel->SetSizer(pageSizer);

    // Conectar eventos
    recipeTable->Bind(wxEVT_LIST_ITEM_SELECTED, &RecipeUI::onSelectRecipe, this);
    btnAdd->Bind(wxEVT_BUTTON, &RecipeUI::onAddRecipe, this);
    btnModify->Bind(wxEVT_BUTTON, &RecipeUI::onModifyRecipe, this);
    btnDelete->Bind(wxEVT_BUTTON, &RecipeUI::onDeleteRecipe, this);
    btnDeleteAll->Bind(wxEVT_BUTTON, &RecipeUI::onDeleteAllRecipes, this);
    btnIngredients->Bind(wxEVT_BUTTON, &RecipeUI::onManageIngredients, this);
    btnSearch->Bind(wxEVT_BUTTON, &RecipeUI::onFindRecipe, this);
    choiceFilterCategory->Bind(wxEVT_CHOICE, &RecipeUI::onFilterCategory, this);
    btnSortName->Bind(wxEVT_BUTTON, &RecipeUI::onSortByName, this);
    btnSortTime->Bind(wxEVT_BUTTON, &RecipeUI::onSortByPrepTime, this);
    btnSaveDisk->Bind(wxEVT_BUTTON, &RecipeUI::onWriteToDisk, this);
    btnLoadDisk->Bind(wxEVT_BUTTON, &RecipeUI::onReadFromDisk, this);
    choiceChefSelector->Bind(wxEVT_CHOICE, &RecipeUI::onChefSelectedForRecipe, this);
    btnClearForm->Bind(wxEVT_BUTTON, &RecipeUI::onClearRecipeForm, this);
    btnExit->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) { Close(true); });

    return panel;
}

wxPanel* RecipeUI::createChefsPage(wxWindow* parent) {
    wxPanel* panel = new wxPanel(parent, wxID_ANY);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* lblInfo = new wxStaticText(
        panel, wxID_ANY,
        wxString::FromUTF8("Gestion de Autores / Chefs — Demostracion de Herencia (Chef : public Persona), "
                           "Realizacion (IMostrable), Composicion (Name) y Polimorfismo"));
    wxFont boldFont = lblInfo->GetFont();
    boldFont.SetWeight(wxFONTWEIGHT_BOLD);
    lblInfo->SetFont(boldFont);
    mainSizer->Add(lblInfo, 0, wxALL, 8);

    wxBoxSizer* contentSizer = new wxBoxSizer(wxHORIZONTAL);

    // Tabla de Chefs
    chefTable = new wxListCtrl(panel, wxID_ANY, wxDefaultPosition, wxSize(620, 320),
                               wxLC_REPORT | wxLC_SINGLE_SEL | wxBORDER_SUNKEN);
    chefTable->InsertColumn(0, "#", wxLIST_FORMAT_LEFT, 40);
    chefTable->InsertColumn(1, "Nombre (Name)", wxLIST_FORMAT_LEFT, 150);
    chefTable->InsertColumn(2, "Edad (Persona)", wxLIST_FORMAT_LEFT, 95);
    chefTable->InsertColumn(3, "Especialidad (Chef)", wxLIST_FORMAT_LEFT, 185);
    chefTable->InsertColumn(4, "Experiencia", wxLIST_FORMAT_LEFT, 95);
    chefTable->InsertColumn(5, "Rol Polimorfico", wxLIST_FORMAT_LEFT, 110);

    contentSizer->Add(chefTable, 3, wxEXPAND | wxRIGHT, 8);

    // Formulario de Chef
    wxStaticBoxSizer* formBox = new wxStaticBoxSizer(wxVERTICAL, panel, "Instancia de Clase Chef (Hereda de Persona)");
    wxFlexGridSizer* grid = new wxFlexGridSizer(5, 2, 8, 8);
    grid->AddGrowableCol(1, 1);

    grid->Add(new wxStaticText(panel, wxID_ANY, "Nombre (Name.first):"), 0, wxALIGN_CENTER_VERTICAL);
    txtChefFirst = new wxTextCtrl(panel, wxID_ANY);
    grid->Add(txtChefFirst, 1, wxEXPAND);

    grid->Add(new wxStaticText(panel, wxID_ANY, "Apellido (Name.last):"), 0, wxALIGN_CENTER_VERTICAL);
    txtChefLast = new wxTextCtrl(panel, wxID_ANY);
    grid->Add(txtChefLast, 1, wxEXPAND);

    grid->Add(new wxStaticText(panel, wxID_ANY, "Edad (Persona.edad):"), 0, wxALIGN_CENTER_VERTICAL);
    txtChefAge = new wxTextCtrl(panel, wxID_ANY, "30");
    grid->Add(txtChefAge, 1, wxEXPAND);

    grid->Add(new wxStaticText(panel, wxID_ANY, "Especialidad (Chef):"), 0, wxALIGN_CENTER_VERTICAL);
    txtChefSpecialty = new wxTextCtrl(panel, wxID_ANY, "Cocina Mexicana");
    grid->Add(txtChefSpecialty, 1, wxEXPAND);

    grid->Add(new wxStaticText(panel, wxID_ANY, "Anios Experiencia:"), 0, wxALIGN_CENTER_VERTICAL);
    txtChefExp = new wxTextCtrl(panel, wxID_ANY, "5");
    grid->Add(txtChefExp, 1, wxEXPAND);

    formBox->Add(grid, 0, wxEXPAND | wxALL, 8);

    wxBoxSizer* btnRow = new wxBoxSizer(wxHORIZONTAL);
    wxButton* btnAddChef = new wxButton(panel, wxID_ANY, "Crear Chef");
    wxButton* btnModChef = new wxButton(panel, wxID_ANY, "Modificar Chef");
    wxButton* btnDelChef = new wxButton(panel, wxID_ANY, "Eliminar Chef");
    btnRow->Add(btnAddChef, 1, wxRIGHT, 4);
    btnRow->Add(btnModChef, 1, wxRIGHT, 4);
    btnRow->Add(btnDelChef, 1);
    formBox->Add(btnRow, 0, wxEXPAND | wxALL, 6);

    wxButton* btnPoly = new wxButton(panel, wxID_ANY, "Demostrar Polimorfismo (Persona vs Chef)");
    formBox->Add(btnPoly, 0, wxEXPAND | wxALL, 6);

    contentSizer->Add(formBox, 2, wxEXPAND);
    mainSizer->Add(contentSizer, 1, wxEXPAND | wxALL, 8);

    // Consola de salida polimorfica
    wxStaticBoxSizer* polyBox = new wxStaticBoxSizer(
        wxVERTICAL, panel, "Salida del Metodo Virtual obtenerFicha() / consultarAutorPolimorfico(const Persona&)");
    txtPolymorphismOutput = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(-1, 130),
                                           wxTE_MULTILINE | wxTE_READONLY);
    wxFont monoFont(10, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    txtPolymorphismOutput->SetFont(monoFont);
    polyBox->Add(txtPolymorphismOutput, 1, wxEXPAND | wxALL, 4);
    mainSizer->Add(polyBox, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 8);

    panel->SetSizer(mainSizer);

    // Eventos de Chefs
    chefTable->Bind(wxEVT_LIST_ITEM_SELECTED, &RecipeUI::onSelectChef, this);
    btnAddChef->Bind(wxEVT_BUTTON, &RecipeUI::onAddChef, this);
    btnModChef->Bind(wxEVT_BUTTON, &RecipeUI::onModifyChef, this);
    btnDelChef->Bind(wxEVT_BUTTON, &RecipeUI::onDeleteChef, this);
    btnPoly->Bind(wxEVT_BUTTON, &RecipeUI::onDemonstratePolymorphism, this);

    return panel;
}

void RecipeUI::refreshRecipeTable(const std::string& filterCategory) {
    recipeTable->DeleteAllItems();
    displayedIndices.clear();

    long row = 0;
    for (size_t i = 0; i < this->recipeListRef.size(); i++) {
        const Recipe& rec = this->recipeListRef[i];
        if (filterCategory != "Todas" && !filterCategory.empty() && rec.getCategory() != filterCategory) {
            continue;
        }

        displayedIndices.push_back(static_cast<int>(i));
        long idx = recipeTable->InsertItem(row, to_string(i));
        recipeTable->SetItem(idx, 1, wxString::FromUTF8(rec.getName()));
        recipeTable->SetItem(idx, 2, wxString::FromUTF8(rec.getAuthorName().toString()));
        recipeTable->SetItem(idx, 3, to_string(rec.getPrepTime()) + " min");
        recipeTable->SetItem(idx, 4, wxString::FromUTF8(rec.getCategory()));
        recipeTable->SetItem(idx, 5, to_string(rec.getIngredientList().size()));
        row++;
    }
    recipeTable->Refresh();
    recipeTable->Update();

    SetStatusText(wxString::FromUTF8("Total de recetas en el vector: " + to_string(this->recipeListRef.size()) +
                                     " | Mostradas: " + to_string(displayedIndices.size())));
}

void RecipeUI::refreshChefTable() {
    chefTable->DeleteAllItems();
    stringstream polySS;
    polySS << "=== LISTADO POLIMORFICO DE INSTANCIAS (consultarAutorPolimorfico) ===\n";

    for (size_t i = 0; i < chefList.size(); i++) {
        const Chef& c = chefList[i];
        long idx = chefTable->InsertItem(i, to_string(i));
        chefTable->SetItem(idx, 1, wxString::FromUTF8(c.getNombre().toString()));
        chefTable->SetItem(idx, 2, to_string(c.getEdad()));
        chefTable->SetItem(idx, 3, wxString::FromUTF8(c.getEspecialidad()));
        chefTable->SetItem(idx, 4, to_string(c.getAniosExperiencia()) + " anios");
        chefTable->SetItem(idx, 5, wxString::FromUTF8(c.obtenerRol()));

        polySS << "[" << i << "] " << consultarAutorPolimorfico(c) << "\n";
    }
    chefTable->Refresh();
    chefTable->Update();
    txtPolymorphismOutput->SetValue(wxString::FromUTF8(polySS.str()));
}

void RecipeUI::updateChefChoiceSelector() {
    choiceChefSelector->Clear();
    choiceChefSelector->Append("-- Escribir autor manualmente --");
    for (size_t i = 0; i < chefList.size(); i++) {
        choiceChefSelector->Append(wxString::FromUTF8(
            chefList[i].getNombre().toString() + " (" + chefList[i].getEspecialidad() + ")"));
    }
    choiceChefSelector->SetSelection(0);
}

void RecipeUI::showRecipeDetails(int realIndex) {
    if (realIndex < 0 || realIndex >= static_cast<int>(this->recipeListRef.size())) {
        txtRecipeDetail->Clear();
        return;
    }

    const Recipe& rec = this->recipeListRef[realIndex];
    stringstream ss;
    ss << "================================================================================\n";
    ss << " RECETA: " << rec.getName() << "\n";
    ss << " AUTOR : " << rec.getAuthorName().toString()
       << "   |   TIEMPO: " << rec.getPrepTime() << " minutos"
       << "   |   CATEGORIA: " << rec.getCategory() << "\n";
    ss << "================================================================================\n\n";
    ss << " | " << left << setw(wIngredientName) << "INGREDIENTE"
       << " | " << left << setw(wQuantity) << "CANTIDAD"
       << " | " << left << setw(wUnit) << "UNIDAD" << " |\n";
    ss << " ------------------------------------------------------------------------------\n";

    if (rec.getIngredientList().empty()) {
        ss << "   (Sin ingredientes registrados)\n";
    } else {
        for (size_t i = 0; i < rec.getIngredientList().size(); i++) {
            ss << rec.getIngredientList()[i].toString();
        }
    }

    ss << "\nPROCEDIMIENTO:\n" << rec.getProcedure() << "\n";
    txtRecipeDetail->SetValue(wxString::FromUTF8(ss.str()));
}

void RecipeUI::onSelectRecipe(wxListEvent& event) {
    long tableRow = event.GetIndex();
    if (tableRow < 0 || tableRow >= static_cast<long>(displayedIndices.size())) {
        return;
    }

    selectedRecipePos = displayedIndices[tableRow];
    const Recipe& rec = this->recipeListRef[selectedRecipePos];

    // Llenar el formulario con los datos de la receta seleccionada
    txtRecipeName->SetValue(wxString::FromUTF8(rec.getName()));
    txtAuthorFirst->SetValue(wxString::FromUTF8(rec.getAuthorName().getFirst()));
    txtAuthorLast->SetValue(wxString::FromUTF8(rec.getAuthorName().getLast()));
    txtPrepTime->SetValue(to_string(rec.getPrepTime()));
    txtProcedure->SetValue(wxString::FromUTF8(rec.getProcedure()));

    int catIdx = choiceCategory->FindString(wxString::FromUTF8(rec.getCategory()));
    if (catIdx != wxNOT_FOUND) {
        choiceCategory->SetSelection(catIdx);
    }

    tempIngredients = rec.getIngredientList();
    showRecipeDetails(selectedRecipePos);
}

void RecipeUI::onChefSelectedForRecipe(wxCommandEvent&) {
    int sel = choiceChefSelector->GetSelection();
    if (sel > 0 && (sel - 1) < static_cast<int>(chefList.size())) {
        const Chef& chosenChef = chefList[sel - 1];
        txtAuthorFirst->SetValue(wxString::FromUTF8(chosenChef.getNombre().getFirst()));
        txtAuthorLast->SetValue(wxString::FromUTF8(chosenChef.getNombre().getLast()));
    }
}

void RecipeUI::onClearRecipeForm(wxCommandEvent&) {
    selectedRecipePos = -1;
    txtRecipeName->Clear();
    txtAuthorFirst->Clear();
    txtAuthorLast->Clear();
    choiceChefSelector->SetSelection(0);
    txtPrepTime->SetValue("30");
    choiceCategory->SetSelection(1);
    txtProcedure->Clear();
    tempIngredients.clear();
    txtRecipeDetail->Clear();
}

void RecipeUI::onAddRecipe(wxCommandEvent&) {
    string rName = txtRecipeName->GetValue().ToUTF8().data();
    string aFirst = txtAuthorFirst->GetValue().ToUTF8().data();
    string aLast = txtAuthorLast->GetValue().ToUTF8().data();
    string timeStr = txtPrepTime->GetValue().ToUTF8().data();
    string proc = txtProcedure->GetValue().ToUTF8().data();
    string cat = choiceCategory->GetStringSelection().ToUTF8().data();

    if (rName.empty() || aFirst.empty() || aLast.empty() || proc.empty()) {
        wxMessageBox("Por favor completa el nombre de la receta, autor y procedimiento.",
                     "Datos incompletos", wxOK | wxICON_WARNING, this);
        return;
    }

    int prepMinutes = 0;
    try {
        prepMinutes = stoi(timeStr);
    } catch (...) {
        wxMessageBox("El tiempo de preparacion debe ser un numero en minutos.",
                     "Error en tiempo", wxOK | wxICON_ERROR, this);
        return;
    }

    Recipe myRecipe;
    myRecipe.setName(rName);

    int chefSel = choiceChefSelector->GetSelection();
    if (chefSel > 0 && (chefSel - 1) < static_cast<int>(chefList.size())) {
        // Relacion de colaboracion entre Recipe y Chef
        myRecipe.asignarChefAutor(chefList[chefSel - 1]);
    } else {
        Name tempName(aFirst, aLast);
        myRecipe.setAuthor(tempName);
    }

    myRecipe.setPrepTime(prepMinutes);
    myRecipe.setProcedure(proc);
    myRecipe.setCategory(cat);
    myRecipe.getIngredientList() = tempIngredients;

    int askIng = wxMessageBox("¿Deseas abrir el administrador de ingredientes antes de guardar la receta?",
                              "Ingredientes de la receta", wxYES_NO | wxICON_QUESTION, this);
    if (askIng == wxYES) {
        IngredientUI ingDialog(this, myRecipe.getIngredientList(), myRecipe.getName());
        ingDialog.manageIngredient();
    }

    this->recipeListRef.push_back(myRecipe);
    selectedRecipePos = static_cast<int>(this->recipeListRef.size()) - 1;
    tempIngredients = myRecipe.getIngredientList();

    refreshRecipeTable(choiceFilterCategory->GetStringSelection().ToUTF8().data());
    showRecipeDetails(selectedRecipePos);
    wxMessageBox("Receta agregada con exito al vector!", "Receta Agregada", wxOK | wxICON_INFORMATION, this);
}

void RecipeUI::onModifyRecipe(wxCommandEvent&) {
    if (selectedRecipePos < 0 || selectedRecipePos >= static_cast<int>(this->recipeListRef.size())) {
        // Intentar buscar por el nombre escrito en el formulario
        string targetName = txtRecipeName->GetValue().ToUTF8().data();
        for (size_t i = 0; i < this->recipeListRef.size(); i++) {
            if (this->recipeListRef[i].getName() == targetName) {
                selectedRecipePos = static_cast<int>(i);
                break;
            }
        }
    }

    if (selectedRecipePos < 0 || selectedRecipePos >= static_cast<int>(this->recipeListRef.size())) {
        wxMessageBox("Selecciona primero una receta de la tabla para modificarla.",
                     "Receta no seleccionada", wxOK | wxICON_WARNING, this);
        return;
    }

    string rName = txtRecipeName->GetValue().ToUTF8().data();
    string aFirst = txtAuthorFirst->GetValue().ToUTF8().data();
    string aLast = txtAuthorLast->GetValue().ToUTF8().data();
    string timeStr = txtPrepTime->GetValue().ToUTF8().data();
    string proc = txtProcedure->GetValue().ToUTF8().data();
    string cat = choiceCategory->GetStringSelection().ToUTF8().data();

    int prepMinutes = this->recipeListRef[selectedRecipePos].getPrepTime();
    try {
        prepMinutes = stoi(timeStr);
    } catch (...) { }

    Recipe& target = this->recipeListRef[selectedRecipePos];
    if (!rName.empty()) target.setName(rName);
    if (!aFirst.empty() || !aLast.empty()) target.setAuthor(Name(aFirst, aLast));
    target.setPrepTime(prepMinutes);
    if (!proc.empty()) target.setProcedure(proc);
    if (!cat.empty()) target.setCategory(cat);

    refreshRecipeTable(choiceFilterCategory->GetStringSelection().ToUTF8().data());
    showRecipeDetails(selectedRecipePos);
    wxMessageBox("Receta modificada correctamente!", "Receta Actualizada", wxOK | wxICON_INFORMATION, this);
}

void RecipeUI::onManageIngredients(wxCommandEvent&) {
    if (selectedRecipePos >= 0 && selectedRecipePos < static_cast<int>(this->recipeListRef.size())) {
        Recipe& rec = this->recipeListRef[selectedRecipePos];
        IngredientUI ingDialog(this, rec.getIngredientList(), rec.getName());
        ingDialog.manageIngredient();
        tempIngredients = rec.getIngredientList();
        refreshRecipeTable(choiceFilterCategory->GetStringSelection().ToUTF8().data());
        showRecipeDetails(selectedRecipePos);
    } else {
        IngredientUI ingDialog(this, tempIngredients, "Nueva Receta");
        ingDialog.manageIngredient();
    }
}

void RecipeUI::onDeleteRecipe(wxCommandEvent&) {
    if (selectedRecipePos < 0 || selectedRecipePos >= static_cast<int>(this->recipeListRef.size())) {
        string targetName = txtRecipeName->GetValue().ToUTF8().data();
        for (size_t i = 0; i < this->recipeListRef.size(); i++) {
            if (this->recipeListRef[i].getName() == targetName) {
                selectedRecipePos = static_cast<int>(i);
                break;
            }
        }
    }

    if (selectedRecipePos < 0 || selectedRecipePos >= static_cast<int>(this->recipeListRef.size())) {
        wxMessageBox("Selecciona una receta de la tabla o escribe su nombre para eliminarla.",
                     "Receta no encontrada", wxOK | wxICON_WARNING, this);
        return;
    }

    string nameToDelete = this->recipeListRef[selectedRecipePos].getName();
    int resp = wxMessageBox(
        wxString::FromUTF8("¿Estas seguro de que deseas eliminar la receta '" + nameToDelete + "'?"),
        "Confirmar eliminacion", wxYES_NO | wxICON_QUESTION, this);

    if (resp == wxYES) {
        this->recipeListRef.erase(this->recipeListRef.begin() + selectedRecipePos);
        selectedRecipePos = -1;
        txtRecipeDetail->Clear();
        refreshRecipeTable(choiceFilterCategory->GetStringSelection().ToUTF8().data());
        wxMessageBox("Receta eliminada correctamente.", "Eliminada", wxOK | wxICON_INFORMATION, this);
    }
}

void RecipeUI::onDeleteAllRecipes(wxCommandEvent&) {
    if (this->recipeListRef.empty()) {
        wxMessageBox("El recetario ya se encuentra vacio.", "Aviso", wxOK | wxICON_INFORMATION, this);
        return;
    }

    int resp = wxMessageBox("¿Estas seguro de eliminar TODAS LAS RECETAS del vector?",
                            "Eliminar todas las recetas", wxYES_NO | wxICON_WARNING, this);
    if (resp == wxYES) {
        this->recipeListRef.clear();
        selectedRecipePos = -1;
        txtRecipeDetail->Clear();
        refreshRecipeTable();
        wxMessageBox("TODAS LAS RECETAS FUERON ELIMINADAS.", "Recetario Vacio", wxOK | wxICON_INFORMATION, this);
    }
}

void RecipeUI::onFindRecipe(wxCommandEvent&) {
    string query = txtSearch->GetValue().ToUTF8().data();
    if (query.empty()) {
        wxMessageBox("Escribe el nombre del platillo o del autor a buscar.",
                     "Busqueda vacia", wxOK | wxICON_WARNING, this);
        return;
    }

    int criteria = choiceSearchCriteria->GetSelection(); // 0 = Nombre platillo, 1 = Autor
    int foundPos = -1;

    for (size_t i = 0; i < this->recipeListRef.size(); i++) {
        if (criteria == 0) {
            if (this->recipeListRef[i].getName().find(query) != string::npos) {
                foundPos = static_cast<int>(i);
                break;
            }
        } else {
            if (this->recipeListRef[i].getAuthorName().toString().find(query) != string::npos) {
                foundPos = static_cast<int>(i);
                break;
            }
        }
    }

    if (foundPos == -1) {
        wxMessageBox("La receta no fue encontrada...", "Sin resultados", wxOK | wxICON_INFORMATION, this);
    } else {
        selectedRecipePos = foundPos;
        choiceFilterCategory->SetSelection(0);
        refreshRecipeTable("Todas");

        recipeTable->SetItemState(foundPos, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED,
                                  wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED);
        recipeTable->EnsureVisible(foundPos);
        showRecipeDetails(foundPos);
    }
}

void RecipeUI::onFilterCategory(wxCommandEvent&) {
    string cat = choiceFilterCategory->GetStringSelection().ToUTF8().data();
    refreshRecipeTable(cat);
}

void RecipeUI::onSortByName(wxCommandEvent&) {
    std::sort(this->recipeListRef.begin(), this->recipeListRef.end(),
              [](const Recipe& a, const Recipe& b) {
                  return Recipe::compareByName(a, b) < 0;
              });
    refreshRecipeTable(choiceFilterCategory->GetStringSelection().ToUTF8().data());
    SetStatusText("La lista fue ordenada por nombre de la receta!");
}

void RecipeUI::onSortByPrepTime(wxCommandEvent&) {
    std::sort(this->recipeListRef.begin(), this->recipeListRef.end(),
              [](const Recipe& a, const Recipe& b) {
                  return Recipe::compareByPrepTime(a, b) < 0;
              });
    refreshRecipeTable(choiceFilterCategory->GetStringSelection().ToUTF8().data());
    SetStatusText("La lista fue ordenada por tiempo de preparacion!");
}

void RecipeUI::onWriteToDisk(wxCommandEvent&) {
    wxFileDialog saveFileDialog(this, "Guardar recetario en disco", "", "recetas.txt",
                                "Archivos de texto (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    string path = saveFileDialog.GetPath().ToUTF8().data();
    if (saveToFile(path)) {
        wxMessageBox("El recetario se guardo correctamente en:\n" + path,
                     "Guardado exitoso", wxOK | wxICON_INFORMATION, this);
    } else {
        wxMessageBox("Fue imposible abrir el archivo para escritura.",
                     "Error", wxOK | wxICON_ERROR, this);
    }
}

void RecipeUI::onReadFromDisk(wxCommandEvent&) {
    wxFileDialog openFileDialog(this, "Leer recetario del disco", "", "recetas.txt",
                                "Archivos de texto (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    string path = openFileDialog.GetPath().ToUTF8().data();
    loadFromFile(path);
    wxMessageBox("Recetario recuperado! Total de recetas: " + to_string(this->recipeListRef.size()),
                 "Lectura exitosa", wxOK | wxICON_INFORMATION, this);
}

void RecipeUI::loadFromFile(const std::string& filename) {
    ifstream myFile(filename);
    if (!myFile.is_open()) {
        return;
    }

    string content;
    getline(myFile, content);
    myFile.close();

    this->recipeListRef.clear();
    stringstream ss(content);
    string token;
    while (getline(ss, token, '|')) {
        if (token.empty()) {
            continue;
        }
        Recipe myRecipe;
        myRecipe.deserialize(token, '*');
        this->recipeListRef.push_back(myRecipe);
    }

    refreshRecipeTable(choiceFilterCategory->GetStringSelection().ToUTF8().data());
    if (!this->recipeListRef.empty()) {
        selectedRecipePos = 0;
        const Recipe& rec = this->recipeListRef[0];
        txtRecipeName->SetValue(wxString::FromUTF8(rec.getName()));
        txtAuthorFirst->SetValue(wxString::FromUTF8(rec.getAuthorName().getFirst()));
        txtAuthorLast->SetValue(wxString::FromUTF8(rec.getAuthorName().getLast()));
        txtPrepTime->SetValue(to_string(rec.getPrepTime()));
        txtProcedure->SetValue(wxString::FromUTF8(rec.getProcedure()));
        int catIdx = choiceCategory->FindString(wxString::FromUTF8(rec.getCategory()));
        if (catIdx != wxNOT_FOUND) choiceCategory->SetSelection(catIdx);
        tempIngredients = rec.getIngredientList();
        recipeTable->SetItemState(0, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED,
                                  wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED);
        showRecipeDetails(0);
    }
}

bool RecipeUI::saveToFile(const std::string& filename) {
    ofstream myFile(filename, ios_base::trunc);
    if (!myFile.is_open()) {
        return false;
    }

    string serialized;
    for (size_t i = 0; i < this->recipeListRef.size(); i++) {
        serialized += this->recipeListRef[i].serialize('*') + '|';
    }
    myFile << serialized;
    myFile.close();
    return true;
}

// ==================== Eventos de la Pestaña de Chefs ====================

void RecipeUI::onSelectChef(wxListEvent& event) {
    selectedChefPos = event.GetIndex();
    if (selectedChefPos >= 0 && selectedChefPos < static_cast<int>(chefList.size())) {
        const Chef& c = chefList[selectedChefPos];
        txtChefFirst->SetValue(wxString::FromUTF8(c.getNombre().getFirst()));
        txtChefLast->SetValue(wxString::FromUTF8(c.getNombre().getLast()));
        txtChefAge->SetValue(to_string(c.getEdad()));
        txtChefSpecialty->SetValue(wxString::FromUTF8(c.getEspecialidad()));
        txtChefExp->SetValue(to_string(c.getAniosExperiencia()));
    }
}

void RecipeUI::onAddChef(wxCommandEvent&) {
    string first = txtChefFirst->GetValue().ToUTF8().data();
    string last = txtChefLast->GetValue().ToUTF8().data();
    string ageStr = txtChefAge->GetValue().ToUTF8().data();
    string spec = txtChefSpecialty->GetValue().ToUTF8().data();
    string expStr = txtChefExp->GetValue().ToUTF8().data();

    if (first.empty() || last.empty() || spec.empty()) {
        wxMessageBox("Completa nombre, apellido y especialidad del Chef.",
                     "Campos requeridos", wxOK | wxICON_WARNING, this);
        return;
    }

    int age = 25, exp = 1;
    try { age = stoi(ageStr); } catch (...) { }
    try { exp = stoi(expStr); } catch (...) { }

    Chef newChef(Name(first, last), age, spec, exp);
    chefList.push_back(newChef);

    refreshChefTable();
    updateChefChoiceSelector();
    wxMessageBox("Instancia de Chef creada y agregada al vector!", "Chef Creado", wxOK | wxICON_INFORMATION, this);
}

void RecipeUI::onModifyChef(wxCommandEvent&) {
    if (selectedChefPos < 0 || selectedChefPos >= static_cast<int>(chefList.size())) {
        wxMessageBox("Selecciona un Chef de la tabla para modificarlo.",
                     "Sin seleccion", wxOK | wxICON_WARNING, this);
        return;
    }

    string first = txtChefFirst->GetValue().ToUTF8().data();
    string last = txtChefLast->GetValue().ToUTF8().data();
    string ageStr = txtChefAge->GetValue().ToUTF8().data();
    string spec = txtChefSpecialty->GetValue().ToUTF8().data();
    string expStr = txtChefExp->GetValue().ToUTF8().data();

    int age = chefList[selectedChefPos].getEdad();
    int exp = chefList[selectedChefPos].getAniosExperiencia();
    try { age = stoi(ageStr); } catch (...) { }
    try { exp = stoi(expStr); } catch (...) { }

    chefList[selectedChefPos].setNombre(Name(first, last));
    chefList[selectedChefPos].setEdad(age);
    chefList[selectedChefPos].setEspecialidad(spec);
    chefList[selectedChefPos].setAniosExperiencia(exp);

    refreshChefTable();
    updateChefChoiceSelector();
    wxMessageBox("Datos del Chef modificados con exito!", "Chef Modificado", wxOK | wxICON_INFORMATION, this);
}

void RecipeUI::onDeleteChef(wxCommandEvent&) {
    if (selectedChefPos < 0 || selectedChefPos >= static_cast<int>(chefList.size())) {
        wxMessageBox("Selecciona un Chef de la tabla para eliminarlo.",
                     "Sin seleccion", wxOK | wxICON_WARNING, this);
        return;
    }

    string fullName = chefList[selectedChefPos].getNombre().toString();
    int resp = wxMessageBox(
        wxString::FromUTF8("¿Deseas eliminar al Chef '" + fullName + "'?"),
        "Confirmar eliminacion", wxYES_NO | wxICON_QUESTION, this);

    if (resp == wxYES) {
        chefList.erase(chefList.begin() + selectedChefPos);
        selectedChefPos = -1;
        refreshChefTable();
        updateChefChoiceSelector();
    }
}

void RecipeUI::onDemonstratePolymorphism(wxCommandEvent&) {
    Persona personaGenerica(Name("Diego", "Ruelas"), 20);
    Chef chefEspecializado(Name("Ana", "Garcia"), 34, "Cocina Navidena", 12);

    // Arreglo de punteros a la clase base Persona para demostrar polimorfismo en tiempo de ejecucion
    vector<const Persona*> listaPolimorfica;
    listaPolimorfica.push_back(&personaGenerica);
    listaPolimorfica.push_back(&chefEspecializado);

    stringstream ss;
    ss << "=== DEMOSTRACION DE LOS 4 PILARES DE LA POO (POLIMORFISMO Y HERENCIA) ===\n\n";
    ss << "Invocando consultarAutorPolimorfico(const Persona&) con enlace dinamico (virtual / override):\n\n";
    for (size_t i = 0; i < listaPolimorfica.size(); i++) {
        ss << "  Objeto " << i + 1 << " -> " << consultarAutorPolimorfico(*listaPolimorfica[i]) << "\n";
    }

    txtPolymorphismOutput->SetValue(wxString::FromUTF8(ss.str()));
    wxMessageBox(wxString::FromUTF8(ss.str()), "Demostracion de Polimorfismo", wxOK | wxICON_INFORMATION, this);
}

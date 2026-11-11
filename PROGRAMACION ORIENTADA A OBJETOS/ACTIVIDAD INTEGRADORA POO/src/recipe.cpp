#include "recipe.hpp"
#include <algorithm>
using namespace std;

Recipe::Recipe() : name(""), authorName(), prepTime(0), procedure(""), category("Comida") { }

Recipe::Recipe(const Recipe& other)
    : name(other.name),
      authorName(other.authorName),
      prepTime(other.prepTime),
      procedure(other.procedure),
      category(other.category),
      ingredientList(other.ingredientList) { }

Recipe::~Recipe() { }

std::string Recipe::getName() const {
    return this->name;
}

Name Recipe::getAuthorName() const {
    return this->authorName;
}

int Recipe::getPrepTime() const {
    return this->prepTime;
}

std::string Recipe::getProcedure() const {
    return this->procedure;
}

std::string Recipe::getCategory() const {
    return this->category;
}

std::vector<Ingredient>& Recipe::getIngredientList() {
    return this->ingredientList;
}

const std::vector<Ingredient>& Recipe::getIngredientList() const {
    return this->ingredientList;
}

void Recipe::setName(const std::string& n) {
    this->name = n;
}

void Recipe::setAuthor(const Name& a) {
    this->authorName = a;
}

void Recipe::setPrepTime(const int& p) {
    this->prepTime = p;
}

void Recipe::setProcedure(const std::string& pro) {
    this->procedure = pro;
}

void Recipe::setCategory(const std::string& c) {
    this->category = c;
}

void Recipe::asignarChefAutor(const Chef& chef) {
    this->authorName = chef.getNombre();
}

void Recipe::addIngredient(const Ingredient& ing) {
    this->ingredientList.push_back(ing);
    // Mantiene los ingredientes ordenados por nombre como en el proyecto original
    std::sort(this->ingredientList.begin(), this->ingredientList.end());
}

bool Recipe::removeIngredientByIndex(int index) {
    if (index < 0 || index >= static_cast<int>(this->ingredientList.size())) {
        return false;
    }
    this->ingredientList.erase(this->ingredientList.begin() + index);
    return true;
}

std::string Recipe::toString(const bool s) const {
    stringstream ss;

    ss << " | " << left << setw(wRecipeName) << this->name << " | "
       << left << setw(wAuthorName) << this->authorName.toString() << " | "
       << left << setw(wPrepTime) << to_string(this->prepTime) << " | "
       << left << setw(wCategory) << this->category << " | "
       << endl;

    if (s) {
        ss << endl;
        ss << " | " << left << setw(wIngredientName) << "INGREDIENTE";
        ss << " | " << left << setw(wQuantity) << "CANTIDAD";
        ss << " | " << left << setw(wUnit) << "UNIDAD";
        ss << " | " << endl << "\n";

        for (size_t i = 0; i < this->ingredientList.size(); i++) {
            ss << this->ingredientList[i].toString();
        }
        ss << "\n";
    }
    ss << "Procedimiento: " << this->procedure << endl;
    return ss.str();
}

Recipe& Recipe::operator=(const Recipe& other) {
    this->name = other.name;
    this->authorName = other.authorName;
    this->prepTime = other.prepTime;
    this->procedure = other.procedure;
    this->category = other.category;
    this->ingredientList = other.ingredientList;

    return *this;
}

bool Recipe::operator==(const Recipe& other) const {
    return this->name == other.name;
}

bool Recipe::operator!=(const Recipe& other) const {
    return this->name != other.name;
}

bool Recipe::operator<(const Recipe& other) const {
    return this->name < other.name;
}

bool Recipe::operator<=(const Recipe& other) const {
    return this->name <= other.name;
}

bool Recipe::operator>(const Recipe& other) const {
    return this->name > other.name;
}

bool Recipe::operator>=(const Recipe& other) const {
    return this->name >= other.name;
}

int Recipe::compare(const Recipe& other) const {
    return this->name.compare(other.name);
}

int Recipe::compare(const Recipe& a, const Recipe& b) {
    return a.compare(b);
}

int Recipe::compareByName(const Recipe& a, const Recipe& b) {
    return a.compare(b);
}

int Recipe::compareByPrepTime(const Recipe& a, const Recipe& b) {
    if (a.prepTime > b.prepTime) return 1;
    else if (a.prepTime == b.prepTime) return 0;
    else return -1;
}

int Recipe::compareByCategory(const Recipe& a, const Recipe& b) {
    return a.category.compare(b.category);
}

int Recipe::compareByAuthor(const Recipe& a, const Recipe& b) {
    return a.authorName.compare(b.authorName);
}

std::string Recipe::serialize(const char& delim) const {
    string result;

    result += this->name + delim;
    result += this->authorName.serialize(',') + delim;
    result += to_string(this->prepTime) + delim;
    result += this->procedure + delim;
    result += this->category + delim;

    for (size_t i = 0; i < this->ingredientList.size(); i++) {
        result += this->ingredientList[i].serialize('*') + '#';
    }

    return result;
}

void Recipe::deserialize(const string& str, const char& delim) {
    stringstream mySStream(str);
    string myStr;

    getline(mySStream, this->name, delim);
    getline(mySStream, myStr, delim);
    this->authorName.deserialize(myStr, ',');
    getline(mySStream, myStr, delim);
    try {
        this->prepTime = myStr.empty() ? 0 : static_cast<int>(stof(myStr));
    } catch (...) {
        this->prepTime = 0;
    }
    getline(mySStream, this->procedure, delim);
    getline(mySStream, this->category, delim);
    getline(mySStream, myStr);

    this->ingredientList.clear();
    stringstream ingStream(myStr);
    string ingToken;
    while (getline(ingStream, ingToken, '#')) {
        if (ingToken.empty()) {
            continue;
        }
        Ingredient myIng;
        myIng.deserialize(ingToken, '*');
        this->ingredientList.push_back(myIng);
    }
}

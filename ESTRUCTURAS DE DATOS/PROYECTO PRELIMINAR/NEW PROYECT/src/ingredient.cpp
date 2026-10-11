#include "ingredient.hpp"
using namespace std;


//Constructores
Ingredient::Ingredient(){ }

Ingredient::Ingredient(const Ingredient&){ }

//Getters
string Ingredient::getName() const{ 
    return this->name;
}

float Ingredient::getQuantity() const{
    return this->quantity;
}

string Ingredient::getUnit() const{
    return this->unit;
}

void Ingredient::setName(const string& n){
    this->name = n;
}

void Ingredient::setQuantity(const float& q){
    this->quantity = q;
}

void Ingredient::setUnit(const string& u){
    this->unit = u;
}

string Ingredient::toString() const{
    stringstream ss;

    ss << " | " << left << setw(wIngredientName) << this->name << " | " << 
    left << setw(wQuantity) << to_string(this->quantity) << " | "
    << left << setw(wUnit) << this->unit << " | " 
    << endl; 

    return ss.str();
}


//Sobrecarga de operador de asignacion

Ingredient& Ingredient::operator=(const Ingredient& other){
    this->name = other.name;
    this->quantity = other.quantity;
    this->unit = other.unit;

    return *this;
}

//Operadores

bool Ingredient::operator==(const Ingredient& other) const{
    return this->name == other.name;
}

bool Ingredient::operator!=(const Ingredient& other) const{
    return this->name != other.name;
}

bool Ingredient::operator<=(const Ingredient& other) const{
    return this->name <= other.name;
}

bool Ingredient::operator<(const Ingredient& other) const{
    return this->name < other.name;
}

bool Ingredient::operator>(const Ingredient& other) const{
    return this->name > other.name;
}

bool Ingredient::operator>=(const Ingredient& other) const{
    return this->name >= other.name;
}

//Comparaciones

int Ingredient::compare(const Ingredient& other) const{
    return this->name.compare(other.name);
}

int Ingredient::compare(const Ingredient& a, const Ingredient& b){
    return a.compare(b);
}

int Ingredient::compareByName(const Ingredient& a, const Ingredient& b){
    return a.compare(b);
}

int Ingredient::compareByQuantity(const Ingredient& a, const Ingredient& b){
    if(a.quantity < b.quantity){
        return -1;
    } else if(a.quantity > b.quantity) {
        return 1;
    } else {
        return 0;
    }
}

int Ingredient::compareByUnit(const Ingredient& a, const Ingredient& b){
    return a.unit.compare(b.unit);
}

std::string Ingredient::serialize(const char& delim) const{
    string result;
    char myQuantity[20];
    sprintf(myQuantity, "%.3f", this->quantity);

    result += this->name + delim;
    result += myQuantity;
    result += delim;
    result += this->unit;

    return result;
}

void Ingredient::deserialize(const std::string& str, const char& delim){
    stringstream mySStream(str);
    string myStr;
  
    getline(mySStream,this->name,delim);
    getline(mySStream,myStr,delim);
    this->quantity = stof(myStr);
    getline(mySStream,this->unit,delim);
}


//Sobrecarga de operadores de flujo

istream& operator>>(istream& is, Ingredient& i){
    string myStr;

    if (!getline(is, i.name)) return is;

    getline (is, myStr);
    i.quantity = stof(myStr);

    getline(is, i.unit);

    return is;
}

ostream& operator<<(ostream& os, const Ingredient& i){
    os << i.name << endl;
    os << i.quantity << endl;
    os << i.unit << endl;
    return os;
}

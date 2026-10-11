#include "product.hpp"
using namespace std;

bool Product::isBarcodeValid(const string& s) const{
    if (s.length() != 13) {
        return false;
    }
    return std::all_of(s.begin(), s.end(), [](unsigned char c) {
        return std::isdigit(c);
    });


}

Product::Product(){ }

Product::Product(const Product& p) : barcode(p.barcode), name(p.name), weight(p.weight), wholePrice(p.wholePrice), retailPrice(p.retailPrice), stock(p.stock){ }

string Product::getBarcode() const{
    return this->barcode;
}

string Product::getName() const{
    return this->name;
}

float Product::getWeight() const{
    return this->weight;
}

Date Product::getIncomeDate() const{
    return this->incomeDate;
}

float Product::getWholePrice() const{
    return this->wholePrice;
}

float Product::getRetailPrice() const{
    return this->retailPrice;
}

int Product::getStock() const{
    return this->stock;
}

string Product::toString() const{
    string result;

    result+= this-> barcode;
    result+= " | ";
    result+= this-> name;
    result+=  " | ";
    result+= to_string(weight);
    result+=  " | ";
    result+= this-> incomeDate.toString();
    result+=  " | ";
    result+= to_string(wholePrice);
    result+=  " | ";
    result+= to_string(retailPrice);
    result+=  " | ";
    result+= to_string(stock);
    result+=  " | ";

    return result;
}

void Product::setBarcode(const string& b){
    if(isBarcodeValid(b) == true) {
        this-> barcode = b;
    }
    else {
        this->barcode = "notValid";
    }
}

void Product::setName(const string& n){
    this-> name=n;
}

void Product::setWeight(const float& w){
    this-> weight=w;
}

void Product::setIncomeDate(const Date& d){
    this-> incomeDate=d;
}

void Product::setWholePrice(const float& w){
    this-> wholePrice=w;
}

void Product::setRetailPrice(const float& r){
    this-> retailPrice=r;
}

void Product::setStock(const int& s){
    this-> stock=s;
}

Product& Product::operator = (const Product& p){
    this -> barcode = p.barcode;
    this -> name = p.name;
    this -> weight = p.weight;
    this -> incomeDate = p.incomeDate;
    this -> wholePrice = p.wholePrice;
    this -> retailPrice = p.retailPrice;
    this -> stock = p.stock;

    return *this;
}

bool Product::operator == (const Product& p) const{
    return this -> barcode == p.barcode;
}

bool Product::operator != (const Product& p) const{
    return !(*this == p);
}

bool Product::operator < (const Product& p) const{
    return this -> stock < p.stock;
}

bool Product::operator <= (const Product& p) const{
    return this -> stock <= p.stock;
}

bool Product::operator > (const Product& p) const{
    return this -> stock > p.stock;
}

bool Product::operator >= (const Product& p) const{
    return this -> stock >= p.stock;
}



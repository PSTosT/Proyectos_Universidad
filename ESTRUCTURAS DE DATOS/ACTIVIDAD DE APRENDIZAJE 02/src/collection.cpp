#include "collection.hpp"
using namespace std;

Collection::Collection(){}


int Collection::findIndex(const string& searchedBarcode) const{
    for (int i = 0; i <= this->lastIndex; i++){
        if(this->productArray[i].getBarcode()==searchedBarcode) {
        return i;
        }
    } 
    return -1;
}

bool Collection::add(const Product& newProduct){
    int index = this->findIndex(newProduct.getBarcode());

    if (index != -1){
        this->productArray[index].setStock((this->productArray[index].getStock()) + 1);
        return true;
    }

    if(this->lastIndex < 499){
        this->lastIndex++;
        this->productArray[this->lastIndex] = newProduct;
        this->productArray[this->lastIndex].setStock(1);
        return true;
    }

    return false;
}

bool Collection::del(const string& searchedBarcode){
   int index = this->findIndex(searchedBarcode);

   if (index != -1){
    int currentStock = this->productArray[index].getStock();

    if (currentStock > 0){
        this->productArray[index].setStock(currentStock-1);
    }
    return true;

   }
   return false;
}

string Collection::printCollection() const{
    if(this->lastIndex == -1){
        return "\nEl inventario se encuentra vacio...";
    }

    string result = "";

    for (int i = 0; i <= this->lastIndex; i++){
       result += this-> productArray[i].toString() + "\n-------------------------\n";
    } 
    return result;
}

bool Collection::exists(const string& barcode) const{
    if (findIndex(barcode) != -1){
        return true;
    }
    else {return false;}
}

    



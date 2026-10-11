#ifndef __PRODUCT_H__
#define __PRODUCT_H__
#include <string>
#include "date.hpp"

class Product{
    private:
        std::string barcode;
        std::string name;
        float weight;
        Date incomeDate;
        float wholePrice;
        float retailPrice;
        int stock;

        bool isBarcodeValid(const std::string&) const;
    public:
        Product();
        Product(const Product&);
        
        std::string getBarcode() const;
        std::string getName() const;
        float getWeight() const;
        Date getIncomeDate() const;
        float getWholePrice() const;
        float getRetailPrice() const;
        int getStock() const;

        std::string toString() const;
        
        void setBarcode(const std::string&);
        void setName(const std::string&);
        void setWeight(const float&);
        void setIncomeDate(const Date&);
        void setWholePrice(const float&);
        void setRetailPrice(const float&);
        void setStock(const int&);

        Product& operator = (const Product&);

        bool operator == (const Product&) const;
        bool operator != (const Product&) const;
        bool operator < (const Product&) const;
        bool operator <= (const Product&) const;
        bool operator > (const Product&) const;
        bool operator >= (const Product&) const;

};

#endif // __PRODUCT_H__
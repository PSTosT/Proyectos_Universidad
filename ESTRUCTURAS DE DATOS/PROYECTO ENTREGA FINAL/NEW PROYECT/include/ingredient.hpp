#ifndef __INGREDIENT_H__
#define __INGREDIENT_H__
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

inline const int wIngredientName = 23;
inline const int wQuantity = 16;
inline const int wUnit = 10;


class Ingredient{
    private:
        std::string name;
        float quantity;
        std::string unit;
    public:
        //Constructores...
        Ingredient();
        Ingredient(const Ingredient&);

        //Getters
        std::string getName() const;
        float getQuantity() const;
        std::string getUnit() const;

        //Setters
        void setName(const std::string&);
        void setQuantity(const float&);
        void setUnit(const std::string&);

        //To string...
        std::string toString() const; 

        //Sobrecarga de operadores
        Ingredient& operator=(const Ingredient&);
        bool operator==(const Ingredient&) const;
        bool operator!=(const Ingredient&) const;
        bool operator<=(const Ingredient&) const;
        bool operator<(const Ingredient&) const;
        bool operator>(const Ingredient&) const;
        bool operator>=(const Ingredient&) const;

        int compare(const Ingredient&) const;
        static int compare(const Ingredient&, const Ingredient&);
        static int compareByName(const Ingredient&, const Ingredient&);
        static int compareByQuantity(const Ingredient&, const Ingredient&);
        static int compareByUnit(const Ingredient&, const Ingredient&);
       
        //Sobrecarga de operadores de flujo 
        friend std::ostream& operator<<(std::ostream&, const Ingredient&);
        friend std::istream& operator>>(std::istream&, Ingredient&);

        std::string serialize(const char& delim = '*') const;
        void deserialize(const std::string&, const char& delim = '*');
};
#endif // __INGREDIENT_H__
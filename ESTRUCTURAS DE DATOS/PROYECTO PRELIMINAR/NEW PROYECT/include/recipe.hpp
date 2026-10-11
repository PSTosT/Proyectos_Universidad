#ifndef __RECIPE_H__
#define __RECIPE_H__

#include <string>
#include "list.hpp"
#include "ingredient.hpp"
#include "ingredientui.hpp"
#include "name.hpp"
#include <sstream>
#include <iomanip>

//Anchos para formateo del texto
inline const int wRecipeName = 30;
inline const int wAuthorName = 20;
inline const int wPrepTime = 25;
inline const int wCategory = 10;


class Recipe {
    private:
        std::string name;
        Name authorName;
        int prepTime;
        std::string procedure;
        std::string category;
        List<Ingredient, 1024> ingredientList;

    public:
        
        //Constructorres y destructor 
        Recipe();
        Recipe(const Recipe&);
        ~Recipe();

        //Getters
        std::string getName() const;
        Name getAuthorName() const;
        int getPrepTime() const;
        std::string getProcedure() const;
        std::string getCategory() const;
        List<Ingredient,1024>& getIngredientList();

        //Setters 
        void setName(const std::string&);
        void setAuthor(const Name&);
        void setPrepTime(const int&);
        void setProcedure(const std::string&);
        void setCategory(const std::string&);

        std::string toString(const bool s = false);

        Recipe& operator=(const Recipe&);

        //Sobrecarga de operadores
        bool operator==(const Recipe&) const;
        bool operator!=(const Recipe&) const;
        bool operator<(const Recipe&) const;
        bool operator<=(const Recipe&) const;
        bool operator>(const Recipe&) const;
        bool operator>=(const Recipe&) const;

        //Compare
        int compare(const Recipe&) const;
        static int compare(const Recipe&, const Recipe&);
        static int compareByName(const Recipe&, const Recipe&);
        static int compareByPrepTime(const Recipe&, const Recipe&);
        static int compareByCategory(const Recipe&, const Recipe&);
        static int compareByAuthor(const Recipe&, const Recipe&);


        //Operadores de flujo
        friend std::ostream& operator<<(std::ostream&, const Recipe&);
        friend std::istream& operator>>(std::istream&, Recipe&);
        
        //Serializacion
        std::string serialize(const char& delim = '*') const;
        void deserialize(const std::string&, const char& delim = '*');





};
#endif // __RECIPE_H__
#ifndef __RECIPE_H__
#define __RECIPE_H__

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include "ingredient.hpp"
#include "name.hpp"
#include "chef.hpp"

// Anchos para formateo del texto
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
    std::vector<Ingredient> ingredientList;

public:
    // Constructores y destructor
    Recipe();
    Recipe(const Recipe&);
    ~Recipe();

    // Getters
    std::string getName() const;
    Name getAuthorName() const;
    int getPrepTime() const;
    std::string getProcedure() const;
    std::string getCategory() const;
    std::vector<Ingredient>& getIngredientList();
    const std::vector<Ingredient>& getIngredientList() const;

    // Setters
    void setName(const std::string&);
    void setAuthor(const Name&);
    void setPrepTime(const int&);
    void setProcedure(const std::string&);
    void setCategory(const std::string&);

    // Relacion de Asociacion / Colaboracion con la clase Chef
    void asignarChefAutor(const Chef& chef);

    // Metodos auxiliares para gestionar el vector de ingredientes
    void addIngredient(const Ingredient& ing);
    bool removeIngredientByIndex(int index);

    std::string toString(const bool s = false) const;

    Recipe& operator=(const Recipe&);

    // Sobrecarga de operadores
    bool operator==(const Recipe&) const;
    bool operator!=(const Recipe&) const;
    bool operator<(const Recipe&) const;
    bool operator<=(const Recipe&) const;
    bool operator>(const Recipe&) const;
    bool operator>=(const Recipe&) const;

    // Compare
    int compare(const Recipe&) const;
    static int compare(const Recipe&, const Recipe&);
    static int compareByName(const Recipe&, const Recipe&);
    static int compareByPrepTime(const Recipe&, const Recipe&);
    static int compareByCategory(const Recipe&, const Recipe&);
    static int compareByAuthor(const Recipe&, const Recipe&);

    // Serializacion
    std::string serialize(const char& delim = '*') const;
    void deserialize(const std::string&, const char& delim = '*');
};

#endif // __RECIPE_H__

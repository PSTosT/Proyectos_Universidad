#include "name.hpp"
Name::Name(std::string& n) : first(n) {   }

std::string Name::getFirst() const{
    return this->first;
}

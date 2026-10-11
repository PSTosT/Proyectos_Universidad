#include "name.hpp"

using namespace std;



Name::Name() {  }

Name::Name(const Name& n) : last(n.last), first(n.first) {  }

Name::Name(const std::string& l, const std::string& f) : last(l), first(f){   }

void Name::setLast(const string& str) {
    this -> last = str;
}

string Name::toString() const {
    return this ->last + ", " +this->first;
}

void Name::setFirst(const string& str) {
    this -> first = str;
}

Name& Name::operator = (const Name& n) {
    this->last = n.last;
    this->first = n.first;

    return *this;
}

bool Name::operator == (const Name& n) const{
    return this->toString() == n.toString();
}



bool Name::operator < (const Name& n) const{
    return this->toString() < n.toString();
}

bool Name::operator != (const Name& n) const{
    return !(*this == n);
}


bool Name::operator <= (const Name& n) const{
    return *this < n or *this == n;
}

bool Name::operator > (const Name& n) const{
    return (*this <= n);
}

bool Name::operator >= (const Name& n) const{
    return (*this < n);
}

std::string Name::serialize(const char& delim){
    //Pendientes para la siguiente clase
}

void Name::deserialize(const std::string&, const char& delim){
    //Pendientes para la siguiente clase
}

std::ostream& operator << (std::ostream&, const Name&){
    //Pendientes para la siguiente clase
}
std::istream& operator >> (std::istream&, const Name&){
    //Pendientes para la siguiente clase
}




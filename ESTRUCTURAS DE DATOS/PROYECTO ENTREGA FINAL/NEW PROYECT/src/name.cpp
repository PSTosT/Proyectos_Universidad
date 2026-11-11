
#include "name.hpp"
using namespace std;

Name::Name(){ }

Name::Name(const Name& other) : first(other.first), last(other.last) { }

Name::~Name(){ }

std::string Name::getFirst() const{  
    return this->first;
}

std::string Name::getLast() const{
    return this->last;
}

void Name::setFirst(const std::string& f){
    this->first = f;
}

void Name::setLast(const std::string& l){
    this->last = l;
}

std::string Name::toString() const{
    std::string result;
    result += this->first 
    + " " + this->last;

    return result;
}

Name& Name::operator=(const Name& other){
    this->first = other.first;
    this->last = other.last;

    return *this;
}

bool Name::operator==(const Name& other) const{
    return (this->first == other.first) and (this->last == other.last);
}

bool Name::operator!=(const Name& other) const{
    return !(*this == other); 
}

bool Name::operator<(const Name& other) const{
    if (this->first == other.first) {
        return this->last < other.last;
    }
    return this->first < other.first;
}

bool Name::operator<=(const Name& other) const{
    return (*this < other) or (*this == other);
}

bool Name::operator>(const Name& other) const{
    return !(*this <= other);
}

bool Name::operator>=(const Name& other) const{
    return !(*this < other);
}

int Name::compare(const Name& other) const{
    int res = this->first.compare(other.first);
    if (res == 0) { 
        return this->last.compare(other.last);
    }
    return res;
}

int Name::compare(const Name& a, const Name& b){
    return a.compare(b);
}

int Name::compareByFirst(const Name& a, const Name& b){
    return a.first.compare(b.first);
}

int Name::compareByLast(const Name& a, const Name& b){
    return a.last.compare(b.last);
}

string Name::serialize(const char& delim) const{
    string result;
    result += this->last + delim;
    result += this->first;

    return result;
}

void Name::deserialize(const string& str, const char& delim){
    stringstream mySStream(str);

    getline(mySStream,this->last,delim);
    getline(mySStream,this->first);
}

istream& operator>>(istream& is, Name& i){

    if (!getline(is, i.first)) return is;
    getline (is, i.last);
    return is;
}

ostream& operator<<(ostream& os, const Name& i){
    os << i.first << endl;
    os << i.last << endl;
    return os;
}

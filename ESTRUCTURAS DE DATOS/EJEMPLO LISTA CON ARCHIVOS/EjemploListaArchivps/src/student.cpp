#include "student.hpp"

using namespace std;

Student::Student(){ }

Student::Student(const Student& s) : code(s.code), name(s.name), birthDate(s.birthDate), career(s.career), startDate(s.startDate), grade(s.grade){ }

std::string Student::getCode() const{
    return this->code;
}

Name Student::getName() const{
    return this->name;
}

Date Student::getBirthDate() const {
    return this->birthDate;
}

std::string Student::getCareer() const {
    return this->career;
}

Date Student::getStartDate() const {
    return this->startDate;
}

float Student::getGrade() const {
    return this->grade;
}

string Student::toString(const bool&) const {
    string result;
    char myGrade[8];

    sprintf(myGrade, "%7.2f", this->grade);

    result+= this->code;
    result+= " | ";
    result+= this->name.toString();
    result.resize(45, ' ');
    result+= " | ";
    result+= this->birthDate.toString();
    result+= " | ";
    result+= career;
    result+= " | ";
    result+= this->startDate.toString();
    result+= " | ";
    result+= myGrade;

    return result;
}

void Student::setCode(const string& c){
    this->code = c;
}

void Student::setName(const Name& n){
    this->name = n;
}

void Student::setBirthDate(const Date& d){
    this->birthDate = d;
}

void Student::setCareer(const std::string& c){
    this->career = c;
}

void Student::setStartDate(const Date& d){
    this->startDate = d;
}

void Student::setGrade(const float& g){
    this->grade = g;
}

Student& Student::operator = (const Student& s) {
    this->code = s.code;
    this->name = s.name;
    this->birthDate = s.birthDate;
    this->career = s.career;
    this->startDate = s.startDate;
    this->grade = s.grade;
    return *this;
}

bool Student::operator == (const Student& s) const { return this->code == s.code; }
bool Student::operator != (const Student& s) const { return this->code != s.code; }
bool Student::operator < (const Student& s) const { return this->code < s.code; }
bool Student::operator <= (const Student& s) const { return this->code <= s.code; }
bool Student::operator > (const Student& s) const { return this->code > s.code; }
bool Student::operator >= (const Student& s) const { return this->code >= s.code; }

int Student::compare(const Student& s) const {
    return this->code.compare(s.code);
}

int Student::compare(const Student& a, const Student& b) {
    return a.compare(b);
}

int Student::compareByCode(const Student& a, const Student& b) {
    return a.code.compare(b.code);
}

int Student::compareByName(const Student& a, const Student& b) {
    // Requires a compare function inside the Name class
    return 0; 
}

int Student::compareByBirthDate(const Student& a, const Student& b) {
    return a.birthDate.compare(b.birthDate);
}

int Student::compareByCareer(const Student& a, const Student& b) {
    return a.career.compare(b.career);
}

int Student::compareByStartDate(const Student& a, const Student& b) {
    return a.startDate.compare(b.startDate);
}

int Student::compareByGrade(const Student& a, const Student& b) {
    if(a.grade < b.grade) return -1;
    if(a.grade > b.grade) return 1;
    return 0;
}

// Extracted exactly as shown in the presentation material[cite: 3]
istream& operator >> (istream& is, Student& s) {
    string myStr;

    getline(is, s.code);
    is >> s.name;
    is >> s.birthDate;
    getline(is, s.career);
    is >> s.startDate;
    getline(is, myStr);
    s.grade = stof(myStr);

    return is;
}

// Extracted exactly as shown in the presentation material[cite: 3]
ostream& operator << (ostream& os, const Student& s) {
    os << s.code << endl;
    os << s.name << endl;
    os << s.birthDate << endl;
    os << s.career << endl;
    os << s.startDate << endl;
    os << s.grade;

    return os;
}
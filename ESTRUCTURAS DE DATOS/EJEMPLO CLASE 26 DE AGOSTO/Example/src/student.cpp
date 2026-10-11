#include <student.hpp>

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

Student& Student::operator = (const Student&)
{
    
}

bool Student::operator == (const Student&) const
{
    
}

bool Student::operator != (const Student&) const
{
    
}

bool Student::operator < (const Student&) const
{
    
}

bool Student::operator <= (const Student&) const
{
    
}

bool Student::operator > (const Student&) const
{
    
}

bool Student::operator >= (const Student&) const
{
    
}

int Student::compare(const Student&) const
{
    
}

int Student::compare(const Student&, const Student&)
{
    
}

int Student::compareByCode(const Student&, const Student&)
{
    
}

int Student::compareByName(const Student&, const Student&)
{
    
}

int Student::compareByBirthDate(const Student&, const Student&)
{
    
}

int Student::compareByCareer(const Student&, const Student&)
{
    
}

int Student::compareByStartDate(const Student&, const Student&)
{
    
}

int Student::compareByGrade(const Student&, const Student&)
{
    
}

std::ostream& operator << (std::ostream&, const Student&)
{
    
}

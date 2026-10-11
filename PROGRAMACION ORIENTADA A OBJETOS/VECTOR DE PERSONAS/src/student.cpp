#include "student.hpp"
using namespace std;

Student::Student() : name("NoName"), curp("NoCurp"), phoneNumber("NullPhoneNumber"), grade(0.0f), bDay(1), bMonth(1), bYear(2000) { }

Student::Student(const Student& s) : name(s.name), curp(s.curp), phoneNumber(s.phoneNumber), grade(s.grade), bDay(s.bDay), bMonth(s.bMonth), bYear(s.bYear) { }

Student::~Student() { }

void Student::RecibeMSG(const std::string& m){
    this->Mensaje = m;
}


//Setters
void Student::setName(
    const std::string& n) { this->name = n; }

void Student::setCurp(const std::string& c) { 
    this->curp = c; }

void Student::setPhoneNumber(const std::string& p) { 
    this->phoneNumber = p; }

void Student::setGrade(const float& g) { 
    this->grade = g; }

void Student::setBirthDate(int d, int m, int y) {
    this->bDay = d;
    this->bMonth = m;
    this->bYear = y;
}

void Student::setMensaje(const std::string& m){
    this->Mensaje = m;
}


//Getters
std::string Student::getName() const { 
    return this->name; }

std::string Student::getCurp() const { 
    return this->curp; }

std::string Student::getPhoneNumber() const { 
    return this->phoneNumber; }
    
std::string Student::getMensaje() const{
    return this->Mensaje;
}

float Student::getGrade() const { 
    return this->grade; }

int Student::getBDay() const { 
    return this->bDay; }

int Student::getBMonth() const { 
    return this->bMonth; }

int Student::getBYear() const { 
    return this->bYear; }

int Student::getAge() const {
    time_t t = time(0); 
    tm* now = localtime(&t);
    
    int currentYear = now->tm_year + 1900;
    int currentMonth = now->tm_mon + 1;
    int currentDay = now->tm_mday;
    
    int calculatedAge = currentYear - this->bYear;
    
    if (currentMonth < this->bMonth or (currentMonth == this->bMonth and currentDay < this->bDay)) {
        calculatedAge--;
    }
    
    return calculatedAge;
}

std::string Student::toString() const {
    return "Nombre: " + this->name + 
           " | CURP: " + this->curp + 
           " | Edad: " + std::to_string(this->getAge()) + " años" +
           " | Tel: " + this->phoneNumber;
}
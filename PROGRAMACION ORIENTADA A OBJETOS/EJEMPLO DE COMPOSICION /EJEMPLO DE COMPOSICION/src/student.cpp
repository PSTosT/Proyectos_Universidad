#include "student.hpp"

using namespace std;

Student::Student() : name(""), major(""), studentCode("") {}

Student::Student(const string& n, const string& m, const string& c) {
    this->name = n;
    this->major = m;
    this->studentCode = c;
}

// Getters
string Student::getName() const {
    return this->name; }
string Student::getMajor() const { 
    return this->major; }
string Student::getCode() const { 
    return this->studentCode; }

// Setters
void Student::setName(const string& n) { 
    this->name = n; }
void Student::setMajor(const string& m) { 
    this->major = m; }
void Student::setCode(const string& c) { 
    this->studentCode = c; }

void Student::addSubject(const Subject& sub) {
    this->enrolledSubjects.push_back(sub);
}

void Student::clearSubjects() {
    this->enrolledSubjects.clear();
}

string Student::toString() const {
    string result = "";
    result += "Informacion del estudiante \n";
    result += "Nombre:  " + this->name + "\n";
    result += "Carrera: " + this->major + "\n";
    result += "Codigo:  " + this->studentCode + "\n";
    result += "\n";
    
    if (this->enrolledSubjects.empty()) {
        result += "No hay materias inscritas actualmente\n";
    } else {
        for (int i = 0; i < this->enrolledSubjects.size(); i++) {
            result += this->enrolledSubjects[i].toString() + "\n\n";
        }
    }
    result += "\n";
    return result;
}

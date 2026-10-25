#include "subject.hpp"

using namespace std;

Subject::Subject() : name(""), code(""), professor(""), schedule("") {}

Subject::Subject(const string& n, const string& c, const string& p, const string& s) {
    this->name = n;
    this->code = c;
    this->professor = p;
    this->schedule = s;
}

//Getters
string Subject::getName() const { return this->name; }
string Subject::getCode() const { return this->code; }
string Subject::getProfessor() const { return this->professor; }
string Subject::getSchedule() const { return this->schedule; }

//Setters
void Subject::setName(const string& n) { this->name = n; }
void Subject::setCode(const string& c) { this->code = c; }
void Subject::setProfessor(const string& p) { this->professor = p; }
void Subject::setSchedule(const string& s) { this->schedule = s; }

string Subject::toString() const {
    string result = "";
    result += "[" + this->code + "] " + this->name + "\n";
    result += "Profesor: " + this->professor + " | Horario: " + this->schedule;
    return result;
}

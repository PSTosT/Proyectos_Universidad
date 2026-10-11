#include "date.hpp"

using namespace std;
using namespace chrono;

bool Date::isValid(const int& y,const int& m,const int& d) const {
    int monthDay[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (y == 0 or m < 1 or m > 12 or d < 1){
        return false;
    }

    if (y % 4 == 0 and (y % 100 != 0 or y % 400 == 0)){
        monthDay[2]++;
    }
    if (d > monthDay[m]) {
        return false;
    }

    return true;
}

int Date::toInt() const{
    return this->year * 10000 + this->month * 100 + this->day;
}

Date::Date() {
    system_clock::time_point today(system_clock:: now());
    time_t tt(system_clock::to_time_t(today));
    struct tm* timeinfo(localtime(&tt));

    this->year = timeinfo->tm_year + 1900;
    this->month = timeinfo->tm_mon + 1;
    this->day = timeinfo->tm_mday;
}

Date::Date(const Date& d) : year(d.year), month(d.month), day(d.day) {}

Date::Date(const int& y, const int& m, const int& d) : Date() {
    if (this->isValid(y, m, d)) {
        this->year = y;
        this->month = m;
        this->day = d;
    }
}

int Date::getYear() const{
    return this->year;
}

int Date::getMonth() const{
    return this->month;
}

int Date::getDay() const{
    return this->day;
}

string Date::toString() const {
    char myDate[12];
    sprintf(myDate, "%02i/%02i/%04i", this->day, this->month, this->year);
    return myDate;
}

void Date::setYear(const int& y){
    if(this->isValid(y, this->month, this->day)){
        this -> year = y;
    }
}

void Date::setMonth(const int& m){
    if(this->isValid(this->year, m, this->day)){
        this -> month = m;
    }
}

void Date::setDay(const int& d){
    if(this->isValid(this->year, this->month, d)){
        this -> day = d;
    }
}

Date& Date::operator=(const Date& d){
    this->year = d.year;
    this->month = d.month;
    this->day = d.day;
    return *this;
}

bool Date::operator == (const Date& d) const{
    return this->toInt() == d.toInt();
}

bool Date::operator != (const Date& d) const{
    return !(*this == d);
}

bool Date::operator < (const Date& d) const{
    return this->toInt() < d.toInt();
}

bool Date::operator <= (const Date& d) const{
    return *this < d or *this == d; 
}

bool Date::operator > (const Date& d) const{
    return !(*this <= d);
}

bool Date::operator >= (const Date& d) const{
    return !(*this < d);
}

int Date::compare(const Date& d) const{
    return this->toInt() - d.toInt();
}

int Date::compare(const Date& a, const Date& b){
    return a.compare(b);
}

std::istream& operator >> (std::istream& is, Date& d){
   string myStr;

   getline(is, myStr);
   d.year = stoi(myStr);

   getline(is, myStr);
   d.month = stoi(myStr);

   getline(is, myStr);
   d.day = stoi(myStr);

   return is;
}

std::ostream& operator << (std::ostream& os, const Date& d){
    os << d.year << endl;
    os << d.month << endl;
    os << d.day;
    return os;
}
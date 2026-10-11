#ifndef __DATE_H__
#define __DATE_H__

#include <string>
#include <chrono>
#include <iostream>

class Date {
private:
    int year;
    int month;
    int day;

    bool isValid(const int&, const int&, const int&) const;

    int toInt() const;

public:
    Date();
    Date(const Date&);
    Date(const int&, const int&, const int&);

    int getYear() const;
    int getMonth() const;
    int getDay() const;

    std::string toString() const;
    
    void setYear(const int&);
    void setMonth(const int&);
    void setDay(const int&);

    Date& operator = (const Date&);
    
    bool operator == (const Date&) const;
    bool operator != (const Date&) const;
    bool operator < (const Date&) const;
    bool operator <= (const Date&) const;
    bool operator > (const Date&) const;
    bool operator >= (const Date&) const;
   
    int compare(const Date&) const;
    static int compare (const Date&, const Date&);

    friend std::ostream& operator << (std::ostream&, const Date&);
    friend std::istream& operator >> (std::istream&, Date&);

    std::string serialize() const;
    void deserialize(const std::string&);
};

#endif // __DATE_H__
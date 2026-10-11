#ifndef __STUDENT_H__
#define __STUDENT_H__

#include <string>
#include <iostream>
 
#include "name.hpp"
#include "date.hpp"

class Student {
private:
    std::string code;
    Name name;
    Date birthDate;
    std::string career;
    Date startDate;
    float grade;

public:
    Student();
    Student(const Student&);

    std::string getCode() const;
    Name getName() const;
    Date getBirthDate() const;
    std::string getCareer() const;
    Date getStartDate() const;
    float getGrade() const;

    std::string toString(const bool& s = false) const;

    void setCode(const std::string&);
    void setName(const Name&);
    void setBirthDate(const Date&);
    void setCareer(const std::string&);
    void setStartDate(const Date&);
    void setGrade(const float&);

    Student& operator = (const Student&);

    bool operator == (const Student&) const;
    bool operator != (const Student&) const;
    bool operator < (const Student&) const;
    bool operator <= (const Student&) const;
    bool operator > (const Student&) const;
    bool operator >= (const Student&) const;

    int compare(const Student&) const;
    static int compare(const Student&, const Student&);

    static int compareByCode(const Student&, const Student&);
    static int compareByName(const Student&, const Student&);
    static int compareByBirthDate(const Student&, const Student&);
    static int compareByCareer(const Student&, const Student&);
    static int compareByStartDate(const Student&, const Student&);
    static int compareByGrade(const Student&, const Student&);

    friend std::ostream& operator << (std::ostream&, const Student&);
    friend std::istream& operator >> (std::istream&, Student&);

    std::string serialize() const;
    void deserialize(const std::string&);
};


#endif // __STUDENT_H__
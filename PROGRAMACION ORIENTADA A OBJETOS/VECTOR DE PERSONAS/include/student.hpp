#ifndef __STUDENT_HPP__
#define __STUDENT_HPP__

#include <string>
#include <iostream>
#include <ctime>

class Student {
private:
    std::string name;
    std::string curp;
    std::string phoneNumber;
    std::string Mensaje = "";
    float grade;
    int bDay, bMonth, bYear;

public:
    Student();
    Student(const Student&);
    ~Student();


    void RecibeMSG(const std::string&);
    // Setters
    void setName(const std::string&);
    void setCurp(const std::string&);
    void setPhoneNumber(const std::string&);
    void setGrade(const float&);
    void setBirthDate(int d, int m, int y);
    void setMensaje(const std::string&);

    // Getters
    std::string getName() const;
    std::string getCurp() const;
    std::string getPhoneNumber() const;
    std::string getMensaje() const;
    float getGrade() const;
    int getBDay() const;
    int getBMonth() const;
    int getBYear() const;
    int getAge() const;

    std::string toString() const;
};

#endif // __STUDENT_HPP__
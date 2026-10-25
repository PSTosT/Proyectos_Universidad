#ifndef __STUDENT_HPP__
#define __STUDENT_HPP__

#include <string>
#include <vector>
#include "subject.hpp"

class Student {
private:
    std::string name;
    std::string major;
    std::string studentCode;
    std::vector<Subject> enrolledSubjects;

public:
    Student(); 
    Student(const std::string&, const std::string&, const std::string&);

    // Getters
    std::string getName() const;
    std::string getMajor() const;
    std::string getCode() const;

    // Setters
    void setName(const std::string&);
    void setMajor(const std::string&);
    void setCode(const std::string&);

    void addSubject(const Subject&);
    void clearSubjects();
    
    std::string toString() const;
};

#endif

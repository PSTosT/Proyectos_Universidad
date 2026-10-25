#ifndef __SUBJECT_HPP__
#define __SUBJECT_HPP__

#include <string>

class Subject {
private:
    std::string name;
    std::string code;
    std::string professor;
    std::string schedule;

public:
    // Constructores
    Subject(); 
    Subject(const std::string&, const std::string&, const std::string&, const std::string&);
    
    // Getters
    std::string getName() const;
    std::string getCode() const;
    std::string getProfessor() const;
    std::string getSchedule() const;

    // Setters
    void setName(const std::string&);
    void setCode(const std::string&);
    void setProfessor(const std::string&);
    void setSchedule(const std::string&);

    std::string toString() const;
};

#endif

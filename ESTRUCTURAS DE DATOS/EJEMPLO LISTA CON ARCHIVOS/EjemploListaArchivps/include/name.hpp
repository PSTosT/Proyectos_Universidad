#ifndef __NAME_H__
#define __NAME_H__

#include <string>
#include <iostream>

class Name{
private:
    std::string last;
    std::string first;

public:
    Name();
    Name(const Name&);
    Name(const std::string&, const std::string&);

    std::string getLast() const;
    std::string getFirst() const; // Fixed typo

    std::string toString() const;

    void setLast(const std::string&);
    void setFirst(const std::string&);

    Name& operator = (const Name&);

    bool operator == (const Name&) const;
    bool operator != (const Name&) const;
    bool operator < (const Name&) const;
    bool operator <= (const Name&) const;
    bool operator > (const Name&) const;
    bool operator >= (const Name&) const;

    friend std::ostream& operator << (std::ostream&, const Name&);
    friend std::istream& operator >> (std::istream&, Name&);

    std::string serialize(const char& delim = '*');
    void deserialize(const std::string&, const char& delim = '*');
};

#endif // __NAME_H__
#ifndef __NAME_H__
#define __NAME_H__
#include <string>
#include <istream>
#include <sstream>
class Name{
    private:
    std::string first;
    std::string last;
    public:

    //Constructores y destructor
    Name();
    Name(const Name&);
    ~Name();

    //Getters

    std::string getFirst() const;
    std::string getLast() const;

    //Setters 
    void setFirst(const std::string&);
    void setLast(const std::string&);

    std::string toString() const;

    Name& operator=(const Name&);

    //Sobrecarga de operadores

    bool operator==(const Name&) const;
    bool operator!=(const Name&) const;
    bool operator<(const Name&) const;
    bool operator<=(const Name&) const;
    bool operator>(const Name&) const;
    bool operator>=(const Name&) const;

    //Comparadores

    int compare(const Name&) const;
    static int compare(const Name&, const Name&);
    static int compareByFirst(const Name&, const Name&);
    static int compareByLast(const Name&, const Name&);

    //Operadores de flujo
    friend std::ostream& operator<<(std::ostream&, const Name&);
    friend std::istream& operator>>(std::istream&, Name&);

    //Serializacion y deserializacion...

    std::string serialize(const char& delim = '*') const;
    void deserialize(const std::string&, const char& delim = '*');
};  
#endif // __NAME_H__
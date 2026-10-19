#ifndef __NAME_H__
#define __NAME_H__
#include <string>
class Name{
    private:
        std::string first;
    public:
        Name(std::string&);
        std::string getFirst() const;
};
#endif // __NAME_H__
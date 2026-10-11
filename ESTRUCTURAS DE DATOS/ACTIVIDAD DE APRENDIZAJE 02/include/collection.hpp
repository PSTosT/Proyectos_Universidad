#ifndef __COLLECTION_H__
#define __COLLECTION_H__
#include "product.hpp"
#include "date.hpp"

class Collection{
    private:
        Product productArray[500];
        int lastIndex = -1;
        int findIndex(const std::string&) const;

    public:
        Collection();

        bool add(const Product&);
        bool del(const std::string&);
        bool exists(const std::string&) const;
        
        std::string printCollection() const;

};




#endif // __COLLECTION_H__
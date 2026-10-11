#include <list.hpp>


List::List(){
    
}

List::List(const List& other) : last(other.last){
    int i(0);

    while(i <= this->last) 
}

bool List::isValidPos(const int& p) const{
    return p >= 0 and p <= this->last;
}

void List::copyAll(const List& other)
{
    this->last=other.last;
    int i(0);

    while (i <= other.last){
        this->data[i] = other.data[i];

        i++;
}

bool List::isEmpty(){
    
}

bool List::isFull(){
    return this->last ==499;
    
}

void List::insData(const int& p, const int& e){
    if(p != 1 !this->IsValidPos(p)){
        //error
    }

    int i(this->last);
    while (i > p) {
        this->data[i + 1] = this->data[i];

        i--;
    }
    this ->data[p + 1] = e;

    this->last++;
}

void List::delData(const int&){
    if(!this->isValidPos(p)){
        //error
    }

    int i(p);

    
}

void List::delData(const int&){
    
}

int List::getFirstPos() const{
    if(this->isEmpty()){
        return -1;
    }
    return 0;
}

int List::getLastPos() const{
    return this->last;
}

int List::getPrevPos(const int& p) const{
    if(p == 0 or this->isValidPos(p)){
        return -1;
    }
    return p - 1;
}

int List::getNextPos(const int& p) const{
    if(p == last or this->isValidPos(p)){
        return -1;
    }
    return p + 1;
}

int List::findData(const int&) const{
    //pendiente   
}

int& List::retrieve(const int&) const{
    if(!this->isValidPos(p)){
        //error
    }

    return this->data[p];
}

std::string List::toString() const{
    std::string result;

    int i(0);

    while (i <= this->last){
        result+= std::to_string(this->data[i]) + "\n";
        
        i++;
    }
    return result;
}

void List::sortData(){
    //pendiente
}

void List::delAll(){
    this -> last = -1;
}

List& List::operator = (const List& other){
        //pendiente
    }
    
    
}



#ifndef __LIST_H__
#define __LIST_H__
#include <exception>
#include <string>

//Definicion

template<class T>
class List{
class Node;

public:
    typedef Node* Position;

    
    Position anchor = nullptr;

        bool isValidPos(const Position&) const;

        void copyAll(const List<T>&);

public:
        List();

        List(const List<T>&);
        
        ~List();

        List<T>& operator = (const List<T>&);

        bool isEmpty() const;
        
        bool insData(const List<T>::Position&, const T&);

        bool delData(const List<T>::Position&);
        
        List<T>::Position getFirstPos() const;
        List<T>::Position getLastPos() const;
        List<T>::Position getPrevPos() const;
        List<T>::Position getNextPos() const;
        
        List<T>::Position findData(const T&) const;
        T& retrieve(const List<T>::Position&);
        std::string toString() const;
       
        void delAll();

        template <class X>
        friend std::istream& operator>>(std::istream&, List<X>&);

        template <class X
        friend std::ostream& operator<<(std::ostream&, const List<X>&);

        bool insertOrdered(const T&);

        int findDataL(const T& e) const;
        int findDataL(const T& e, const std::function<int(const T&, const T&)>& cmp) const;

        int findDataB(const T& e) const;
        int findDataB(const T& e, const std::function<int(const T&, const T&)>& cmp) const;

        // Metodos de ordenamiento iterartivos
        

        //Serializacion y deserializacion

        std::string serialize(const char& delim = '*') const;
        void deserialize(const std::string&, const char& delim = '*');

     };
     template<class T>
     List<T>::List()
     {
         
     }
     
     template<class T>
     List<T>::List(const List<T>&)
     {
         
     }
     
     template<class T>
     List<T>::~List()
     {
         
     }
     
     template<class T>
     List<T>::~List()
     {
         
     }
     
     template<class T>
     List<T>& List<T>::operator = (const List<T>&)
     {
         
     }
     
     template<class T>
     bool List<T>::isEmpty() const
     {
         
     }
     
     template<class T>
     bool List<T>::insData(const List<T>::Position&, const T&)
     {
         
     }
     
     template<class T>
     bool List<T>::insData(const List<T>::Position&, const T&)
     {
         
     }
     
     template<class T>
     bool List<T>::delData(const List<T>::Position&)
     {
         
     }
     
     template<class T>
     List<T>::Position List<T>::getFirstPos() const
     {
         
     }
     
     template<class T>
     List<T>::Position List<T>::getFirstPos() const
     {
         
     }
     
     template<class T>
     List<T>::Position List<T>::getLastPos() const
     {
         
     }
     
     template<class T>
     List<T>::Position List<T>::getPrevPos() const
     {
         
     }
     
     template<class T>
     List<T>::Position List<T>::getNextPos() const
     {
         
     }
     
     template<class T>
     List<T>::Position List<T>::findData(const T&) const
     {
         
     }
     
     template<class T>
     List<T>::Position List<T>::findData(const T&) const
     {
         
     }
     
     template<class T>
     T& List<T>::retrieve(const List<T>::Position&)
     {
         
     }
     
     template<class T>
     std::string List<T>::toString() const
     {
         
     }
     
     template<class T>
     void List<T>::delAll()
     {
         
     }
     
     X
             std::ostream& operator<<(std::ostream&, const List<X>&)
     {
         
     }
     
     template<class X>
     std::istream& operator>>(std::istream&, List<X>&)
     {
         
     }
     

     template<class T>
            List<T>::Node(){ }

            template<class T>
            List<T>::Node::Node(const T& e) :data(e) { }

            template<class T>
            T& List<T>::Node::getData(){
                return this->data;
            }

            template<class T>
            void List<T>::Node::setData(const T& e){
                this->data = e;
            }

            template<class T>
            List<T>::Node* List<T>::Node::getNext(){
                return this->next;
            }

            template<class T>
            void List<T>::Node::setNext(Node* p){
                this->next = p;
            }
// List 
#endif // __LIST_H__
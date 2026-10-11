#include "list.hpp"
#include "student.hpp"
#include "userinterface.hpp"

int main() {
    // Instantiate the list with the exact size required by the UserInterface
    List<Student, 500> myList; 
    
    UserInterface myUI(myList);
    
    return 0;
}
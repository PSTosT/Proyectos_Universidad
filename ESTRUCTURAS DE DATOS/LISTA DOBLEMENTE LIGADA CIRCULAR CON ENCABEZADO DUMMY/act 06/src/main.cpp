#include "song.hpp"
#include "list.hpp"
#include "userinterface.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    List<Song> myList; 
    UserInterface myUI(myList);
}
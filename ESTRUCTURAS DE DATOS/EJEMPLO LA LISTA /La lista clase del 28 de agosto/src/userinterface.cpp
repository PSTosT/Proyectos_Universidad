#include "userinterface.hpp"

using namespace std;
using namespace chrono;
UserInterface::UserInterface(List& l) : myListRef(&l) {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_real_distribution<int> distribution(111, 999);
    auto randomInt = bind(distribution, generator);

    int myInt;

    for(int i(0); i < 20; i++){
        myInt = randomInt();

        cout << "Aniadiendo " << myInt << endl;

        myListRef->insData(myListRef->getLastPos(), myInt);
    }
    cout << endl < endl;\

    cout << "Contenido de la lista>" <<endl;

    cout << myListRef -> toString
}

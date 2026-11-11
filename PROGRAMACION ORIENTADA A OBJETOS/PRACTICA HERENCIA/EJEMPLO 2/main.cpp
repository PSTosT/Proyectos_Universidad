#include <iostream>
class Cuenta {
    private:
        double saldo;
    public:
        Cuenta(double inicial) : saldo(inicial) {}

        void depositar(double cantidad) {
            if (cantidad > 0) saldo += cantidad;
        }

        void mostrarSaldo() const {
            std::cout << "Saldo: " << saldo << "\n";
        }
};
 
int main() {
    Cuenta cuenta(765);
    cuenta.depositar(87);
    cuenta.mostrarSaldo();

    Cuenta cuenta1(987);
    cuenta1.depositar(1008);
    cuenta1.mostrarSaldo();
    return 0;
}
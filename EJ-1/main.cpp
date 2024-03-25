#include <iostream>
#include <random>

using namespace std;

int main() {

    int numero;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(2, 20);

    for (int i = 0; i < 10; i++){
        numero = dis(gen);
        cout << "El numero " << i << " aleatorio es: " << numero << endl;
    }

    return 0;
}

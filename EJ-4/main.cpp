#include <iostream>

using namespace std;

int main()
{

    // creacion de vector con 30 elementos aleatorios cada vez distintos al compilar entre 1 y 15
    int vector[30];
    for (int i = 0; i < 30; i++)
    {
        vector[i] = rand() % 15 + 1;
    }

    // calcular la moda del vector
    int moda = 0;
    int frecuencia = 0;
    for (int i = 0; i < 30; i++)
    {
        int contador = 0;
        for (int j = 0; j < 30; j++)
        {
            if (vector[i] == vector[j])
            {
                contador++;
            }
        }
        if (contador > frecuencia)
        {
            frecuencia = contador;
            moda = vector[i];
        }
    }

    for (int i = 0; i < 30; i++)
    {
        cout << vector[i] << " ";
    }

    cout << "La moda del vector es: " << moda << endl;

    return 0;
}

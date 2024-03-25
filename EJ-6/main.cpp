#include <iostream>
#include <string>
#include <algorithm> // Para std::sort

using namespace std;

class Auto
{
private:
    string marca;
    string modelo;
    int anio;

public:
    Auto(string marca, string modelo, int anio);
    void getDatos(string &marca, string &modelo, int &anio);
    void setDatos(string marca, string modelo, int anio);

    // Función para comparar autos por año
    static bool compararPorAnio(const Auto &a, const Auto &b);
};

Auto::Auto(string marca, string modelo, int anio) : marca(marca), modelo(modelo), anio(anio)
{
}

void Auto::getDatos(string &marca, string &modelo, int &anio)
{
    marca = this->marca;
    modelo = this->modelo;
    anio = this->anio;
}

void Auto::setDatos(string marca, string modelo, int anio)
{
    this->marca = marca;
    this->modelo = modelo;
    this->anio = anio;
}

// Comparador por año
bool Auto::compararPorAnio(const Auto &a, const Auto &b)
{
    return a.anio < b.anio;
}

int main()
{
    string marca, modelo;
    int anio;

    Auto auto1("Toyota", "Corolla", 2020);
    auto1.getDatos(marca, modelo, anio);
    cout << "Marca: " << marca << ", Modelo: " << modelo << ", Año: " << anio << endl;

    Auto auto2("Nissan", "Sentra", 2019);
    auto2.getDatos(marca, modelo, anio);
    cout << "Marca: " << marca << ", Modelo: " << modelo << ", Año: " << anio << endl;

    // Agregar todos los objetos a un vector
    Auto autos[2] = {auto1, auto2};

    // Ordenar los autos por año
    sort(autos, autos + 2, Auto::compararPorAnio);

    // Mostrar los autos ordenados por año
    cout << "\nAutos ordenados por año:\n";
    for (int i = 0; i < 2; ++i)
    {
        autos[i].getDatos(marca, modelo, anio);
        cout << "Marca: " << marca << ", Modelo: " << modelo << ", Año: " << anio << endl;
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <string>

class Jugador {
private:
    int velocidad;
    int fuerza;
    std::string nombre;

public:
    // Constructor
    Jugador() : velocidad(0), fuerza(0), nombre("sin nombre") {}

    // Constructor con parámetros
    Jugador(int vel, int fuer, const std::string& nom) : velocidad(vel), fuerza(fuer), nombre(nom) {}

    // Setters
    void setVelocidad(int vel) { velocidad = vel; }
    void setFuerza(int fuer) { fuerza = fuer; }
    void setNombre(const std::string& nom) { nombre = nom; }

    // Getters
    int getVelocidad() const { return velocidad; }
    int getFuerza() const { return fuerza; }
    const std::string& getNombre() const { return nombre; }

    // Destructor
    ~Jugador() {
        // Aquí podrías realizar acciones de limpieza si es necesario
    }
};

int main() {
    std::vector<Jugador> jugadores;

    // Insertar 10 jugadores distintos en el vector
    for (int i = 1; i <= 10; ++i) {
        Jugador jugador(i * 7, i * 4, "Jugador: " + std::to_string(i));
        jugadores.push_back(jugador);
    }

    // Mostrar los datos de cada jugador
    for (const auto& jugador : jugadores) {
        std::cout << "Nombre: " << jugador.getNombre() << ", Velocidad: " << jugador.getVelocidad()
                  << ", Fuerza: " << jugador.getFuerza() << std::endl;
    }

    return 0;
}

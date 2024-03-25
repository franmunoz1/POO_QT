#include <iostream>
#include <QString>

// Clase Persona
class Persona {
public:
    Persona(const QString& nombre) : nombre(nombre) {}

    QString getNombre() const {
        return nombre;
    }

private:
    QString nombre;
};

// Clase Poste
class Poste {
public:
    Poste(double altura, double diametro) : altura(altura), diametro(diametro) {}

    double getAltura() const {
        return altura;
    }

    double getDiametro() const {
        return diametro;
    }

private:
    double altura;
    double diametro;
};

// Función genérica para imprimir descripción de cualquier objeto
template<typename T>
void imprimirDescripcion(const T& objeto) {
    std::cout << "Descripción: ";
    imprimirDescripcionEspecifica(objeto);
    std::cout << std::endl;
}

// Sobrecarga de la función para objetos de tipo Persona
void imprimirDescripcionEspecifica(const Persona& persona) {
    std::cout << "Persona con nombre " << persona.getNombre().toStdString();
}

// Sobrecarga de la función para objetos de tipo Poste
void imprimirDescripcionEspecifica(const Poste& poste) {
    std::cout << "Poste con altura de " << poste.getAltura() << " metros y " << poste.getDiametro() << " cm de diámetro";
}

int main() {
    // Crear objetos de prueba
    Persona persona1("Lucrecia");
    Persona persona2("Juan");

    Poste poste1(8.0, 15.0);
    Poste poste2(10.5, 20.0);

    // Probar la función genérica de impresión
    imprimirDescripcion(persona1);
    imprimirDescripcion(persona2);
    imprimirDescripcion(poste1);
    imprimirDescripcion(poste2);

    return 0;
}

#include <iostream>
#include <string>
#include <vector>


class Instrumento {
public:

    virtual void sonar() const = 0;


    virtual void verlo() const {
        std::cout << "Marca: Yamaha" << std::endl;
    }

    virtual ~Instrumento() {}
};


class Guitarra : public Instrumento {
private:
    int cuerdas;

public:

    Guitarra(int _cuerdas = 6) : cuerdas(_cuerdas) {}


    void sonar() const override {
        std::cout << "Guitarra suena..." << std::endl;
    }


    int getCuerdas() const { return cuerdas; }
    void setCuerdas(int _cuerdas) { cuerdas = _cuerdas; }
};


class Bateria : public Instrumento {
private:
    int tambores;

public:

    Bateria(int _tambores = 4) : tambores(_tambores) {}


    void sonar() const override {
        std::cout << "Batería suena..." << std::endl;
    }


    int getTambores() const { return tambores; }
    void setTambores(int _tambores) { tambores = _tambores; }
};


class Electrico {
public:

    Electrico() {}


    ~Electrico() {
        std::cout << "Desenchufado" << std::endl;
    }


    int getVoltaje() const { return 220; }
};

class Teclado : public Instrumento, public Electrico {
private:
    int teclas;

public:

    Teclado(int _teclas = 61) : teclas(_teclas) {}


    void sonar() const override {
        std::cout << "Teclado suena..." << std::endl;
    }


    int getTeclas() const { return teclas; }
    void setTeclas(int _teclas) { teclas = _teclas; }
};

int main() {

    std::vector<Instrumento*> instrumentos;


    instrumentos.push_back(new Guitarra());
    instrumentos.push_back(new Bateria());
    instrumentos.push_back(new Teclado());


    for (const auto& inst : instrumentos) {
        inst->verlo();
        inst->sonar();
        if (auto* guitarra = dynamic_cast<Guitarra*>(inst)) {
            std::cout << "Cuerdas: " << guitarra->getCuerdas() << std::endl;
        } else if (auto* bateria = dynamic_cast<Bateria*>(inst)) {
            std::cout << "Tambores: " << bateria->getTambores() << std::endl;
        } else if (auto* teclado = dynamic_cast<Teclado*>(inst)) {
            std::cout << "Teclas: " << teclado->getTeclas() << std::endl;
            std::cout << "Voltaje: " << teclado->getVoltaje() << " volts" << std::endl;
        }
    }


    for (const auto& inst : instrumentos) {
        delete inst;
    }

    return 0;
}

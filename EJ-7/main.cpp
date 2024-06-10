#include <QCoreApplication>
#include <iostream>
#include <vector>
#include <algorithm> // para std::sort
#include "paleta.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // Crear un vector de objetos Paleta
    std::vector<Paleta> paletas;
    paletas.emplace_back("Marca Nox", "Modelo X", 350.0);
    paletas.emplace_back("Marca Head", "Modelo Y", 325.0);
    paletas.emplace_back("Marca Adidas", "Modelo Z", 340.0);
    paletas.emplace_back("Marca Bullpadel", "Modelo W", 330.0);

    // Imprimir antes de ordenar
    std::cout << "Antes de ordenar:" << std::endl;
    for (const auto &paleta : paletas) {
        std::cout << paleta.getMarca().toStdString() << " "
                  << paleta.getModelo().toStdString() << ": "
                  << paleta.getPeso() << " gramos" << std::endl;
    }

    // Estrategia para ordenar: lambda function comparando por peso
    std::sort(paletas.begin(), paletas.end(), [](const Paleta &a, const Paleta &b) {
        return a.getPeso() < b.getPeso();
    });

    // Imprimir después de ordenar
    std::cout << "Después de ordenar:" << std::endl;
    for (const auto &paleta : paletas) {
        std::cout << paleta.getMarca().toStdString() << " "
                  << paleta.getModelo().toStdString() << ": "
                  << paleta.getPeso() << " gramos" << std::endl;
    }

    return a.exec();
}

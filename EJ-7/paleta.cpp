#include "paleta.h"

Paleta::Paleta(const QString &marca, const QString &modelo, double peso)
    : marca(marca), modelo(modelo), peso(peso) {}

QString Paleta::getMarca() const {
    return marca;
}

QString Paleta::getModelo() const {
    return modelo;
}

double Paleta::getPeso() const {
    return peso;
}

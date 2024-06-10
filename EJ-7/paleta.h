#ifndef PALETA_H
#define PALETA_H

#include <QString>

class Paleta {
public:
    Paleta(const QString &marca, const QString &modelo, double peso);

    QString getMarca() const;
    QString getModelo() const;
    double getPeso() const;

private:
    QString marca;
    QString modelo;
    double peso;
};

#endif // PALETA_H

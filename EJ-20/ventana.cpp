#include "ventana.h"
#include "boton.h"
#include <QGridLayout>
#include <QPainter>

Ventana::Ventana(QWidget *parent) : QWidget(parent)
{
    // Configurar el diseño de la ventana
    QGridLayout *layout = new QGridLayout(this);

    // Crear los botones con el texto y color correspondientes
    Boton *boton1 = new Boton("Mi dentista", Boton::Rojo, this);
    Boton *boton2 = new Boton("Visitas", Boton::Morado, this);
    Boton *boton3 = new Boton("Técnicas de higiene", Boton::Violeta, this);
    Boton *boton4 = new Boton("Mi boca", Boton::Azul, this);
    Boton *boton5 = new Boton("Hora de cepillarse", Boton::Verde, this);

    // Añadir los botones al diseño de la ventana
    layout->addWidget(boton1, 0, 0);
    layout->addWidget(boton2, 1, 0);
    layout->addWidget(boton3, 2, 0);
    layout->addWidget(boton4, 3, 0);
    layout->addWidget(boton5, 4, 0);

    setLayout(layout);

    // Conectar las señales de clic de los botones a slots (aquí, por simplicidad, se conecta a lambdas vacíos)
    connect(boton1, &Boton::signal_clic, this, [](){ /* Acción para el botón 1 */ });
    connect(boton2, &Boton::signal_clic, this, [](){ /* Acción para el botón 2 */ });
    connect(boton3, &Boton::signal_clic, this, [](){ /* Acción para el botón 3 */ });
    connect(boton4, &Boton::signal_clic, this, [](){ /* Acción para el botón 4 */ });
    connect(boton5, &Boton::signal_clic, this, [](){ /* Acción para el botón 5 */ });
}

Ventana::~Ventana()
{
    // Destructor
}

void Ventana::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    // Dibujar un fondo degradado
    QLinearGradient gradient(0, 0, width(), height());
    gradient.setColorAt(0, QColor(255, 165, 0)); // Naranja
    gradient.setColorAt(1, QColor(0, 0, 255));   // Azul
    painter.fillRect(rect(), gradient);
}

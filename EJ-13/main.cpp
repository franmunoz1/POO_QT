#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>

void updateWindowTitle(int value, QWidget* ventana) {
    ventana->setWindowTitle(QString("Volumen: %1").arg(value));
}

int main(int argc, char** argv) {
    QApplication a(argc, argv);

    QWidget* ventana = new QWidget;  // Es la ventana padre (principal)
    ventana->setWindowTitle("Volumen");
    ventana->resize(300, 50);

    QSpinBox* spinBox = new QSpinBox;
    QSlider* slider = new QSlider(Qt::Horizontal);
    spinBox->setRange(0, 100);
    slider->setRange(0, 100);

    // Conexiones para sincronizar el QSpinBox y el QSlider
    QObject::connect(spinBox, qOverload<int>(&QSpinBox::valueChanged),
                     slider, &QSlider::setValue);
    QObject::connect(slider, &QSlider::valueChanged,
                     spinBox, qOverload<int>(&QSpinBox::setValue));

    // Conexión para actualizar el título de la ventana
    QObject::connect(slider, &QSlider::valueChanged, [&ventana, spinBox](int value) {
        updateWindowTitle(value, ventana);
        spinBox->clearFocus();
    });

    spinBox->setValue(15);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(spinBox);
    layout->addWidget(slider);
    ventana->setLayout(layout);
    ventana->setVisible(true);

    return a.exec();
}

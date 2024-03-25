#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtGui/QPixmap>
#include <QtCore/QTimer>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Crear un objeto QLabel
    QLabel label;

    // Cargar la imagen desde un archivo JPG en el disco duro
    QPixmap imagen("/Users/franciscomunoz/Desktop/definitive-map.png");

    // Escalar la imagen para que se ajuste al tamaño del QLabel sin deformarse
    label.setPixmap(imagen.scaled(label.size(), Qt::KeepAspectRatio));

    // Mostrar el QLabel maximizado
    label.showMaximized();

    // Configurar un temporizador para cerrar la aplicación después de 3 segundos
    QTimer::singleShot(3000, [&](){
        label.close(); // Cerrar el QLabel
        a.quit();      // Cerrar la aplicación
    });

    return a.exec();
}

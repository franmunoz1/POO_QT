#ifndef VENTANA_H
#define VENTANA_H

#include <QWidget>
#include <QImage>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

QT_BEGIN_NAMESPACE
namespace Ui { class Ventana; }
QT_END_NAMESPACE

class Ventana : public QWidget
{
    Q_OBJECT

public:
    Ventana(QWidget *parent = nullptr);
    ~Ventana();

private:
    Ui::Ventana *ui;
    QImage im;
    QNetworkAccessManager *manager;
    int indiceActual;

    QString obtenerUrlDesdeArchivo(int indice);
    void cargarImagenDesdeUrl(const QString &url);

protected:
    void paintEvent( QPaintEvent * );

private slots:
    void slot_descargaFinalizada(QNetworkReply *reply);
    void anterior();
    void siguiente();
};

#endif // VENTANA_H

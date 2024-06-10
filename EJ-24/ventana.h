#ifndef VENTANA_H
#define VENTANA_H

#include <QWidget>
#include <QNetworkAccessManager>

QT_BEGIN_NAMESPACE
namespace Ui { class Ventana; }
QT_END_NAMESPACE

class Ventana : public QWidget
{
    Q_OBJECT

public:
    explicit Ventana(QWidget *parent = nullptr);
    ~Ventana();
    void downloadFile(const QString &urlString);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void replyFinished(QNetworkReply *reply);
    void slot_pbUrl_clicked();
    void slot_selectDirectory_clicked();
    void slot_selectImage_clicked();

private:
    Ui::Ventana *ui;
    QNetworkAccessManager manager;
    QString downloadDirectory;
    QImage image;
};

#endif // VENTANA_H

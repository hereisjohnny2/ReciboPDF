#ifndef RECIBOPDF_H
#define RECIBOPDF_H

#include <QMainWindow>
#include <QMap>
#include <QFile>
#include <QDebug>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include <QTextDocument>
#include <QPrinter>

#include <QDate>
#include <QLocale>

#include "novoinquilinodialog.h"

#include <memory>

#include "cinquilino.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ReciboPDF; }
QT_END_NAMESPACE

class ReciboPDF : public QMainWindow
{
    Q_OBJECT

public:
    ReciboPDF(QWidget *parent = nullptr);
    ~ReciboPDF();

    static QString LerJson(QFile &arquivoJson);

private slots:
    void on_actionCarregarInquilinos_triggered();

    void on_boxInquilinos_currentIndexChanged(const QString &nome);

    void on_buttonGerar_clicked();

    void on_actionCriarInquilino_triggered();

private:
    Ui::ReciboPDF *ui;
    QMap<QString, std::shared_ptr<CInquilino>> inquilinos;
    void CarregarInfoInquilino(std::shared_ptr<CInquilino> inquilino);
};
#endif // RECIBOPDF_H

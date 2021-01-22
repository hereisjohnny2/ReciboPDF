#ifndef RECIBOPDF_H
#define RECIBOPDF_H

#include <QMainWindow>
#include <QMap>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

#include <QObject>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include <QTextDocument>
#include <QPrinter>

#include <QDate>
#include <QLocale>

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

    QString LerJson(QFile &arquivoJson);
    QString nomeArquivoJson = "data/inquilinos.json";

private slots:
    void on_actionCarregarInquilinos_triggered();

    void on_boxInquilinos_currentIndexChanged(const QString &nome);

    void on_buttonGerar_clicked();

    void on_buttonSalvar_clicked();

private:
    Ui::ReciboPDF *ui;
    QMap<QString, std::shared_ptr<CInquilino>> inquilinos;
    
    void CarregarInfoInquilino(std::shared_ptr<CInquilino> inquilino);
    void CarregarInquilinos(QString& nomeArquivo);

    QStringList GetDataAtual();
    void GerarPDFdeJson(QString& html);
};
#endif // RECIBOPDF_H

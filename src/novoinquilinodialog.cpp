#include "novoinquilinodialog.h"
#include "ui_novoinquilinodialog.h"

#include "recibopdf.h"

NovoInquilinoDialog::NovoInquilinoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NovoInquilinoDialog)
{
    ui->setupUi(this);
}

NovoInquilinoDialog::~NovoInquilinoDialog()
{
    delete ui;
}

void NovoInquilinoDialog::on_buttonBox_accepted()
{
    QFile arquivo("data/inquilinos.json");

    QJsonDocument jsonDocumento = QJsonDocument::fromJson(ReciboPDF::LerJson(arquivo).toUtf8());
    QJsonObject jsonObj = jsonDocumento.object();
    QJsonArray inquilinosArray = jsonObj.value("INQUILINOS").toArray();

    QJsonObject inquilino;
    inquilino.insert("NOME CONTRATO", QJsonValue::fromVariant(ui->inputNome->text()));
    inquilino.insert("ENDEREÇO COMPLETO", QJsonValue::fromVariant(ui->inputEndereco->text()));
    inquilino.insert("COMPLEMENTO", QJsonValue::fromVariant(ui->inputComp->text()));
    inquilino.insert("CIDADE", QJsonValue::fromVariant(ui->inputCity->text()));
    inquilino.insert("VALOR", QJsonValue::fromVariant(ui->inputAluguel->text().toDouble()));

    inquilinosArray.push_back(inquilino);
    jsonObj.insert("INQUILINOS", QJsonValue::fromVariant(inquilinosArray));

    QJsonDocument jsonDocumentoSaida;
    jsonDocumentoSaida.setObject(jsonObj);

    arquivo.open(QIODevice::ReadWrite | QIODevice::Text);
    arquivo.write(jsonDocumentoSaida.toJson());

    arquivo.close();
}

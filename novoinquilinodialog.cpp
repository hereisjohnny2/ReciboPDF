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

    QJsonDocument jsonDocumento = QJsonDocument::fromJson(ReciboPDF::LerJson(arquivo, this).toUtf8());
    if (jsonDocumento.isEmpty())
    {
        return;
    }

    QJsonObject jsonObj = jsonDocumento.object();

    QJsonArray inquilinosArray = jsonObj.value("inquilinos").toArray();

    QJsonObject inquilino;
    inquilino.insert("nome", QJsonValue::fromVariant(ui->inputNome->text()));
    inquilino.insert("endereco", QJsonValue::fromVariant(ui->inputEndereco->text()));
    inquilino.insert("valor", QJsonValue::fromVariant(ui->inputAluguel->text().toDouble()));

    inquilinosArray.push_back(inquilino);
    jsonObj.insert("inquilinos", QJsonValue::fromVariant(inquilinosArray));

    // QJsonDocument jsonDocumentoSaida;
    jsonDocumento.setObject(jsonObj);

    arquivo.open(QIODevice::ReadWrite | QIODevice::Text);
    arquivo.write(jsonDocumento.toJson());

    arquivo.close();
}

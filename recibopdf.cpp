#include "recibopdf.h"
#include "ui_recibopdf.h"

ReciboPDF::ReciboPDF(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ReciboPDF)
{
    ui->setupUi(this);
    CarregarInquilinos(nomeArquivoJson);
}

ReciboPDF::~ReciboPDF()
{
    delete ui;
}

QString ReciboPDF::LerJson(QFile &arquivoJson)
{
    if (!arquivoJson.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, tr("Não foi possível abrir o arquivo!"), arquivoJson.errorString());
        return "";
    }
    QString dadosJson = arquivoJson.readAll();
    arquivoJson.close();

    return dadosJson;
}

void ReciboPDF::CarregarInfoInquilino(std::shared_ptr<CInquilino> inquilino)
{
    ui->inputEndereco->setText(inquilino->Endereco());
    ui->inputValor->setText(QString::number(inquilino->ValorAluguel(), 'g', 6));
}

void ReciboPDF::CarregarInquilinos(QString& nomeArquivo)
{
    QFile arquivo(nomeArquivo);

    QJsonDocument jsonDocumento = QJsonDocument::fromJson(LerJson(arquivo).toUtf8());
    if (jsonDocumento.isEmpty())
    {
        return;
    }

    QJsonObject jsonObj = jsonDocumento.object();
    QJsonArray inquilinosArray = jsonObj.value("inquilinos").toArray();

    inquilinos.clear();

    QSignalBlocker blocker(ui->boxInquilinos);
    ui->boxInquilinos->clear();

    for (auto inquilino : inquilinosArray) {
        auto nome = inquilino.toObject().value("nome").toString();
        auto endereco = inquilino.toObject().value("endereco").toString();
        auto valorAluguel = inquilino.toObject().value("valor").toDouble();
        inquilinos[nome] = std::make_shared<CInquilino>(nome, endereco, valorAluguel);

        ui->boxInquilinos->addItem(nome);
    }
    CarregarInfoInquilino(inquilinos[ui->boxInquilinos->currentText()]);
}


void ReciboPDF::on_actionCarregarInquilinos_triggered()
{
    nomeArquivoJson = QFileDialog::getOpenFileName(this, tr("Abrir dados dos inquilinos"));
    CarregarInquilinos(nomeArquivoJson);
}

void ReciboPDF::on_boxInquilinos_currentIndexChanged(const QString &nome)
{
    CarregarInfoInquilino(inquilinos[nome]);
}

void ReciboPDF::on_buttonSalvar_clicked()
{
    QFile arquivo(nomeArquivoJson);

    QJsonDocument jsonDocumento = QJsonDocument::fromJson(LerJson(arquivo).toUtf8());
    if (jsonDocumento.isEmpty())
    {
        return;
    }

    QJsonObject jsonObj = jsonDocumento.object();

    QJsonArray inquilinosArray = jsonObj.value("inquilinos").toArray();

    QJsonObject inquilino;
    inquilino.insert("nome", QJsonValue::fromVariant(ui->boxInquilinos->currentText()));
    inquilino.insert("endereco", QJsonValue::fromVariant(ui->inputEndereco->text()));
    inquilino.insert("valor", QJsonValue::fromVariant(ui->inputValor->text().toDouble()));

    inquilinosArray.push_back(inquilino);
    jsonObj.insert("inquilinos", QJsonValue::fromVariant(inquilinosArray));

    // QJsonDocument jsonDocumentoSaida;
    jsonDocumento.setObject(jsonObj);

    arquivo.open(QIODevice::ReadWrite | QIODevice::Text);
    arquivo.write(jsonDocumento.toJson());

    arquivo.close();

    CarregarInquilinos(nomeArquivoJson);

}

QStringList ReciboPDF::GetDataAtual()
{
    auto data = QDate::currentDate();

    QString dia = QString::number(data.day()),
            mes = data.longMonthName(data.month()),
            ano = QString::number(data.year());
    return { dia, mes, ano };
}

void ReciboPDF::GerarPDFdeJson(QString& html)
{
    QTextDocument documento;
    documento.setHtml(html);

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(ui->boxInquilinos->currentText() + "_recibo.pdf");
    printer.setPageMargins(QMarginsF(15, 15, 15, 15));

    documento.print(&printer);

    QMessageBox::information(this, tr("ReciboPDF"), tr("Documento criado com sucesso!"));
}

void ReciboPDF::on_buttonGerar_clicked()
{
    QString nome = ui->boxInquilinos->currentText(),
            endereco = inquilinos[nome]->Endereco(),
            valor = QString::number(inquilinos[nome]->ValorAluguel()),
            mesRecibo = ui->boxMeses->currentText();

    QStringList data = GetDataAtual();

    QString html =
            "<p align=center>"
                "<img src='assets/imagens/logo.jpg' width='621'>"
            "</p>"
            "<br>"
            "<h2 align=center>RECIBO DE ALUGUEL DE IMÓVEL RESIDENCIAL</h2>"
            "<br>"
            "<p align=justify>"
                "Recebi de "
                "<b>" + nome + "</b>"
                ", a importância de R$"
                "<b>" + valor + "</b>"
                ", em dinheiro, referente ao pagamento de sua mensalidade locatícia do mês de "
                "<b>" + mesRecibo + "</b>"
                ", relativo ao imóvel localizado na "
                "<b>" + endereco + "</b>"
                "."
            "</p>"
            "<div align=right>"
                "Rio das Ostras, "
                + data[0] + " de " + data[1] + " de " + data[2] +
                "<p align=right>"
                    "<img src='assets/imagens/assinatura.png' height='40'>"
                "</p>"
                "Crissima Cardoso Carvalho"
            "</div>"
            "<br>"
            "<br>"
            "<hr>"
            "<br>"
            "<br>"
            "<p align=center>"
                "<img src='assets/imagens/logo.jpg' width='621'>"
            "</p>"
            "<br>"
            "<h2 align=center>RECIBO DE ALUGUEL DE IMÓVEL RESIDENCIAL</h2>"
            "<br>"
            "<p align=justify>"
                "Recebi de "
                "<b>" + nome + "</b>"
                ", a importância de R$"
                "<b>" + valor + "</b>"
                ", em dinheiro, referente ao pagamento de sua mensalidade locatícia do mês de "
                "<b>" + mesRecibo + "</b>"
                ", relativo ao imóvel localizado na "
                "<b>" + endereco + "</b>"
                "."
            "</p>"
            "<div align=right>"
                "Rio das Ostras, "
                + data[0] + " de " + data[1] + " de " + data[2] +
                "<p align=right>"
                    "<img src='assets/imagens/assinatura.png' height='40'>"
                "</p>"
                "Crissima Cardoso Carvalho"
            "</div>"
            ;

    GerarPDFdeJson(html);
}

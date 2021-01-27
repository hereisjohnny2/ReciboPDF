#include "recibopdf.h"
#include "ui_recibopdf.h"

ReciboPDF::ReciboPDF(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ReciboPDF)
{
    ui->setupUi(this);
}

ReciboPDF::~ReciboPDF()
{
    delete ui;
}

QString ReciboPDF::LerJson(QFile &arquivoJson)
{
    arquivoJson.open(QIODevice::ReadOnly | QIODevice::Text);
    QString dadosJson = arquivoJson.readAll();
    arquivoJson.close();

    return dadosJson;
}

void ReciboPDF::CarregarInfoInquilino(std::shared_ptr<CInquilino> inquilino)
{
    ui->inputEndereco->setText(inquilino->Endereco());
    ui->inputValor->setText(QString::number(inquilino->ValorAluguel(), 'g', 6));
}


void ReciboPDF::on_actionCarregarInquilinos_triggered()
{
    QFile arquivo("data/inquilinos.json");

    QJsonDocument jsonDocumento = QJsonDocument::fromJson(ReciboPDF::LerJson(arquivo).toUtf8());
    QJsonObject jsonObj = jsonDocumento.object();
    QJsonArray inquilinosArray = jsonObj.value("INQUILINOS").toArray();

    inquilinos.clear();

    for (auto inquilino : inquilinosArray) {
        auto nome = inquilino.toObject().value("NOME CONTRATO").toString();
        auto endereco = inquilino.toObject().value("ENDEREÇO COMPLETO").toString();
        auto complemento = inquilino.toObject().value("COMPLEMENTO").toString();
        auto cidade = inquilino.toObject().value("CIDADE").toString();
        auto valorAluguel = inquilino.toObject().value("VALOR").toDouble();

        endereco = endereco + " - " + complemento + " - " + cidade;
        inquilinos[nome] = std::make_shared<CInquilino>(nome, endereco, valorAluguel);

        ui->boxInquilinos->addItem(nome);
    }
    CarregarInfoInquilino(inquilinos[ui->boxInquilinos->currentText()]);
}

void ReciboPDF::on_boxInquilinos_currentIndexChanged(const QString &nome)
{
    CarregarInfoInquilino(inquilinos[nome]);
}

void ReciboPDF::on_buttonGerar_clicked()
{
    QString nome = ui->boxInquilinos->currentText();
    QString endereco = inquilinos[nome]->Endereco();
    QString valor = QString::number(inquilinos[nome]->ValorAluguel());
    QString mesRecibo = ui->boxMeses->currentText();

    auto data = QDate::currentDate();

    QString dia = QString::number(data.day()),
            mes = data.longMonthName(data.month()),
            ano = QString::number(data.year());

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
                + dia + " de " + mes + " de " + ano +
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
                + dia + " de " + mes + " de " + ano +
                "<p align=right>"
                    "<img src='assets/imagens/assinatura.png' height='40'>"
                "</p>"
                "Crissima Cardoso Carvalho"
            "</div>"
            ;

    QTextDocument documento;
    documento.setHtml(html);

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(nome + "_recibo.pdf");
    printer.setPageMargins(QMarginsF(15,15,15,15));

    documento.print(&printer);
}

void ReciboPDF::on_actionCriarInquilino_triggered()
{
    auto novoInquilino = new NovoInquilinoDialog;
    novoInquilino->show();
}

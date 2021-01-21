#ifndef NOVOINQUILINODIALOG_H
#define NOVOINQUILINODIALOG_H

#include <QDialog>
#include <QDebug>

#include <QFile>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

namespace Ui {
class NovoInquilinoDialog;
}

class NovoInquilinoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NovoInquilinoDialog(QWidget *parent = nullptr);
    ~NovoInquilinoDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::NovoInquilinoDialog *ui;
};

#endif // NOVOINQUILINODIALOG_H

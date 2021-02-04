#ifndef CINQUILINO_H
#define CINQUILINO_H

#include <QString>


class CInquilino
{

private:
    QString nome;
    QString endereco;
    double valorAluguel {0.0};
    double valorIptu {0.0};

public:
    CInquilino(QString &_nome, QString &_endereco, double &_valorAluguel, double& _valorIptu)
        : nome(_nome), endereco(_endereco), valorAluguel(_valorAluguel), valorIptu(_valorIptu) {}

    QString Nome() {return nome;}
    QString Endereco() {return endereco;}
    double ValorAluguel() {return valorAluguel;}
    double ValorIptu() {return valorIptu;}

};

#endif // CINQUILINO_H

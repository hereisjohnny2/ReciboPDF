#ifndef CINQUILINO_H
#define CINQUILINO_H

#include <QString>


class CInquilino
{

private:
    QString nome;
    QString endereco;
    QString complemento;
    QString cidade;
    double valorAluguel {0.0};
    double valorIptu {0.0};

public:
    CInquilino(QString &_nome, QString &_endereco, QString &_complemento, QString &_cidade, double &_valorAluguel, double& _valorIptu)
        : nome(_nome), endereco(_endereco), complemento(_complemento), cidade(_cidade), valorAluguel(_valorAluguel), valorIptu(_valorIptu) {}

    QString Nome() {return nome;}
    QString Endereco() {return endereco;}
    QString Complemento() {return complemento;}
    QString Cidade() {return cidade;}
    double ValorAluguel() {return valorAluguel;}
    double ValorIptu() {return valorIptu;}

};

#endif // CINQUILINO_H

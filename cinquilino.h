#ifndef CINQUILINO_H
#define CINQUILINO_H

#include <QString>


class CInquilino
{

private:
    QString nome;
    QString endereco;
    double valorAluguel {0.0};

public:
    CInquilino(QString &_nome, QString &_endereco, double &_valorAluguel)
        : nome(_nome), endereco(_endereco), valorAluguel(_valorAluguel) {}

    QString Nome() {return nome;}
    QString Endereco() {return endereco;}
    double ValorAluguel() {return valorAluguel;}

};

#endif // CINQUILINO_H

#include "recibopdf.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ReciboPDF w;
    w.show();
    return a.exec();
}

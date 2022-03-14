#include "casaautomatizada.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CasaAutomatizada w;
    w.show();
    return a.exec();
}

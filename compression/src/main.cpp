#include <QCoreApplication>
#include "Decoder.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Decoder d("01 Le Renard.wav");
    d.start();

    return a.exec();
}

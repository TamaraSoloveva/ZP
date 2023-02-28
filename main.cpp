#include "mainwindow.h"
#include "prg.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Prg *s = new Prg;
    s->show();
    return a.exec();

}

#ifndef PRG_H
#define PRG_H

#include <QWidget>
#include <QDir>
#include <QMessageBox>
#include <QTextStream>
#include "ui_zp.h"

class Prg : public QWidget
{
    Q_OBJECT
public:
    Prg();
private:
    //void funcParseLine();
    Ui::Form *myUi;


private slots:
    void slotGetDays(int index);
    void slotParseStr( QString line );
    void countZPslot();

signals:
    void sendLinesignal(QString line);
};

#endif // PRG_H

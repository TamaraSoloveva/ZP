#include "prg.h"

Prg::Prg()
{
    /*Ui::Form **/myUi = new Ui::Form;
    myUi->setupUi(this);

    QStringList lst;
    lst << "-" << "Январь" << "Февраль" << "Март" << "Апрель" << "Май" << "Июнь"
        << "Июль" << "Август" << "Сентябрь" << "Октябрь" << "Ноябрь" << "Декабрь";
    myUi->comboBox->addItems(lst);
    myUi->comboBox->setCurrentIndex(0);

    connect(myUi->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Prg::slotGetDays);
    connect(this, &Prg::sendLinesignal, this, &Prg::slotParseStr);
    connect(myUi->pushButton, &QPushButton::clicked, this, &Prg::countZPslot);
}

void Prg::countZPslot() {
    if ( !myUi->lineEdit_2->text().isEmpty() && !myUi->lineEdit->text().isEmpty() && !myUi->lineEdit_3->text().isEmpty()) {
        int ttlZP = myUi->lineEdit_2->text().toInt();
        int wrkHoursBefore = myUi->lineEdit_6->text().toInt();
        int wrkHoursAfter = myUi->lineEdit_7->text().toInt();
        int ttlWrkHours = wrkHoursBefore + wrkHoursAfter;
        double zpPerHour = (double)ttlZP / (double)ttlWrkHours;

        myUi->lineEdit_4->setText( QString::number(wrkHoursBefore * zpPerHour  * 0.87 ));
        myUi->lineEdit_5->setText( QString::number(wrkHoursAfter * zpPerHour  * 0.87 ));
    }
}

void Prg::slotParseStr( QString line ) {
    QRegExp rx("(\\d+)");
    QStringList list;
    int pos = 0;
    while ((pos = rx.indexIn(line, pos)) != -1) {
        list << rx.cap(1);
        pos += rx.matchedLength();
    }
    myUi->lineEdit->setText(list.at(0));
    myUi->lineEdit_6->setText(list.at(1));
    myUi->lineEdit_3->setText(list.at(2));
    myUi->lineEdit_7->setText(list.at(3));
}




void Prg::slotGetDays(int index) {
    QString flPath = QDir::currentPath() + "/hours.txt";
    if ( !QFile::exists(flPath)) {
         QMessageBox::warning(this, tr("Внимание"), tr("Файл hours.txt не обнаружен"));
         return;
    }
    QFile fl(flPath);
    int num=0;
    QString line;
    if (fl.open(QIODevice::ReadOnly)) {
        QTextStream stream(&fl);
        while( num < 12) {
            line = stream.readLine();
            line = line.trimmed();
            if (num == (index-1) )
                break;
            num++;
        }
        fl.close();
    }
    emit sendLinesignal(line);
}

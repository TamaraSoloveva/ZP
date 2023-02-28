#include "mainwindow.h"
#include "ui_zp.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Ui::Form *myUi = new Ui::Form;

    myUi->setupUi(this);
}

MainWindow::~MainWindow()
{
}


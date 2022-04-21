#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QDoubleValidator *X_Validator = new QDoubleValidator(0,10000000,4);
    QDoubleValidator *Y_Validator = new QDoubleValidator(-500000,500000,4);
    ui->Coo_X->setValidator(X_Validator);
    ui->Coo_Y->setValidator(Y_Validator);

}

MainWindow::~MainWindow()
{
    delete ui;
}


#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //限定输入
    ui->setupUi(this);
    QDoubleValidator *X_Validator = new QDoubleValidator(0,10000000,4);
    QDoubleValidator *Y_Validator = new QDoubleValidator(-500000,500000,4);
    QDoubleValidator *B_Validator = new QDoubleValidator(-90,90,6);
    QDoubleValidator *L_Validator = new QDoubleValidator(-180,180,6);
    QDoubleValidator *L0_Validator = new QDoubleValidator(-180,180,6);

    ui->Coo_X->setValidator(X_Validator);
    ui->Coo_Y->setValidator(Y_Validator);
    ui->B_line->setValidator(B_Validator);
    ui->L_line->setValidator(L_Validator);
    ui->L0_line->setValidator(L0_Validator);

    //关联信号与槽
    connect(ui->B_d,SIGNAL(valueChanged(int)),this,SLOT(BSpin_ValChange()));
    connect(ui->B_m,SIGNAL(valueChanged(int)),this,SLOT(BSpin_ValChange()));
    connect(ui->B_s,SIGNAL(valueChanged(double)),this,SLOT(BSpin_ValChange()));

    connect(ui->L_d,SIGNAL(valueChanged(int)),this,SLOT(LSpin_ValChange()));
    connect(ui->L_m,SIGNAL(valueChanged(int)),this,SLOT(LSpin_ValChange()));
    connect(ui->L_s,SIGNAL(valueChanged(double)),this,SLOT(LSpin_ValChange()));

    connect(ui->L0_d,SIGNAL(valueChanged(int)),this,SLOT(L0Spin_ValChange()));
    connect(ui->L0_m,SIGNAL(valueChanged(int)),this,SLOT(L0Spin_ValChange()));
    connect(ui->L0_s,SIGNAL(valueChanged(double)),this,SLOT(L0Spin_ValChange()));



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::BSpin_ValChange()
{
    B_d = ui->B_d->value();
    B_m = ui->B_m->value();
    B_s = ui->B_s->value();
    B_ss = B_d*3600+B_m*60+B_s;
    ui->B_line->setText(QString::number(B_ss/3600,'f',6));
}

void MainWindow::LSpin_ValChange()
{
    L_d = ui->L_d->value();
    L_m = ui->L_m->value();
    L_s = ui->L_s->value();
    L_ss = L_d*3600+L_m*60+L_s;
    ui->L_line->setText(QString::number(L_ss/3600,'f',6));
}

void MainWindow::L0Spin_ValChange()
{
    L0_d = ui->L0_d->value();
    L0_m = ui->L0_m->value();
    L0_s = ui->L0_s->value();
    L0_ss = L0_d*3600+L0_m*60+L0_s;
    ui->L0_line->setText(QString::number(L0_ss/3600,'f',6));
}



void MainWindow::on_B_line_editingFinished()
{
    B_ss = ui->B_line->text().toDouble()*3600;
    B_d = B_ss/3600;
    B_m = (B_ss-B_d*3600)/60;
    B_s = B_ss-B_m*60-B_d*3600;
    ui->B_d->setValue(B_d);
    ui->B_m->setValue(B_m);
    ui->B_s->setValue(B_s);
}

void MainWindow::on_L_line_editingFinished()
{
    L_ss = ui->L_line->text().toDouble()*3600;
    L_d = L_ss/3600;
    L_m = (L_ss-L_d*3600)/60;
    L_s = L_ss-L_m*60-L_d*3600;
    ui->L_d->setValue(L_d);
    ui->L_m->setValue(L_m);
    ui->L_s->setValue(L_s);
}

void MainWindow::on_L0_line_editingFinished()
{
    L0_ss = ui->L0_line->text().toDouble()*3600;
    L0_d = L0_ss/3600;
    L0_m = (L0_ss-L0_d*3600)/60;
    L0_s = L0_ss-L0_m*60-L0_d*3600;
    ui->L0_d->setValue(L0_d);
    ui->L0_m->setValue(L0_m);
    ui->L0_s->setValue(L0_s);
}

void MainWindow::on_Btn_Clear_clicked()
{
    ui->B_d->setValue(0);
    ui->B_m->setValue(0);
    ui->B_s->setValue(0);
    ui->B_line->setText("0.000000");


    ui->L_d->setValue(0);
    ui->L_m->setValue(0);
    ui->L_s->setValue(0);
    ui->L_line->setText("0.000000");

    ui->L0_d->setValue(0);
    ui->L0_m->setValue(0);
    ui->L0_s->setValue(0);
    ui->L0_line->setText("0.000000");

    ui->Coo_X->setText("0.0000");
    ui->Coo_Y->setText("0.0000");
}

void MainWindow::on_Btn_PosCal_clicked()//正算
{
    using namespace std;
    //准备变量
    B_d = ui->B_d->value();
    B_m = ui->B_m->value();
    B_s = ui->B_s->value();
    B_ss = B_d*3600+B_m*60+B_s;
    B_r = B_ss / rho2;

    L_d = ui->L_d->value();
    L_m = ui->L_m->value();
    L_s = ui->L_s->value();
    L_ss = L_d*3600+L_m*60+L_s;
    L_r = L_ss / rho2;

    L0_d = ui->L0_d->value();
    L0_m = ui->L0_m->value();
    L0_s = ui->L0_s->value();
    L0_ss = L0_d*3600+L0_m*60+L0_s;

    l=(L_ss-L0_ss)/rho2;
    x = 0,y = 0;

    if(ui->radBtn_T->isChecked()) //克拉索夫斯基椭球
    {
        N = 6399698.902 - (21562.267-(108.973-0.612*pow(cos(B_r),2))*pow(cos(B_r),2))*pow(cos(B_r),2);
        a0 = 32140.404 - (135.3302-(0.7092-0.0040*pow(cos(B_r),2))*pow(cos(B_r),2))*pow(cos(B_r),2);
        a4 = (0.25+0.00252*pow(cos(B_r),2))*pow(cos(B_r),2)-0.04166;
        a6 = (0.166*pow(cos(B_r),2)-0.084)*pow(cos(B_r),2);
        a3 = (0.3333333+0.001123*pow(cos(B_r),2))*pow(cos(B_r),2)-0.1666667;
        a5 = 0.0083-(0.1667-(0.1968+0.0040*pow(cos(B_r),2))*pow(cos(B_r),2))*pow(cos(B_r),2);

        x = 6367558.4969*B_r-(a0-(0.5+(a4+a6*pow(l,2))*pow(l,2))*pow(l,2)*N)*sin(B_r)*cos(B_r);
        y = (1+(a3+a5*pow(l,2))*pow(l,2))*l*N*cos(B_r);
    }
    else if(ui->radBtn_IAG->isChecked()) //1975国际椭球
    {
        N = 6399596.652 - (21565.045-(108.996-0.603*pow(cos(B_r),2))*pow(cos(B_r),2))*pow(cos(B_r),2);
        a0 = 32144.5189 - (135.3646-(0.7034-0.0041*pow(cos(B_r),2))*pow(cos(B_r),2))*pow(cos(B_r),2);
        a4 = (0.25+0.00253*pow(cos(B_r),2))*pow(cos(B_r),2)-0.04167;
        a6 = (0.167*pow(cos(B_r),2)-0.083)*pow(cos(B_r),2);
        a3 = (0.3333333+0.001123*pow(cos(B_r),2))*pow(cos(B_r),2)-0.1666667;
        a5 = 0.00878-(0.1702-0.20382*pow(cos(B_r),2))*pow(cos(B_r),2);

        x = 6367452.1328*B_r-(a0-(0.5+(a4+a6*pow(l,2))*pow(l,2))*pow(l,2)*N)*sin(B_r)*cos(B_r);
        y = (1+(a3+a5*pow(l,2))*pow(l,2))*l*N*cos(B_r);
    }

    ui->Coo_X->setText(QString::number(x,'f',4));
    ui->Coo_Y->setText(QString::number(y,'f',4));

}


void MainWindow::on_Btn_CouCal_clicked() //反算
{
    x = ui->Coo_X->text().toDouble();
    y = ui->Coo_Y->text().toDouble();

    if(ui->radBtn_T->isChecked())
    {
        Beta = x/6367558.4969*rho2;
        Beta_r = x/6367558.4969;
        Bf = Beta+(50221746+(293622+(2350+22*pow(cos(Beta_r),2))*pow(cos(Beta_r),2))*pow(cos(Beta_r),2))*1e-10*sin(Beta_r)*cos(Beta_r)*rho2;
        Bf_r = Bf/rho2;
        Nf = 6399698.902 -(21562.267-(108.973-0.612*pow(cos(Bf_r),2))*pow(cos(Bf_r),2))*pow(cos(Bf_r),2);
        Z = y/(Nf*cos(Bf_r));
        b2 = (0.5+0.003369*pow(cos(Bf_r),2))*sin(Bf_r)*cos(Bf_r);
        b3 = 0.333333-(0.166667-0.001123*pow(cos(Bf_r),2))*pow(cos(Bf_r),2);
        b4 = 0.25+(0.16161+0.00562*pow(cos(Bf_r),2))*pow(cos(Bf_r),2);
        b5 = 0.2-(0.1667-0.0088*pow(cos(Bf_r),2))*pow(cos(Bf_r),2);

        B_ss = Bf-(1-(b4-0.12*pow(Z,2))*pow(Z,2))*pow(Z,2)*b2*rho2;
        l = (1-(b3-b5*pow(Z,2))*pow(Z,2))*Z*rho2;
        L_ss = l+L0_ss;
    }
    else if(ui->radBtn_IAG->isChecked())
    {
        Beta = x/6367452.133*rho2;
        Beta_r =x/6367452.133;
        Bf = Beta+(50228976+(293697+(2383+22*pow(cos(Beta_r),2))*pow(cos(Beta_r),2))*pow(cos(Beta_r),2))*1e-10*sin(Beta_r)*cos(Beta_r)*rho2;
        Bf_r = Bf/rho2;
        Nf = 6399596.652 -(21565.047-(109.003-0.612*pow(cos(Bf_r),2))*pow(cos(Bf_r),2))*pow(cos(Bf_r),2);
        Z = y/(Nf*cos(Bf_r));
        b2 = (0.5+0.00336975*pow(cos(Bf_r),2))*sin(Bf_r)*cos(Bf_r);
        b3 = 0.333333-(0.1666667-0.001123*pow(cos(Bf_r),2))*pow(cos(Bf_r),2);
        b4 = 0.25+(0.161612+0.005617*pow(cos(Bf_r),2))*pow(cos(Bf_r),2);
        b5 = 0.2-(0.16667-0.00878*pow(cos(Bf_r),2))*pow(cos(Bf_r),2);

        B_ss = Bf-(1-(b4-0.147*pow(Z,2))*pow(Z,2))*pow(Z,2)*b2*rho2;
        l = (1-(b3-b5*pow(Z,2))*pow(Z,2))*Z*rho2;
        L_ss = l+L0_ss;
    }

    B_d = B_ss/3600;
    B_m = (B_ss-B_d*3600)/60;
    B_s = B_ss-B_m*60-B_d*3600;
    ui->B_d->setValue(B_d);
    ui->B_m->setValue(B_m);
    ui->B_s->setValue(B_s);

    L_d = L_ss/3600;
    L_m = (L_ss-L_d*3600)/60;
    L_s = L_ss-L_m*60-L_d*3600;
    ui->L_d->setValue(L_d);
    ui->L_m->setValue(L_m);
    ui->L_s->setValue(L_s);
}





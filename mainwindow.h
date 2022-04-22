#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <cmath>
#include <QMainWindow>
#include <QRegularExpression>
#include <QDoubleValidator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Btn_PosCal_clicked();

    void on_Btn_Clear_clicked();

    void on_Btn_CouCal_clicked();

private:
    Ui::MainWindow *ui;
    const double rho2 = 206264.806247;
    int B_d,B_m,L_d,L_m,L0_d,L0_m;
    double B_s,B_ss,B_r,L_s,L_ss,L_r,L0_s,L0_ss;
    double x,y;
    //正算参数
    double l,N,a0,a4,a6,a3,a5;
    //反算参数
    double Bf,Beta,Z,Nf,b2,b3,b4,b5;

};
#endif // MAINWINDOW_H

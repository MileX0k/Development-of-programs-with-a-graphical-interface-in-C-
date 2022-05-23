#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//==============================TASK 1=====================================

void MainWindow::on_buttonResult_clicked()
{
    int a = ui->valueA->text().toInt();
    int b = ui->valueB->text().toInt();
    int c = ui->valueC->text().toInt();
    int discr = b*b - 4*a*c;
    QString error = "Корней нет";


    if (a == 0){
        ui->valueAnswer->setText(error + ", a = 0");
    } else {
        if (discr < 0){
            ui->valueAnswer->setText(error + ", дискриминант отрицательный");
        } else if (discr == 0){
            int val = ((-b)+std::sqrt(discr)) / 2*a;
            ui->valueAnswer->setText("x = " + QString::number(val));
        } else {
            int val = ((-b)+std::sqrt(discr)) / 2*a;
            int val2 = ((-b)-std::sqrt(discr)) / 2*a;
            ui->valueAnswer->setText("x1 = " + QString::number(val) + ";  x2 = " + QString::number(val2));
        }
    }
}

//=========================================================================

//==============================TASK 2=====================================

void MainWindow::on_lessonTwoButtonResult_clicked()
{
    float a = ui->lessonTwoValueA->text().toFloat();
    float b = ui->lessonTwoValueB->text().toFloat();
    float angle = ui->lessonTwoAngle->text().toFloat();
    float c = qCos(angle);
    float PI = 3.1415;

    if (ui->buttonDegrees->isChecked()){
        c = qCos(angle * PI / 180);
    }
    float result = qSqrt(qPow(a,2) + qPow(b,2) - (2*a*b*c));

    ui->lessonTwoValueAnswer->setText("c = " + QString::number(result));
}

//=========================================================================

//==============================TASK 3=====================================

void MainWindow::on_movePushButton_clicked()
{
    QString str1 = ui->firstTextEdit->toPlainText();
    QString str2 = ui->secondTextEdit->toPlainText();
    ui->secondTextEdit->setText(str2 + str1);
    ui->firstTextEdit->clear();
}


void MainWindow::on_replacePushButton_clicked()
{
    QString str2 = ui->secondTextEdit->toPlainText();
    ui->firstTextEdit->setText(str2);
}

// Знаю, что это не совсем то, что надо по заданию, я подумал это интереснее =)
void MainWindow::on_randomPushButton_clicked()
{
    QString str = ui->firstTextEdit->toPlainText();
    int rdm = rand() % 70;

        qDebug() << rdm;

    if (rdm <= 10)
        ui->firstTextEdit->setHtml("<b>" + str + "<b>");
    else if (rdm > 10 && rdm <= 20)
        ui->firstTextEdit->setHtml("<i>" + str + "<i>");
    else if (rdm > 20 && rdm <= 30)
        ui->firstTextEdit->setHtml("<font color='red'>" + str + "</font>");
    else if (rdm > 30 && rdm <= 40)
        ui->firstTextEdit->setHtml("<font face='Times New Roman'>" + str + "</font>");
    else if (rdm > 40 && rdm <= 50)
        ui->firstTextEdit->setHtml("<font size = 20>" + str + "</font>");
    else if (rdm > 50 && rdm <= 60)
        ui->firstTextEdit->setHtml("<sup>" + str + "<sup>");
    else if (rdm > 60 && rdm <= 70)
        ui->firstTextEdit->setHtml("<sub>" + str + "<sub>");
}


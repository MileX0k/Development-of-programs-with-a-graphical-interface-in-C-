#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "task1.h"

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_cmdLinkButtonTask1_clicked()
{
    Task1 *t1 = new Task1();
    t1->show();
}


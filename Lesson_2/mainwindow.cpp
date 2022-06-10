#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{

}


void MainWindow::on_buttonStartTask_2_clicked()
{
    sModel = new QStandardItemModel(this);
    ui->listView->setModel(sModel);

    sModel->appendRow(new QStandardItem(QIcon(":/pref/images/cpp.png"), "C++"));
    sModel->appendRow(new QStandardItem(QIcon(":/pref/images/csharp.png"), "C#"));
    sModel->appendRow(new QStandardItem(QIcon(":/pref/images/python.png"), "Pyton"));
    sModel->appendRow(new QStandardItem(QIcon(":/pref/images/php.png"), "PHP"));
    sModel->appendRow(new QStandardItem(QIcon(":/pref/images/java.png"), "Java"));
    sModel->appendRow(new QStandardItem(QIcon(":/pref/images/javascript.png"), "JavaScript"));

}

void MainWindow::on_buttonAddLanguage_clicked()
{
    QStandardItem *newLanguage = new QStandardItem;
    newLanguage->setIcon(QIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPlay)));
    newLanguage->setText("Новый язык");
    sModel->appendRow(newLanguage);
}


void MainWindow::on_buttonDeleteLanguage_clicked()
{
    QItemSelectionModel *item = ui->listView->selectionModel();
    QModelIndexList indexes = item->selectedIndexes();
    QModelIndex index;

    if (item->hasSelection() == false) {
        qDebug() << "Строка не выделена";
    } else {
    foreach (index, indexes) {
        int row = index.row();
        ui->listView->setRowHidden(row, true);
        }
    }
}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if (arg1){
    ui->listView->setViewMode(QListView::IconMode);
    } else
    ui->listView->setViewMode(QListView::ListMode);
}


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemSelectionModel>
#include <QStandardItemModel>

#include <QListWidgetItem>
#include <QListView>

#include <QMessageBox>



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
   void on_buttonStartTask_2_clicked();

   void on_buttonAddLanguage_clicked();

   void on_buttonDeleteLanguage_clicked();

   void on_checkBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QStandardItemModel *sModel;
};
#endif // MAINWINDOW_H

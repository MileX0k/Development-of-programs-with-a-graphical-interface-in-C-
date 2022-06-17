#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTranslator>
#include <QApplication>
#include <QEvent>
#include <QKeyEvent>

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
    QString filter = ("Текстовый файл(*.txt)");

    bool checkOpenButton = false;

private slots:
    void on_saveButton_clicked();

    void on_openButton_clicked();

    void on_descriptionButton_pressed();

    void on_descriptionButton_released();

    void on_radioButtonOnlyRead_clicked(bool checked);

    void on_comboBoxLanguages_currentIndexChanged(int index);

protected:

    void changeEvent(QEvent * event) override;
    void keyPressEvent(QKeyEvent * event) override;
    void createNewDoc();


private:
    Ui::MainWindow *ui;
    QTranslator *translator;
    void changeTranslator(QString postfix);
    QKeyEvent *keyboard;
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTranslator>
#include <QApplication>
#include <QEvent>
#include <QKeyEvent>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QTextEdit>
#include <QLineEdit>
#include <QDateTime>

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
    void on_descriptionButton_clicked();
    void on_radioButtonOnlyRead_clicked(bool checked);
    void on_comboBoxLanguages_currentIndexChanged(int index);
    void on_radioButtonDarkTheme_clicked();
    void on_radioButtonLightTheme_clicked();
    void on_printButton_clicked();
    void on_newFileButton_clicked();
    void on_leftAligmentButton_clicked();
    void on_centralAligmentButton_clicked();
    void on_rightAligmentButton_clicked();
    void on_widthAligmentButton_clicked();
    void on_fontComboBox_currentFontChanged(const QFont &f);
    void on_sizeFontBox_valueChanged(int arg1);
    void on_plainTextEdit_cursorPositionChanged();

    void on_calendarButton_clicked();

protected:
    void changeEvent(QEvent * event) override;
    void keyPressEvent(QKeyEvent * event) override;
    void createNewDoc();

private:
    Ui::MainWindow *ui;
    QTranslator *translator;
    QKeyEvent *keyboard;
    QTextEdit *description;
    QTextCharFormat frm;

private:
    void changeTranslator(QString postfix);
    bool warningWindow();
    void closeFile();
    void printText();
    void createMenu();
    void setFontToText(QTextCharFormat form);
};
#endif // MAINWINDOW_H

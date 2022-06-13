#ifndef TASK1_H
#define TASK1_H

#include <QMainWindow>
#include <QLabel>
#include <QFileDialog>


namespace Ui { class Task1; }


class Task1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit  Task1 (QWidget *parent = nullptr);
    ~Task1();
    QString filter = ("Текстовый файл(*.txt)");


private slots:
    void on_saveButton_clicked();

    void on_openButton_clicked();

    void on_descriptionButton_pressed();

    void on_descriptionButton_released();

private:
    Ui::Task1 *ui;
};

#endif // TASK1_H

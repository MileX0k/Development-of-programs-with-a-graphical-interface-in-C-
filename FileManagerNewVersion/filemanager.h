#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QMainWindow>

#include <QGridLayout>
#include <QTreeView>
#include <QFileSystemModel>
#include <QDir>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QStatusBar>
#include <QLabel>

#include "Controller.h"


class FileManager : public QMainWindow
{
    Q_OBJECT

public:
    FileManager(QWidget *parent = nullptr);
    ~FileManager();

protected slots:
    void on_doubleClicked(const QModelIndex &index);
    void findFileSlot();
    void changeStatusLabel(QString);
    void printFindFile(QString);

private:
    void createBrowser();

private:
    QGridLayout *gridLay;
    QTreeView *tree;
    QFileSystemModel *model;
    QLineEdit *searchEdit;
    QComboBox *selDrive;
    QLabel *statusLabel;
    Controller *controller;
    QTextEdit *infoText;

};
#endif // FILEMANAGER_H

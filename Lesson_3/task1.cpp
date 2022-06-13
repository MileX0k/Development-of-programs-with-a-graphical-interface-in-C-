#include "task1.h"
#include "ui_task1.h"

Task1::Task1(QWidget *parent)
    :QMainWindow(parent)
    , ui(new Ui::Task1)
{
    ui->setupUi(this);
    //setAttribute(Qt::WA_DeleteOnClose, true);

}

Task1::~Task1() {
    delete ui;
}



void Task1::on_saveButton_clicked()
{
    QString s = QFileDialog::getSaveFileName(this, "Окно сохранения", QDir::current().path(), filter);
    if (s.length() > 0) {
        QString ext = QString(&(s.data()[s.length() - 4]));
        if (ext == ".txt") {
            QFile file(s);
            if (file.open(QFile::WriteOnly | QFile::NewOnly)) {
                QTextStream stream (&file);
                stream << ui->plainTextEdit->toPlainText();
                file.close();
            }
        }
    }
}


void Task1::on_openButton_clicked()
{
    QString s = QFileDialog::getOpenFileName(this, "Окно открытия", QDir::current().path(), filter);
    if(s.length() > 0) {
        int index = s.indexOf(".txt");
        if (index !=-1 && s.length()-4 == index) {
            QFile file(s);
            if (file.open(QFile::ReadOnly | QFile::ExistingOnly)) {
                QTextStream stream(&file);
                ui->plainTextEdit->setPlainText(stream.readAll());
                file.close();
            }
        }
    }
}

QString str;

void Task1::on_descriptionButton_pressed()
{
    str = ui->plainTextEdit->toPlainText();
    QString s = ":/Description.txt";
    QFile file(s);

    if (file.open(QFile::ReadOnly)) {
        QTextStream stream(&file);
        ui->plainTextEdit->appendPlainText(stream.readAll());
        file.close();
    }
}

void Task1::on_descriptionButton_released()
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit->insertPlainText(str);
}

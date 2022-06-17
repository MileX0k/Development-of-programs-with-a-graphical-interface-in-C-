#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    translator = new QTranslator(this);
    qApp->installTranslator(translator);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_saveButton_clicked()
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

void MainWindow::on_radioButtonOnlyRead_clicked(bool checked)
{
    if (checked){
        checkOpenButton = true;
        //ui->plainTextEdit->setReadOnly(checkOpenButton);
    }else {
        checkOpenButton = false;
        ui->plainTextEdit->setReadOnly(checkOpenButton);

    }
}

void MainWindow::on_openButton_clicked()
{
    QString s = QFileDialog::getOpenFileName(this, "Окно открытия", QDir::current().path(), filter);
    if(s.length() > 0) {
        int index = s.indexOf(".txt");
        if (index !=-1 && s.length()-4 == index) {
            QFile file(s);
            if (!checkOpenButton){
                if (file.open(QFile::ReadOnly | QFile::ExistingOnly)) {
                    QTextStream stream(&file);
                    ui->plainTextEdit->setPlainText(stream.readAll());
                    file.close();
                }
            } else {
                if (file.open(QFile::ReadOnly)) {
                    QTextStream stream(&file);
                    ui->plainTextEdit->setPlainText(stream.readAll());
                    ui->plainTextEdit->setReadOnly(checkOpenButton);
                    file.close();
                }

            }
        }
    }
}

QString str;
void MainWindow::on_descriptionButton_pressed()
{
    str = ui->plainTextEdit->toPlainText();
    QString s = "://Description.txt";
    QFile file(s);

    if (file.open(QFile::ReadOnly)) {
        QTextStream stream(&file);
        ui->plainTextEdit->appendPlainText(stream.readAll());
        file.close();
    }
}

void MainWindow::on_descriptionButton_released()
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit->insertPlainText(str);
}

void MainWindow::changeTranslator(QString postfix)
{
    QApplication::removeTranslator(translator);
    translator = new QTranslator(this);
    static_cast<void>(translator->load("QtLanguage_" + postfix));
    QApplication::installTranslator(translator);
}


void MainWindow::on_comboBoxLanguages_currentIndexChanged(int index)
{
    if (index == 0) {
        ui->retranslateUi(this);
     }
    if (index == 1) {
        changeTranslator("en");
    }
}

void MainWindow::createNewDoc()
{
    QMessageBox choise;
    choise.setWindowTitle("Создать новый документ?");
    choise.setText("Все несохраненные данные будут утеряны!");  // Надо сделать перевод на английский
    choise.setStandardButtons(QMessageBox::Yes);
    choise.addButton(QMessageBox::No);
    choise.setDefaultButton(QMessageBox::No);
    if (choise.exec() == QMessageBox::Yes){
        ui->plainTextEdit->clear();
        ui->retranslateUi(this);
        ui->comboBoxLanguages->setCurrentIndex(0);
        ui->radioButtonOnlyRead->setChecked(0);
    } else choise.close();

}


void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        setWindowTitle("Main window");
        ui->descriptionButton->setText("Description");
        ui->saveButton->setText("Save");
        ui->openButton->setText("Open");
        ui->radioButtonOnlyRead->setText("Read-only");
        ui->descriptionButton->setToolTip("Click for a hint");
        ui->comboBoxLanguages->setItemText(0, "Russian");
        ui->comboBoxLanguages->setItemText(1, "English");

    } else QMainWindow::changeEvent(event);

}

void MainWindow::keyPressEvent(QKeyEvent *event){

   if (event->type() == QKeyEvent::KeyPress) {
        if (event->modifiers() == Qt::ControlModifier){
            if (event->key() == Qt::Key_O){
               on_openButton_clicked();
            } else if (event->key() == Qt::Key_S) {
                on_saveButton_clicked();
            } else if (event->key() == Qt::Key_Q)
                MainWindow::close();
            else if (event->key() == Qt::Key_N) {
                 createNewDoc();
                }
        }
    }
}





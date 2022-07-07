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
    QString const s = QFileDialog::getSaveFileName(this, tr("Окно сохранения"), QDir::current().path(), filter);
    if (s.length() > 0) {
        QString ext = QString(&(s.data()[s.length() - 4]));
        if (".txt" == ext) {
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
    QString const s = QFileDialog::getOpenFileName(this, tr("Окно открытия"), QDir::current().path(), filter);
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

void MainWindow::on_descriptionButton_pressed()
{
    textCopiedBeforeHelp = ui->plainTextEdit->toPlainText();
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
    ui->plainTextEdit->insertPlainText(textCopiedBeforeHelp);
}

void MainWindow::changeTranslator(QString postfix)
{
    QApplication::removeTranslator(translator);
    translator = new QTranslator(this);
    static_cast<void>(translator->load("D:/Qt projects/Lesson_5/QtLanguage_" + postfix));
    QApplication::installTranslator(translator);
}

void MainWindow::on_comboBoxLanguages_currentIndexChanged(int index)
{
    if (index == 0) {
        changeTranslator("ru");
    }
    if (index == 1) {
        changeTranslator("en");
    }
}

void MainWindow::createNewDoc()
{
    QMessageBox choise;
    choise.setWindowTitle(tr("Создать новый документ?"));
    choise.setText(tr("Все несохраненные данные будут утеряны!"));
    choise.setStandardButtons(QMessageBox::Yes);
    choise.addButton(QMessageBox::No);
    choise.setDefaultButton(QMessageBox::No);
    if (choise.exec() == QMessageBox::Yes){
        ui->plainTextEdit->clear();        
        ui->comboBoxLanguages->setCurrentIndex(0);
        ui->radioButtonOnlyRead->setChecked(0);
    } else choise.close();
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        setWindowTitle(tr("Главное окно"));
        ui->descriptionButton->setText(tr("Справка"));
        ui->saveButton->setText(tr("Сохранить"));
        ui->openButton->setText(tr("Открыть"));
        ui->radioButtonOnlyRead->setText(tr("Только для чтения"));
        ui->descriptionButton->setToolTip(tr("Нажмите для подсказки"));
        ui->comboBoxLanguages->setItemText(0, tr("Русский"));
        ui->comboBoxLanguages->setItemText(1, tr("Английский"));
        ui->radioButtonLightTheme->setText(tr("Светлая тема"));
        ui->radioButtonDarkTheme->setText(tr("Темная тема"));
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

void MainWindow::on_radioButtonDarkTheme_clicked()
{
    QString darkButton = ("QPushButton { color: rgb(255, 255, 255); border: 1px solid black; }");
    QString darkMainW = ("QMainWindow { color: rgb(255, 255, 255); background-color: grey; border: 1px solid black;  }"
                         "QMainWindow::title { background-color: rgb(49, 49, 49);}");
    QString darkWidget = ("QWidget { color: rgb(255, 255, 255); background-color: rgb(49, 49, 49); }");
    QString darkRadioButton = ("QRadioButton { color: rgb(255, 255, 255);");
    QString darkComboBox = ("QComboBox { color: rgb(255, 255, 255); }");
    QString darkPlainText = ("QPlainTexEdit { color: rgb(255, 255, 255);"
                             "selection-background-color: rgb(104, 104, 104);"
                             "border: 1px solid black;  }");
    qApp->setStyleSheet( darkButton + darkMainW + darkWidget +
                         darkRadioButton + darkComboBox + darkPlainText);
}

void MainWindow::on_radioButtonLightTheme_clicked()
{
    qApp->setStyleSheet("");
}

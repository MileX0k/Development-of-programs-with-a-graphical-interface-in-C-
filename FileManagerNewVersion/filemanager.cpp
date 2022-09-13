#include "filemanager.h"

FileManager::FileManager(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *widget = new QWidget(this);
    setCentralWidget(widget);
    gridLay = new QGridLayout(this);
    widget->setLayout(gridLay);


    createBrowser();


}

FileManager::~FileManager()
{
}



void FileManager::createBrowser()
{
    searchEdit = new QLineEdit(this);
    gridLay->addWidget(searchEdit, 0, 0, 1, 2);
    selDrive = new QComboBox(this);
    gridLay->addWidget(selDrive, 0, 2);

    QPushButton *findButton = new QPushButton(this);
    gridLay->addWidget(findButton, 0, 3, 1, 1);
    findButton->setText(tr("Find"));
    connect(findButton, &QPushButton::clicked, this, &FileManager::findFileSlot);

    if (QSysInfo::productType() == "windows")
    {
        QFileInfoList infolist = QDir::drives();
        int amount = infolist.count();
        for (int i = 0; i < amount; i++)
        {
            selDrive->addItem(infolist.at(i).path());
        }
    }
    else
    {
        QStringList str = {"/", "/home/", "/mount/", "/opt/"};
        int amount = str.count();
        for (int i = 0; i < amount; i++)
        {
            selDrive->addItem(str.at(i));
        }
    }

    infoText = new QTextEdit(this);
    gridLay->addWidget(infoText, 1, 0, 2, 8);

    tree = new QTreeView(this);
    gridLay->addWidget(tree, 2, 0, 8, 8);

    model = new QFileSystemModel(this);
    model->setFilter(QDir::QDir::AllEntries);
    model->setRootPath("");
    tree->setModel(model);

    controller = new Controller(this);
    statusLabel = new QLabel(this);
    QStatusBar *statusBar = this->statusBar();
    statusBar->addWidget(statusLabel);

    connect(controller, &Controller::changFindPath, this, &FileManager::changeStatusLabel);
    connect(controller, &Controller::genPathOfFile, this, &FileManager::printFindFile);
    connect(controller, &Controller::newFind, infoText, &QTextEdit::clear);

    setMinimumSize(700, 600);
    connect(tree, &QTreeView::doubleClicked, this, &FileManager::on_doubleClicked);
    tree->setColumnWidth(0, 350);
}

void FileManager::on_doubleClicked(const QModelIndex &index)
{
    QFileInfo fileInfo = model->fileInfo(index);
    if (fileInfo.fileName() == "..")
    {
        QDir dir = fileInfo.dir();
        dir.cdUp();
        tree->setRootIndex(model->index(dir.absolutePath()));
    }
    else if (fileInfo.fileName() == ".")
    {
        tree->setRootIndex(model->index(""));
    } else if (fileInfo.isDir())
    {
        tree->setRootIndex(index);
    }
}

void FileManager::findFileSlot()
{
    QString linesearch = searchEdit->text();
    if (linesearch.length() == 0) return;
    controller->startFind(selDrive->currentText(), linesearch);
}

void FileManager::changeStatusLabel(QString line)
{
    statusLabel->setText(line);
}

void FileManager::printFindFile(QString str)
{
    infoText->append(str);
}

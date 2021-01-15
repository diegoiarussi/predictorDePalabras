#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tst.h"
#include "dialog.h"
#include <QMessageBox>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    trie = new Tst();
    val = 1;
}


MainWindow::~MainWindow()
{
    delete trie;
    delete ui;
}


void MainWindow::on_actionOpen_triggered()
{
    auto filename = QFileDialog::getOpenFileName(this, tr("Open Image"), QDir::homePath());
    if (filename.isEmpty())
        return;

    trie->uploadFile(val);
    QStringList sl = trie->getListWords();
    ui->listWidget->clear();
    ui->listWidget->addItems(sl);
}


void MainWindow::on_actionSave_triggered()
{ 
    auto filename = QFileDialog::getOpenFileName(this, tr("Open Image"), QDir::homePath());
    if (filename.isEmpty())
        return;

    trie->saveAllWords();
}


void MainWindow::on_PushButton_clicked()
{
    QStringList sl;
    if (ui->comboBox->currentText() == "Insert")
    {
        trie->insert(ui->lineEdit->text(),val);
        sl = trie->getListWords();
        ui->listWidget->clear();
        ui->listWidget->addItems(sl);
    }

    if (ui->comboBox->currentText() == "Remove")
    {
        trie->remove(ui->lineEdit->text());
        sl = trie->getListWords();
        ui->listWidget->clear();
        ui->listWidget->addItems(sl);
    }

    if (ui->comboBox->currentText() == "Prefix")
    {
        Dialog * aux = new Dialog(this);
        aux->setModal(true);
        aux->wordsPrefix(trie->prefix(ui->lineEdit->text()));
        aux->show();
    }

    if (ui->comboBox->currentText() == "Search")
    {
        QMessageBox msgBox;
        QString message;
        bool exist = trie->get(ui->lineEdit->text());
        message.append(exist == true ? "" : "IN").append("VALID WORD");
        msgBox.setText(message);
        msgBox.exec();
    }
}


void MainWindow::on_actionNew_triggered()
{
    delete trie;
    trie = new Tst();
    ui->listWidget->clear();
    ui->lineEdit->clear();
}

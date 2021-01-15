#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>


class Tst;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots: 
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_PushButton_clicked();

    void on_actionNew_triggered();

private:
    Ui::MainWindow *ui;
    Tst * trie;
    int val;
};


#endif // MAINWINDOW_H

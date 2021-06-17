#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "statements.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void closeTab(int);

    void openTabLists(doc_type type);
    void openTabRecords(int ID_List);

    void on_act_allSales_triggered();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H

#ifndef LOAD_SUPPLIER_PRICELIST_H
#define LOAD_SUPPLIER_PRICELIST_H

#include <QDialog>
#include <QThread>
#include <QTextStream>
#include <QFile>

#include <tcpclient.h>

namespace Ui {
class Load_supplier_pricelist;
}

class ReaderAndSender;

class Load_supplier_pricelist : public QDialog
{
    Q_OBJECT

public:
    explicit Load_supplier_pricelist(QWidget *parent = nullptr, TcpClient *client = new TcpClient());
    ~Load_supplier_pricelist();

private slots:
    void on_btn_load_clicked();
    void on_btn_explorer_clicked();

    void updateProcessInfo(int count);
    void handleError();
    void finishWork();

    void on_btn_stop_clicked();

signals:
    void abort();

private:
    Ui::Load_supplier_pricelist *ui;
    TcpClient *client;
    ReaderAndSender *RAS;
    QThread *thread;
    QFile *file;
};

class ReaderAndSender : public QObject
{
    Q_OBJECT
public:
    explicit ReaderAndSender(TcpClient *client = new TcpClient(),
                             QFile *file = nullptr,
                             QString supplier = "Omega");

public slots:
    void doWork();
    void forceQuit();

signals:
    void countChanged(int);
    void sendData(const QString&);
    void errorDetected();
    void finished();

private:
    TcpClient *client;
    QFile *file;
    QString supplier;
    bool abort;
};

#endif // LOAD_SUPPLIER_PRICELIST_H

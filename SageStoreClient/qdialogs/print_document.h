#ifndef PRINT_DOCUMENT_H
#define PRINT_DOCUMENT_H

#include <QDialog>

#include <tcpclient.h>

namespace Ui {
class Print_document;
}

class Print_document : public QDialog
{
    Q_OBJECT

public:
    explicit Print_document(QWidget *parent = nullptr, TcpClient *client = new TcpClient());
    ~Print_document();

private slots:
    void on_btn_print_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::Print_document *ui;
    TcpClient *client;
};

#endif // PRINT_DOCUMENT_H

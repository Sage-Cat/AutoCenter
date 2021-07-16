#ifndef ADDPERSON_H
#define ADDPERSON_H

#include <QDialog>

#include "networkcommunication.h"

namespace Ui {
class AddPerson;
}

class AddPerson : public QDialog
{
    Q_OBJECT

public:
    explicit AddPerson(QWidget *parent = nullptr,
                       NetworkCommunication *networkCommunication = new NetworkCommunication(new TcpClient),
                       Tables table = Tables::customers,
                       QString ID = ""
                );
    ~AddPerson();

private slots:
    void on_btn_add_clicked();

private:
    Ui::AddPerson *ui;
    NetworkCommunication *networkCommunication;
    Tables table;
    QString ID;
};

#endif // ADDPERSON_H

#ifndef PERSONS_H
#define PERSONS_H

#include <QWidget>
#include <QTableWidgetItem>

#include "networkcommunication.h"

namespace Ui {
class Persons;
}

class Persons : public QWidget
{
    Q_OBJECT

public:
    explicit Persons(QWidget *parent = nullptr,
                     NetworkCommunication *networkCommunication = new NetworkCommunication(new TcpClient),
                     Tables table = Tables::customers
              );
    ~Persons();

private slots:
    void on_btn_add_clicked();
    void on_btn_del_clicked();
    void on_btn_refresh_clicked();
    void on_btn_info_clicked();
    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);

    void on_btn_cars_clicked();

public /* methods */:
    //! IF ID NOT 'NULL' THEN REPLACE (EDIT) RECORD
    void openEditDialog(QString ID);

signals:
    void tabInfoRequested(Tables info_view, int ID);

private:
    Ui::Persons *ui;
    NetworkCommunication *networkCommunication;
    Tables table;
};

#endif // PERSONS_H

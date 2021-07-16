#ifndef ADDPRODUCT_H
#define ADDPRODUCT_H

#include <QDialog>

#include "networkcommunication.h"

namespace Ui {
class AddProduct;
}

class AddProduct : public QDialog
{
    Q_OBJECT

public:
    explicit AddProduct(QWidget *parent = nullptr,
                        NetworkCommunication *networkCommunication = new NetworkCommunication(new TcpClient)
            );
    ~AddProduct();

    const QString &getID_Product() const;

private slots:
    void on_btn_add_clicked();

private:
    Ui::AddProduct *ui;
    NetworkCommunication *networkCommunication;

    QString ID_Product;
};

#endif // ADDPRODUCT_H

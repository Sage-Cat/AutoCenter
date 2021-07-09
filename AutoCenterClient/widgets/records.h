#ifndef RECORDS_H
#define RECORDS_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QVector>

#include "networkcommunication.h"

namespace Ui {
class Records;
}

class Records : public QWidget
{
    Q_OBJECT

public:
    explicit Records(QWidget *parent = nullptr,
                     NetworkCommunication *networkCommunication = new NetworkCommunication(new TcpClient),
                     int ID_List = 0
              );
    ~Records();

private slots:
    void on_comboBox_Customer_currentIndexChanged(int index);
    void on_comboBox_Seller_currentIndexChanged(int index);

    void on_btn_refresh_clicked();

    void on_btn_add_clicked();
    void on_btn_del_clicked();
    void on_tableWidget_itemChanged(QTableWidgetItem *item);

    void changeListType(int type_index);
    int getNextNumberforListType(int type_index);
    void changeListNumber(int number);

    void on_btn_print_barcode_clicked();

    void on_btn_print_document_clicked();

private /* methods */:
    void init_graphical_widgets();
    void update_line_sum();

    //! example: row=5, data='Count=3'
    void edit_cell(int row, QString data);

    QString find_ID_ProductType_by_Code(QString code);

    QStringList getAllCustomersNames_and_setIndexToID();
    QStringList getAllSellersNames_and_setIndexToID();

private:
    Ui::Records *ui;
    NetworkCommunication *networkCommunication;
    int ID_List;

    //! test_indexToID[index] = ID
    QVector<int> customers_indexToID, sellers_indexToID;

    bool ignore_combobox_index_changing;
    bool ignore_tableWidget_cells_changing;
};

#endif // RECORDS_H

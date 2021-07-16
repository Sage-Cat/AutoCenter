#ifndef _H
#define _H

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
                     int ID_List = 0,
                     OperationType type = OperationType::sale
              );
    ~Records();

private slots:
    /* COMBOBOXES */
    void on_comboBox_Customer_currentIndexChanged(int index);
    void on_comboBox_Seller_currentIndexChanged(int index);

    /* BUTTONS */
    void on_btn_add_clicked();
    void on_btn_del_clicked();
    void on_btn_refresh_clicked();

    /* ACTION */
    void on_tableWidget_itemChanged(QTableWidgetItem *item);

    /* PRINT */
    void on_btn_print_barcode_clicked();
    void on_btn_print_document_clicked();

    /* CUSTOM */
    void changeListType(int type_index);

private /* methods */:
    /* for comboboxes */
    QStringList getAllCustomersNames_and_setIndexToID();
    QStringList getAllSellersNames_and_setIndexToID();

    /* for initialization and updating */
    void init_graphical_widgets();
    void update_line_sum();
    void changeListNumber(int number);

    /* for itemChanged ACTION */
    void handleChangingForExistingRow(int row, int column, QString data);
    void handleChangingForNonExistingRow(int column, QString data);

    //! example: row=5, data='Count=3'
    void edit_cell(int row, QString data);

    /* supporting */
    QString find_IDProduct_by_Code(QString code);
    int getNextNumberforListType(int type_index);

    //! returns new ID_Product
    QString createNewProduct();

    //! adds to DB new record
    bool addNewRecordToDB(QString ID_Product);

private:
    Ui::Records *ui;
    NetworkCommunication *networkCommunication;
    int ID_List;
    OperationType operationType;

    //! test_indexToID[index] = ID
    QVector<int> customers_indexToID, sellers_indexToID;

    /* supporting */
    bool ignore_combobox_index_changing;
    bool ignore_tableWidget_cells_changing;
};

#endif // _H

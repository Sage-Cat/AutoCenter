#ifndef LISTS_H
#define LISTS_H

#include "basewidget.h"

namespace Ui {
class Lists;
}

class Lists : public BaseWidget
{
    Q_OBJECT

public:
    explicit Lists(BaseWidget *parent = nullptr, OperationType type = OperationType::sale);
    ~Lists();

signals:
    void tabRecordsRequested(int ID_List);

private slots:
    void on_btn_add_clicked();
    void on_btn_del_clicked();
    void on_btn_refresh_clicked();

    void on_radio_all_clicked();
    void on_radio_org_clicked();
    void on_radio_not_org_clicked();

private:
    Ui::Lists *ui;
    OperationType type;
};

#endif // LISTS_H

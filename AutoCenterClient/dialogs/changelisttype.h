#ifndef CHANGELISTTYPE_H
#define CHANGELISTTYPE_H

#include <QDialog>

#include "statements.h"

namespace Ui {
class ChangeListType;
}

class ChangeListType : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeListType(QWidget *parent = nullptr);
    ~ChangeListType();

signals:
    void typeSelected(int type_index);

private slots:
    void on_btn_change_clicked();

private:
    Ui::ChangeListType *ui;
};

#endif // CHANGELISTTYPE_H

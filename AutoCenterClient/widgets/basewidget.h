#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>

#include "networkcommunication.h"
#include "statements.h"

class BaseWidget : public QWidget, public NetworkCommunication
{
    Q_OBJECT
public:
    explicit BaseWidget(QWidget *parent = nullptr);

signals:

};

#endif // BASEWIDGET_H

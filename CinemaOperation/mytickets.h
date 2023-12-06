#ifndef MYTICKETS_H
#define MYTICKETS_H

#include <QWidget>
#include "bookedtickets.h"
namespace Ui {
class mytickets;
}

class mytickets : public QWidget
{
    Q_OBJECT

public:
    explicit mytickets(QWidget *parent = nullptr);
    ~mytickets();
    void loadtik();
    void drawtick();
    bool getTicketsInfo;
private:
    Ui::mytickets *ui;
    BaseCompil *db;
};

#endif // MYTICKETS_H

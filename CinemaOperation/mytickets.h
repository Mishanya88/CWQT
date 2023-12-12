#ifndef MYTICKETS_H
#define MYTICKETS_H

#include <QWidget>
#include <QErrorMessage>
#include "QMessageBox"
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

    bool getTicketsInfo;
signals:
    void on_Right_clicked();
    void on_Left_clicked();
    void currentIndexChanged(int);

private slots:
    void drawtick();

    void on_pbSaveAll_clicked();

private:
    QGraphicsView *Gr;
    Ui::mytickets *ui;
    BaseCompil *db;
    bookedtickets *bilet;
};

#endif // MYTICKETS_H

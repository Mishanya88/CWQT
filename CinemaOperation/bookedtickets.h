#ifndef BOOKEDTICKETS_H
#define BOOKEDTICKETS_H

#include <QObject>
#include <QWidget>

#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>

#include <QVector>

#include <QSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

#include <QFileDialog>
#include <QImageWriter>
#include "basecompil.h"
#include <QMessageBox>
#include <QDebug>

#include <QDateTime>

namespace Ui {
class bookedtickets;
}

class bookedtickets : public QWidget
{
    Q_OBJECT

public:
    bookedtickets(QVector<int> ,QString,QWidget *parent = nullptr);
    explicit bookedtickets(QVector<int> inpBookedIDs,QString NameB,QString filmtime, QWidget *parent = nullptr);
    ~bookedtickets();

    QGraphicsScene *scene;

    QGraphicsView* getview(){return view;}

    QVector<int> bookedIDs;
    QString bookedName;
    QVector<QGraphicsItemGroup*> tickets;


    bool getTicketsInfo();

    void drawTicket();

    int id = 0;

private slots:

    void on_pbLeft_clicked();

    void on_pbRight_clicked();

    void on_pbExit_clicked();

    void on_pbSaveAll_clicked();

private:
    bool full = false;
    QGraphicsView *view;
    QString time;
    BaseCompil* dt;
    Ui::bookedtickets *ui;
};

#endif // BOOKEDTICKETS_H

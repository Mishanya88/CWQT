#ifndef DRAWCINEMA_H
#define DRAWCINEMA_H

#include <QObject>
#include <QWidget>

#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>

#include "seat.h"
#include "seatbooked.h"
#include "basecompil.h"
#include <QPair>
#include <QVector>

#include <QDebug>
#include <QMessageBox>

#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

class drawCinema : public QGraphicsView
{
    Q_OBJECT
public:
    explicit drawCinema(int id_s,QString name, QWidget *parent = nullptr);
    virtual ~drawCinema(){

        for(int i = 0; i < cols; i++)
            for(int j = 0; j < rows; j++)
            {
                seats[i][j]->~seat();
            }

        for(int i = 0; i < seats.size(); i++)
            QVector<seat*>().swap(seats[i]);
        QVector<QVector<seat*>>().swap(seats);
        delete scene;


        qDebug() << "destructor drawCinema called";
    }

    QGraphicsScene      *scene;
    BaseCompil          *db;

    QString Namefilm;
    int id_session;
    int cols = 15;
    int rows = 10;

    const int width = 800;
    const int height = 600;

    int screenSpace = 0;

    int cellWidth = 50;
    int cellHeight = 50;

    void drawScene();
    bool getRoomInfo();
    bool getBookedInfo();

    QVector<QPair<int, int>> chosen;
    QVector<QVector<seat*>> seats;

signals:
    void itemClickedSignal(int i, int j);
public slots:
    void itemClicked(int i, int j);

};

#endif // DRAWCINEMA_H

#ifndef BOOKING_H
#define BOOKING_H

#include <QWidget>
#include "drawcinema.h"
#include "basecompil.h"
#include <QVector>
#include <QPair>
#include "bookedtickets.h"
#include <QSqlDatabase>
#include <QSql>
#include <QSqlError>
#include <QSqlRecord>

#include <QDateTime>

namespace Ui {
class booking;
}

class booking : public QWidget
{
    Q_OBJECT

public:
    explicit booking(int id_s,QString name , QString time,QWidget *parent = nullptr);
    ~booking();
    drawCinema    *scene;
    BaseCompil    *db;
    QString timefilm;
    QString NameFilm;
    int id_session;
    QVector<QPair<int, int>> bookedSeats;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void itemClicked(int i, int j);

private:
    Ui::booking *ui;
    signals:
    void closeSignal();
};

#endif // BOOKING_H

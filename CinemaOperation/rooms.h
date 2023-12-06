#ifndef ROOMS_H
#define ROOMS_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include<basecompil.h>
#include <QMessageBox>
#include <QDebug>

#include <QVector>

namespace Ui {
class rooms;
}

class rooms : public QWidget
{
    Q_OBJECT

public:
    explicit rooms(QWidget *parent = nullptr);
    ~rooms();

    QVector<QVector<QTableWidgetItem*>> items;

    void initTable();

    bool getRooms();
    QString numbers();
    bool createConnection();

private slots:

    void on_pbInsert_clicked();

    void on_pbDelete_clicked();

    void on_pbExit_clicked();

    void on_pbChoose_clicked();

public:
    signals:
    void signalDeleted();
    void signalInsertR();

private:
    Ui::rooms *ui;
    QString NumberRooms;
    BaseCompil *m_db;
};

#endif // ROOMS_H

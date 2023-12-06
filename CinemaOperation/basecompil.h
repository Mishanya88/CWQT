#ifndef BASECOMPIL_H
#define BASECOMPIL_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QDir>
#include<QDateTime>
#include "QMessageBox"
class BaseCompil
{
public: 
    static BaseCompil *getInstance();
    BaseCompil();
    ~BaseCompil();
    void addToDatabase(QSqlDatabase mydb);
    bool isOpen() const;
    void open();
    void insertUser(QString,QString);
    void insertRooms(QString cols,QString rows);
    void insertMovie(QString movieName,int movieLength,int timeSlot,QDateTime dt,QByteArray moviePhoto,int roomid);
    void insertSession(QString movieName, int roomid,int idsession);
    void insertPT(QVector<QPair<QString, QString>> mas, QString name);
    void deletFull(QString str , QString );
    void delsession(int , QString);
    QString findPrice(QString,QString);
    QVector<int> findId(QString);
private:
    static BaseCompil *instance;
    QSqlDatabase db;
};

#endif // BASECOMPIL_H

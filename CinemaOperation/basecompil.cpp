#include "basecompil.h"


BaseCompil *BaseCompil::instance = new BaseCompil();
BaseCompil *BaseCompil::getInstance()
{
    return instance;
}


BaseCompil::BaseCompil()
{
    /*db = QSqlDatabase::addDatabase("QSQLITE");;
    db.setDatabaseName(path);
    // code below to test run the database connection
    if (!db.open()) {
        qDebug()<<"setup stage: failed to connect to database";
    } else {
        qDebug() <<"Successfully connect to database";
    }*/

}
BaseCompil::~BaseCompil()
{
    if (db.isOpen())
    {
        db.close();
    }

}
void BaseCompil::open()
{
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::database("qt_sql_default_connection");
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("database.db");
    }
    if (db.isOpen()) {
        return;
    }
    if (!db.open()) {
        qDebug() << __FILE__ << __LINE__ << "Error: Failed to connect database." << db.lastError();
    } else {
        qDebug() << __FILE__ << __LINE__ << "Succeed to connect database." ;
    }

    QSqlQuery query(db);
    //  user
    QString createSql = "CREATE TABLE IF NOT EXISTS user ("
                "u_id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                "username TEXT,"
                "password TEXT,"
                "accessLevel INTEGER"
              ");";
    query.prepare(createSql);
    if(!query.exec()) {
        qDebug() << __FILE__ << __LINE__ << "Error: Fail to create table." << query.lastError();
    } else {
        qDebug() << __FILE__ << __LINE__ << "Table created!";
    }
    query.clear();
    // movie
    createSql = "CREATE TABLE IF NOT EXISTS MOVIES ("
                    "moveid INTEGER NOT NULL PRIMARY KEY,"
                    "name TEXT,"
                    "length INTEGER,"
                    "timeSlot INTEGER,"
                    "u_time TEXT,"
                    "img BLOB NOT NULL,"
                    "roomid INTEGER"
                  ");";
        query.prepare(createSql);
        if(!query.exec()) {
            qDebug() << __FILE__ << __LINE__ << "Error: Fail to create table." << query.lastError();
        } else {
            qDebug() << __FILE__ << __LINE__ << "Table created!";
        }
        query.clear();
        //rooms
        createSql = "CREATE TABLE IF NOT EXISTS ROOMS ("
                        "ID_ROOM INTEGER NOT NULL PRIMARY KEY,"
                        "COLS INTEGER,"
                        "ROWS INTEGER,"
                        "quantity INTEGER"
                      ");";
            query.prepare(createSql);
            if(!query.exec()) {
                qDebug() << __FILE__ << __LINE__ << "Error: Fail to create table." << query.lastError();
            } else {
                qDebug() << __FILE__ << __LINE__ << "Table created!";
            }
            query.clear();
           //booekd
            createSql = "CREATE TABLE IF NOT EXISTS BOOKED ("
                            "ID_BOOKED INTEGER NOT NULL PRIMARY KEY,"
                            "ID_SESSION INTEGER,"
                            "COL INTEGER,"
                            "ROW INTEGER,"
                            "Name TEXT,"
                            "time TEXT,"
                            "price TEXT"
                          ");";
                query.prepare(createSql);
                if(!query.exec()) {
                    qDebug() << __FILE__ << __LINE__ << "Error: Fail to create table." << query.lastError();
                } else {
                    qDebug() << __FILE__ << __LINE__ << "Table created!";
                }
                query.clear();
             //sesion
             createSql = "CREATE TABLE IF NOT EXISTS SESSIONS ("
                                "name TEXT,"
                                "roomid INTEGER,"
                                "id_sessions INTEGER"
                              ");";
                    query.prepare(createSql);
                    if(!query.exec()) {
                        qDebug() << __FILE__ << __LINE__ << "Error: Fail to create table." << query.lastError();
                    } else {
                        qDebug() << __FILE__ << __LINE__ << "Table created!";
                    }
                    query.clear();
            createSql = "CREATE TABLE IF NOT EXISTS PriceTime ("
                            "ID_PT INTEGER NOT NULL PRIMARY KEY,"
                            "name TEXT,"
                            "time TEXT,"
                            "price TEXT"
                          ");";
                query.prepare(createSql);
                if(!query.exec()) {
                    qDebug() << __FILE__ << __LINE__ << "Error: Fail to create table." << query.lastError();
                } else {
                    qDebug() << __FILE__ << __LINE__ << "Table created!";
                }
                query.clear();

}

bool BaseCompil::isOpen() const
{
    return db.isOpen();
}

void BaseCompil::insertUser(QString name, QString password)
{
    QSqlQuery movieQuery(db);
    movieQuery.prepare("INSERT INTO user (username, password, accessLevel) VALUES (:username, :password, :accessLevel)");
    movieQuery.bindValue(":username", name);
    movieQuery.bindValue(":password", password);
    movieQuery.bindValue(":accessLevel", 0);
    if(!movieQuery.exec()) {
        qDebug() << __FILE__ << __LINE__ << "insert error: " << movieQuery.lastError();
    }
    else {
        qDebug() << __FILE__ << __LINE__ << "insert success!";
    }




}
void BaseCompil::insertRooms(QString cols,QString rows)
{
    QSqlQuery q(db);
    q.prepare("INSERT INTO ROOMS (COLS, ROWS) VALUES (:cols, :rows);");
    q.bindValue(":cols", cols);
    q.bindValue(":rows", rows);

    if(!q.exec()){
        QMessageBox::warning(0, "Ошибка запроса", q.lastError().text());
        return;
    }

}
void BaseCompil::insertMovie(QString movieName,int movieLength,int timeSlot,QDateTime dt,QByteArray moviePhoto,int roomid)
{
    //QSqlQuery q(db);
    QSqlQuery *q = new QSqlQuery(db);
    q->prepare("INSERT INTO MOVIES(name, length, timeSlot, u_time, img, roomid) values (?, ?, ?, ?, ? ,?)");
    q->addBindValue(movieName);
    q->addBindValue(movieLength);
    q->addBindValue(timeSlot);
    q->addBindValue(dt);
    q->addBindValue(moviePhoto);
    q->addBindValue(roomid);
    if(!q->exec())
    {
        QMessageBox::warning(0,"Ошибка запроса",q->lastError().text());
        return;
    }
}
void BaseCompil::insertSession(QString movieName, int roomid , int idsession)
{
    QSqlQuery q(db);
    QString str;

    //q.exec("SELECT EXISTS(SELECT name FROM SESSIONS WHERE name =" + movieName + ")");
    str =("SELECT name, roomid, id_sessions FROM SESSIONS WHERE name = '" + movieName + "' AND roomid = "
              + QString::number(roomid) + " AND id_sessions = " + QString::number(idsession));
//    if(q.exec("SELECT EXISTS(SELECT name, roomid, id_sessions FROM SESSIONS WHERE name ='" + movieName +"' AND roomid ="
//              + QString::number(roomid) + "AND id_sessions = " +QString::number(idsession) +")") == 1)
//           return;
    if (!q.exec(str)) {
        QMessageBox::warning(0, "Ошибка запроса", q.lastError().text());
        return;
    }

    q.next();
    int count = q.value(1).toInt();
    if (count > 0)
        return;
    q.prepare("INSERT INTO SESSIONS (name, roomid,id_sessions) VALUES (:name, :roomid,:id_sessions);");
    q.bindValue(":name", movieName);
    q.bindValue(":roomid", roomid);
    q.bindValue(":id_sessions", idsession);
    if(!q.exec()){
        QMessageBox::warning(0, "Ошибка запроса", q.lastError().text());
        return;
    }

}

void BaseCompil::insertPT(QVector<QPair<QString, QString>> mas , QString name)
{

    QSqlQuery q(db);

db.transaction();
    for(int i = 0; i < mas.size(); i++){

        q.prepare("INSERT INTO PriceTime (name,time,price) "
                  "VALUES (:name, :time, :price);");
        q.bindValue(":name", name);
        q.bindValue(":time", mas[i].first);
        q.bindValue(":price", mas[i].second);

        if (!q.exec()) {
                    qDebug() << "Ошибка при вставке данных:" << q.lastError().text();
                }
    }
    db.commit();
}

void BaseCompil::deletFull(QString strId,QString strName)
{
    QSqlQuery q(db);

    q.prepare("DELETE FROM MOVIES WHERE moveid = :moveid");
    q.bindValue(":moveid", strId);
    q.exec();

    q.prepare("DELETE FROM PriceTime WHERE name = :mname");
    q.bindValue(":mname", strName);
    q.exec();

    q.prepare("DELETE FROM SESSIONS WHERE name = :mname");
    q.bindValue(":mname", strName);
    q.exec();

    q.prepare("DELETE FROM BOOKED WHERE name = :mname");
    q.bindValue(":mname", strName);
    q.exec();

}

void BaseCompil::delsession(int num, QString filmname)
{
    QSqlQuery q(db);
    q.prepare("DELETE FROM BOOKED WHERE Name = :moveid AND ID_SESSION = :id");
    q.bindValue(":moveid", filmname);
    q.bindValue(":id", num);
    q.exec();

}

QString BaseCompil::findPrice(QString nm , QString tm)
{
    QSqlQuery q;

        q.prepare("SELECT PriceTime.price FROM PriceTime "
                  "WHERE name = '" + nm + "'AND time = :time");
        q.bindValue(":time", tm);
        if(!q.exec()){
            QMessageBox::warning(0, "Ошибка запроса ", q.lastError().text());

        }
        QSqlRecord rec = q.record();
        QString price;
        while(q.next()){
            price = (q.value(rec.indexOf("price")).toString());
        }

        return  price;

}

QVector<int> BaseCompil::findId(QString nm)
{
    QVector<int> ids;
    QSqlQuery q;
    q.prepare("SELECT ID_BOOKED FROM BOOKED WHERE name = :nm");
    q.bindValue(":nm",nm);
    if(!q.exec()){
        QMessageBox::warning(0, "Ошибка запроса ", q.lastError().text());

    }
    QSqlRecord rec = q.record();
    QString price;
    while(q.next()){
        ids.push_back(q.value(rec.indexOf("ID_BOOKED")).toInt());
    }
    return ids;
}










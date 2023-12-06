#include "mytickets.h"
#include "ui_mytickets.h"

mytickets::mytickets(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mytickets)
{
    ui->setupUi(this);
    db = BaseCompil::getInstance();
    loadtik();
    drawtick();
}

mytickets::~mytickets()
{
    delete ui;
}


void mytickets::loadtik()
{
    QList<QString> List;
    QSqlQuery q;
    q.prepare("SELECT name FROM MOVIES");
    if(!q.exec()){
        QMessageBox::warning(0, "Ошибка запроса ", q.lastError().text());
        return;
    }
    QSqlRecord rec = q.record();
    QString price;
    while(q.next()){
        List.push_back(q.value(rec.indexOf("name")).toString());
    }
    ui->comboBox->addItems(List);
}
//bool mytickets::getTicketsInfo(){   // SQL запрос и запись данных в tickets

//    if(!tickets.isEmpty()){
//        for(auto& o : tickets)
//            delete o;
//        tickets.clear();
//        tickets.shrink_to_fit();
//    }

//    for(int i = 0; i < bookedIDs.size(); i++){
//        QSqlQuery q;
//        {
//            q.prepare("SELECT PriceTime.price,MOVIES.name, length, u_time, roomid, "
//                      "ROW, COL FROM MOVIES, BOOKED,PriceTime "
//                      "WHERE MOVIES.name = '" + bookedName +
//                      "'AND BOOKED.ID_BOOKED = :id_booked "
//                      "AND PriceTime.time = :time AND PriceTime.name ='" + bookedName + "'");
//            q.bindValue(":id_booked", bookedIDs[i]);
//            q.bindValue(":time", time);
//            if(!q.exec()){
//                QMessageBox::warning(0, "Ошибка запроса ", q.lastError().text());
//                return 0;
//            }

//        }

//        QSqlRecord rec = q.record();

//        tickets.push_back(new QGraphicsItemGroup());

//        while(q.next()){

//            QString data;
//            QFont f;
//            f.setPixelSize(20);
//            f.setFamily("Oswald");

//            tickets[i]->setY(0);
//            tickets[i]->addToGroup(scene->addText("Билет \t\t\t№" + QString::number(bookedIDs[i]), f));

//            tickets[i]->setY(20);
//            QDateTime dt;
//            dt = q.value(rec.indexOf("u_time")).toDateTime();
//            tickets[i]->addToGroup(scene->addText(dt.date().toString() + "\t" +
//                                                  "\tв " + time + "\n", f));

//            tickets[i]->setY(40);
//            data = q.value(rec.indexOf("price")).toString();
//            tickets[i]->addToGroup(scene->addText("Стоимость билета\t" + data + " рублей \n", f));

//            tickets[i]->setY(60);
//            data = q.value(rec.indexOf("length")).toString();
//            tickets[i]->addToGroup(scene->addText("Продолжительность\t" + data + "\n", f));

//            tickets[i]->setY(80);
//            data = QString::number(q.value(rec.indexOf("COL")).toInt() + 1);
//            tickets[i]->addToGroup(scene->addText("Место\t\t\t" + data + "\n", f));

//            tickets[i]->setY(100);
//            data = QString::number(q.value(rec.indexOf("ROW")).toInt() + 1);
//            tickets[i]->addToGroup(scene->addText("Ряд\t\t\t" + data + "\n", f));

//            tickets[i]->setY(120);
//            data = q.value(rec.indexOf("roomid")).toString();
//            tickets[i]->addToGroup(scene->addText("Зал\t\t\t" + data + "\n", f));

//            f.setPixelSize(30);
//            tickets[i]->setY(150);

//            data = q.value(rec.indexOf("name")).toString();
//            tickets[i]->addToGroup(scene->addText("Фильм:  " + data + "\n", f));

//            tickets[i]->setY(190);
//            f.setPixelSize(40);
//            tickets[i]->addToGroup(scene->addText("Кинотеатр М", f));
//        }
//    }

//    qDebug() << "getTickets success";
//    return 1;
//}
void mytickets::drawtick()
{
    QVector<int> ids;
    ids = db->findId(ui->comboBox->currentText());
    bookedtickets *bilet = new bookedtickets(ids,ui->comboBox->currentText());
    QGraphicsView *Gr;
    Gr = bilet->getview();
    ui->gridLayout->addWidget(Gr);
    bilet->getTicketsInfo();
    bilet->drawTicket();




}

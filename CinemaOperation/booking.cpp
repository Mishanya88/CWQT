#include "booking.h"
#include "ui_booking.h"

booking::booking(int id_s,QString name,QString time, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::booking)
{
    db = BaseCompil::getInstance();
    id_session = id_s;
    NameFilm = name;
    timefilm = time;
    ui->setupUi(this);

    scene = new drawCinema(id_session,name, this);
    connect(scene, SIGNAL(itemClickedSignal(int, int)), this, SLOT(itemClicked(int, int)));
    ui->gridLayout->addWidget(scene);
    ui->gridLayout->geometry().setWidth(scene->width);
    ui->gridLayout->geometry().setHeight(scene->height);
    ui->gridLayout->geometry().setCoords(0, 0, 800, 600);
}

void booking::on_pushButton_clicked()
{
    if(!bookedSeats.size())
    {
        QMessageBox::warning(0, "Выберите места", "Выберите места для брони кликнув по ним на графике");
        return;
    }

    QSqlQuery q;

    for(int i = 0; i < bookedSeats.size(); i++){
        q.prepare("INSERT INTO BOOKED (ID_SESSION, ROW, COL , Name,time,price) "
                  "VALUES (:id_session, :row, :col, :name , :time , :price );");
        q.bindValue(":id_session", id_session);
        q.bindValue(":name", NameFilm);
        q.bindValue(":col", bookedSeats[i].first);
        q.bindValue(":row", bookedSeats[i].second);
        q.bindValue(":time", timefilm);
        q.bindValue(":price", db->findPrice(NameFilm,timefilm));
        scene->seats[bookedSeats[i].first][bookedSeats[i].second] = new
                seatBooked(bookedSeats[i].first,
                           bookedSeats[i].second,
                           scene->cellWidth,
                           scene->cellHeight);
        scene->seats[bookedSeats[i].first][bookedSeats[i].second]->
                setX(bookedSeats[i].first * scene->cellWidth);
        scene->seats[bookedSeats[i].first][bookedSeats[i].second]->
                setY((scene->rows - 1 - bookedSeats[i].second) * scene->cellHeight);
        scene->scene->addItem(scene->seats[bookedSeats[i].first][bookedSeats[i].second]);

        if(!q.exec())
        {
            qDebug() << "Query error on INSERT" << q.lastError().text();
            return;
        }
    }

    QVector<int> ids;

    for(int i = 0; i < bookedSeats.size(); i++){
        q.clear();
        q.prepare("SELECT ID_BOOKED FROM BOOKED WHERE "
                  "ROW = :ROW AND COL = :COL AND ID_SESSION = :ID_SESSION AND Name = :Name ;");
        q.bindValue(":ROW", bookedSeats[i].second);
        q.bindValue(":COL", bookedSeats[i].first);
        q.bindValue(":ID_SESSION", id_session);
        q.bindValue(":Name", NameFilm);

        qDebug() << "Pair " << bookedSeats[i].second << ", " << bookedSeats[i].first;

        if(!q.exec()){
            qDebug() << "Query error on select id_booked" << q.lastError().text();
            return;
        }

        QSqlRecord rec = q.record();

        while(q.next()){
            ids.push_back(q.value(rec.indexOf("ID_BOOKED")).toInt());
        }
    }

    qDebug() << "ids: ";
    for(int i = 0; i < ids.size(); i++){
        qDebug() << ids[i] << " ";
    }

    bookedSeats.clear();
    bookedSeats.shrink_to_fit();

    scene->scene->update();

    ui->teBooked->setText("Места забронированы");

    bookedtickets *btck = new bookedtickets(ids, NameFilm,timefilm , nullptr);
    btck->show();
}

void booking::on_pushButton_2_clicked()
{
    this->close();
    emit closeSignal();
}

void booking::itemClicked(int i, int j){

    bool idkwtd = 1;

    for(int a = 0; a < bookedSeats.size(); a++){
        if(bookedSeats[a].first == i && bookedSeats[a].second == j)
        {
            qDebug() << "Already present " << i << " " << j;
            bookedSeats.erase(bookedSeats.begin() + a);
            bookedSeats.shrink_to_fit();
            idkwtd = 0;
            break;
        }
    }

    if(idkwtd){
        QPair<int, int> buff(i, j);
        bookedSeats.push_back(buff);
    }

    ui->teBooked->clear();
    ui->teBooked->append("Выбранные места: ");
    for(int a = 0; a < bookedSeats.size(); a++){
        ui->teBooked->append("Ряд " +
                             QString::number(bookedSeats[a].second + 1) +
                             " Место " +
                             QString::number(bookedSeats[a].first + 1));
    }

}

booking::~booking()
{
    scene->~drawCinema();
    delete scene;
    delete ui;
}

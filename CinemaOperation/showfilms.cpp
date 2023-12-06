#include "showfilms.h"
#include "ui_showfilms.h"
#include "mainwindow.h"

#define timeticked 1000
ShowFilms::ShowFilms(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowFilms)
{
    ui->setupUi(this);
    m_db = BaseCompil::getInstance();
    ui->dateEdit->setDate(QDate::currentDate());
    mytimer.start(1000);
    mytimer2.start(timeticked);
    QObject::connect(&mytimer, SIGNAL( timeout() ),
                          this,  SLOT(timecheked()));

    QObject::connect(&mytimer2, SIGNAL( timeout() ),
                          this,  SLOT(checkedButtonTime()));

    //updateFilms();

}

ShowFilms::~ShowFilms()
{
    delete ui;
}

QPixmap ShowFilms::toPixmap(const QByteArray &buffer){
    QPixmap result;
    QDataStream bRead( buffer );
    bRead >> result;

    return result;
}

QString ShowFilms::toHourMinute(int minute)
{
    int hours = minute / 60;
    int minutes = minute % 60;
    return QString::number(hours) + " HR " + QString::number(minutes) + " MIN";
}

void ShowFilms::setUser()
{
    QVector<int> ids;
    QSqlQuery q;
    q.prepare("SELECT id_sessions FROM SESSIONS");
    if(!q.exec()){
        QMessageBox::warning(0, "Ошибка запроса ", q.lastError().text());
        return ;
    }
    QSqlRecord rec = q.record();
        while(q.next()){
            ids.push_back(q.value(rec.indexOf("id_sessions")).toInt());
        }
    bookedtickets *btck = new bookedtickets(ids, "namefilm","-1");
    btck->show();

}

void ShowFilms::checkTime(QString film)
{
    arr.clear();
    QSqlQuery q;
    q.prepare("SELECT time, price FROM PriceTime WHERE name = :nameFilm ;");
    q.bindValue(":nameFilm", film);
    if (!q.exec()) {
        QMessageBox::warning(0, "Ошибка запроса ", q.lastError().text());
        return;
    }
    while (q.next()) {

        QString timeValue = q.value(0).toString();
        QString priceValue = q.value(1).toString();
        arr.push_back(QPair<QString, QString>(timeValue, priceValue));
    }
    if (arr.isEmpty()) {
        qDebug() << "Записей для фильма:" << film << "не найдено";
        // Обработайте случай, если записи не найдены.
    }



}

void ShowFilms::onAddWidgets(int movieID, QString name, int length, int timeSlot, QPixmap img ,int roomid)
{
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->frame->layout());
    QGroupBox* groupBox = new QGroupBox(ui->frame);
    QHBoxLayout* hOfGroupBox = new QHBoxLayout;
    checkTime(name);

    QLabel* picture = new QLabel();
    picture->setFixedWidth(469);
    picture->setFixedHeight(200);
    int w = picture->width();
    int h = picture->height();
    picture->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));

    QVBoxLayout* movieDetails = new QVBoxLayout;
    movieDetails->addStretch();

    QVBoxLayout* nameAndLength = new QVBoxLayout;
    QLabel* movieName = new QLabel(name);
    movieName->setFont(QFont("Arial", 14, QFont::Bold));
    QLabel* movieLength = new QLabel(toHourMinute(length));
    movieLength->setFont(QFont("Arial", 8));
    nameAndLength->addWidget(movieName);
    nameAndLength->addWidget(movieLength);
    nameAndLength->addStretch();

    QHBoxLayout* buttonsOfTime = new QHBoxLayout;

    for (int i = 0; i < timeSlot; i++) {
        QVBoxLayout* buttonLayout = new QVBoxLayout;

        QPushButton* button = new QPushButton(this);
        QLabel* priceLabel = new QLabel();

        if (arr[i].first == "10:40" || arr[i].first == "13:00" || arr[i].first == "15:40" || arr[i].first == "19:00" || arr[i].first == "21:00")
        {
            button->setText(arr[i].first);
            button->setProperty("myName", name);
            button->setProperty("myId", i + 1);
            m_db->insertSession(name, roomid, i + 1);
            priceLabel->setText(arr[i].second);
            connect(button, &QPushButton::clicked, this, &ShowFilms::implementButton);
        }

        button->setMinimumSize(85, 23);
        button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        buttonLayout->addWidget(button);



        priceLabel->setAlignment(Qt::AlignCenter);
        buttonLayout->addWidget(priceLabel);

        buttonsOfTime->addLayout(buttonLayout);
    }

    buttonsOfTime->addStretch();
    movieDetails->addLayout(nameAndLength);
    movieDetails->addLayout(buttonsOfTime);
    hOfGroupBox->addWidget(picture);
    hOfGroupBox->addLayout(movieDetails);
    groupBox->setLayout(hOfGroupBox);

    layout->insertWidget(layout->count() - 1, groupBox);

    mButtonToLayoutMap.insert(groupBox, hOfGroupBox);



}
void ShowFilms::implementButton()
{

    //qDebug()<<namfilms;
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    QString namfilms = buttonSender->property("myName").toString();
    int idfilms = buttonSender->property("myId").toInt();
    qDebug()<<buttonSender->property("myId").toString();
    if (buttonSender->text() == "10:40"){
         b = new booking(idfilms,namfilms,"10:40");
    } else if (buttonSender->text() == "13:00"){
        b = new booking(idfilms,namfilms,"13:00");
    } else if (buttonSender->text() == "15:40"){
        b = new booking(idfilms,namfilms,"15:40");
    } else if (buttonSender->text() == "19:00"){
        b = new booking(idfilms,namfilms,"19:00");
    } else if (buttonSender->text() == "21:00"){
        b = new booking(idfilms,namfilms,"21:00");
    }

    b->show();
    //hide();

}

void ShowFilms::updateFilms()
{
    QSqlQuery query;
    query.exec("SELECT * FROM movies");
    int i = 0;
    while (query.next()) {
        //int movieID = query.value(0).toInt();
        QString movieName = query.value(1).toString();
        int length = query.value(2).toInt();
        int timeSlot = query.value(3).toInt();
        QDateTime dt = query.value(4).toDateTime();
        //qDebug()<<dt.date();
        QPixmap moviePhoto = toPixmap(query.value(5).toByteArray());
        int roomid = query.value(6).toInt();
        //qDebug()<<dt.date() <<ui->dateEdit->date();
        if(dt.date() == ui->dateEdit->date() && dt.date() >= QDate::currentDate())
            onAddWidgets(i, movieName, length, timeSlot, moviePhoto,roomid);
        i++;
    }



}

void ShowFilms::on_dateEdit_dateChanged(const QDate &date)
{
    QList<QWidget*> widgets = findChildren<QWidget*>();
    foreach(QWidget *widget, widgets) {
        QGroupBox *groupBox = qobject_cast<QGroupBox*>(widget);

        if (groupBox) {
            groupBox->deleteLater();
        }
    }
    updateFilms();
}

void ShowFilms::timecheked()
{
    QTime time_obj;
    ui->timeEdit->setTime(time_obj.currentTime());
}

void ShowFilms::checkedButtonTime()
{
    QTime time_obj;
    QString timeString = time_obj.currentTime().toString("hh:mm");
    QList<QWidget*> widgets = findChildren<QWidget*>();
    foreach(QWidget *widget, widgets) {
        QPushButton *button = qobject_cast<QPushButton*>(widget);
        if(button){
            if (timeString >= button->text())
            {
//               button->setEnabled(false);
//               m_db->delsession(button->property("myId").toInt(),button->property("myName").toString());

            }
            if(button->objectName() == "pushButton_2")
               button->setEnabled(true);
        }

    }

}

void ShowFilms::on_pushButton_2_clicked()
{
    hide();
    MainWindow* login = new MainWindow();
    login->show();

}

void ShowFilms::on_pushButton_clicked()
{
    mytickets *tik = new mytickets();
    tik->show();



}

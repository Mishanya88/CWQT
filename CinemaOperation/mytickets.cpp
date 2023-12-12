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
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(drawtick()));
//    connect(this, SIGNAL(on_Right_clicked()), bilet, SLOT(on_pbRight_clicked()));
//    connect(this, SIGNAL(on_Left_clicked()), bilet, SLOT(on_pbLeft_clicked()));

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
//    QVector<int> ids;
//    ids = db->findId(ui->comboBox->currentText());
//    bilet = new bookedtickets(ids,ui->comboBox->currentText());
//    Gr = bilet->getview();
//    ui->gridLayout->addWidget(Gr);
}

void mytickets::drawtick()
{
    QVector<int> ids;
    ids = db->findId(ui->comboBox->currentText());
    qDebug()<<ids;
    if(ids.size() == 0){
        qDebug()<<"yes";
        //ui->gridLayout->removeWidget(Gr);
        bilet->sceneclr();
        bilet->drawTicket();
        QMessageBox::warning(this,"Ошибка","На фильм нет билетов");
        return;
    }
    bilet = new bookedtickets(ids,ui->comboBox->currentText());
    ui->gridLayout->removeWidget(Gr);
    Gr = bilet->getview();
    ui->gridLayout->addWidget(Gr);
    bilet->getTicketsInfo();
    bilet->drawTicket();
    connect(this, SIGNAL(on_Right_clicked()), bilet, SLOT(on_pbRight_clicked()));
    connect(this, SIGNAL(on_Left_clicked()), bilet, SLOT(on_pbLeft_clicked()));
}





void mytickets::on_pbSaveAll_clicked()
{
    bilet->on_pbSaveAll_clicked();
}

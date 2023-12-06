#include "timeandprice.h"
#include "ui_timeandprice.h"
#define N 5
TimeandPrice::TimeandPrice(int numberseans , QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimeandPrice)
{
    m_db = BaseCompil::getInstance();
    ui->setupUi(this);
    idClone = numberseans;
    viewElements(numberseans);
}


TimeandPrice::~TimeandPrice()
{
    delete ui;
}

void TimeandPrice::viewElements(int id)
{

    if(!id)return;
    int startId = N - 1;
    QList<QWidget*> subwidgets = this->findChildren<QWidget*>();
    QListIterator<QWidget*> it(subwidgets); // iterate through the list of widgets
    QWidget *awiget;
    int i = 0;
    //qDebug()<<"name_price" + QString::number(startId);
    it.toBack();
    while (it.hasPrevious()) {
        if(i == N - id)
            break;
        awiget = it.previous();// take each widget in the list
        if (awiget->objectName().contains("Slot_price" + QString::number(startId)))
            awiget->setHidden(1);
        if (awiget->objectName().contains("name_price" + QString::number(startId)))
            awiget->setHidden(1);
        if (awiget->objectName().contains("Slot_time" + QString::number(startId)))
            awiget->setHidden(1);
        if (awiget->objectName().contains("name_time" + QString::number(startId)))
        {
            i++;
            awiget->setHidden(1);
            startId--;
        }

    }

}

void TimeandPrice::requestInsert(QString name)
{
    m_db->insertPT(arrTP,name);
}

void TimeandPrice::on_buttonBox_accepted()
{

    int startId = 0;
    QList<QWidget*> subwidgets = this->findChildren<QWidget*>();
    QListIterator<QWidget*> it(subwidgets); // iterate through the list of widgets
    QWidget *awiget;
    int i = 0;
    i = 0;
    startId = 0;
    it.toFront();
    QString temp;
    QComboBox *comboBox;
    while (it.hasNext()) {
        if(i == idClone)
            break;
        awiget = it.next(); // take each widget in the list
        if (awiget->objectName().contains("Slot_time" + QString::number(startId)))
        {
             comboBox = qobject_cast<QComboBox*>(awiget);
             temp = comboBox->currentText();
        }
        if (awiget->objectName().contains("Slot_price" + QString::number(startId)))
        {
            comboBox = qobject_cast<QComboBox*>(awiget);
            arrTP.push_back(QPair<QString, QString> (temp, comboBox->currentText()));
            i++;
            startId++;
        }

    }

}

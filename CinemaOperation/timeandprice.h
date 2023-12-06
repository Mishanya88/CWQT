#ifndef TIMEANDPRICE_H
#define TIMEANDPRICE_H

#include <QDialog>
#include<QDebug>
#include"basecompil.h"
namespace Ui {
class TimeandPrice;
}

class TimeandPrice : public QDialog
{
    Q_OBJECT

public:
    explicit TimeandPrice(int nb , QWidget *parent = nullptr);
    ~TimeandPrice();
    void viewElements(int id);
    QVector<QPair<QString, QString>> arrTP;
    void requestInsert(QString name);

private slots:
    void on_buttonBox_accepted();

private:
    int idClone;
    BaseCompil *m_db;
    Ui::TimeandPrice *ui;
};

#endif // TIMEANDPRICE_H

#ifndef SHOWFILMS_H
#define SHOWFILMS_H
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHash>
#include <QFile>
#include <QButtonGroup>
#include <QWidget>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>
#include <QDialog>
#include <QTimer>
#include <QGroupBox>
#include "basecompil.h"
#include "booking.h"
#include "bookedtickets.h"
#include "mytickets.h"

namespace Ui {
class ShowFilms;
}

class ShowFilms : public QWidget
{
    Q_OBJECT

private:
    QHash<QGroupBox*, QHBoxLayout*> mButtonToLayoutMap;

public:
    explicit ShowFilms(QWidget *parent = nullptr);
    ~ShowFilms();
    void updateFilms();
    QPixmap toPixmap(const QByteArray &buffer);
    void onAddWidgets(int movieID, QString name, int length, int timeSlot, QPixmap img,int roomid);
    QString toHourMinute(int minute);
    void setUser();
    void checkTime(QString film);

private slots:
    void implementButton();
    void on_dateEdit_dateChanged(const QDate &date);
    void timecheked();
    void checkedButtonTime();
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    QList<QPair<QString,QString>> arr;
    QTimer mytimer,mytimer2;
    Ui::ShowFilms *ui;
    BaseCompil* m_db;
    booking *b;
};

#endif // SHOWFILMS_H

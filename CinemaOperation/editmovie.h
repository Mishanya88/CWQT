#ifndef EDITMOVIE_H
#define EDITMOVIE_H
#include <QWidget>
#include <rooms.h>
#include <QTime>
#include "mainwindow.h"
#include "timeandprice.h"
namespace Ui {
class EditMovie;
}

class EditMovie : public QWidget
{
    Q_OBJECT

public:
    explicit EditMovie(QWidget *parent = nullptr);
    ~EditMovie();
    QByteArray toByteArray(const QPixmap &data);
    void initTable();
    void updateTable();
    QVector<QVector<QTableWidgetItem*>> items;
private slots:
    void on_buttonRooms_clicked();
    void editingNuRoom();
    void on_btn_choosePhoto_clicked();
    void on_btn_addMovie_clicked();

    void on_btn_removeMovie_clicked();

    void on_pushButton_export_clicked();

    void on_pushButton_import_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    rooms* showEditRooms;
    TimeandPrice* windowPT;
    Ui::EditMovie *ui;
    QPixmap Photo;
    QByteArray moviePhoto;
    BaseCompil *m_db;
    QString path;
    QString roomid;
};

#endif // EDITMOVIE_H

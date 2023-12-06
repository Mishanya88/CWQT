#include "editmovie.h"
#include "ui_editmovie.h"
#include <QDebug>
#include <QFileDialog>
#define N 7
EditMovie::EditMovie(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditMovie)
{
    ui->setupUi(this);
    showEditRooms = new rooms();
    QTime t;
    t.setHMS(10, 40, 0);
    m_db = BaseCompil::getInstance();
    ui->dateTimeEdit->setDate(QDate::currentDate());
    initTable();
    updateTable();
    //ui->dateTimeEdit->setTime(t);
}

EditMovie::~EditMovie()
{
    delete ui;
}
void EditMovie::initTable()
{

    QStringList headersList;
    headersList << "ID" << "Фильм" << "Время" << "Кол-во сеансов" <<"Дата"<<"ID Зала";
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels(headersList);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}
void EditMovie::updateTable()
{
    QSqlQuery q;

    q.prepare("SELECT * FROM MOVIES;");
    if(!q.exec()){
        QMessageBox::warning(0, "Ошибка запроса", q.lastError().text());
        return ;
    }

    ui->tableWidget->clear();
    initTable();

    for(int i = 0; i < items.size(); i++){
        QVector<QTableWidgetItem*>().swap(items[i]);
        items[i].shrink_to_fit();
    }
    QVector<QVector<QTableWidgetItem*>>().swap(items);
    items.clear();
    items.shrink_to_fit();
    int i = 0;

    // Читаем результат запроса

    QSqlRecord rec = q.record();

    while(q.next()){
        items.push_back(QVector<QTableWidgetItem*>());
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);

        for(int j = 0; j < N; j++)
            items[i].push_back(new QTableWidgetItem);

        items[i][0]->setText(q.value(rec.indexOf("moveid")).toString());
        items[i][1]->setText(q.value(rec.indexOf("name")).toString());
        items[i][2]->setText(q.value(rec.indexOf("length")).toString());
        items[i][3]->setText(q.value(rec.indexOf("timeSlot")).toString());
        items[i][4]->setText(q.value(rec.indexOf("u_time")).toString());
        items[i][5]->setText(q.value(rec.indexOf("roomid")).toString());

        for(int j = 0; j < N; j++){
            ui->tableWidget->setItem(i, j, items[i][j]);
        }

        i++;
    }


}

QByteArray EditMovie::toByteArray(const QPixmap &data){
      QByteArray result;
      QDataStream bWrite( &result, QIODevice::WriteOnly );
      bWrite << data;
      return result;
}

void EditMovie::on_buttonRooms_clicked()
{
    showEditRooms->show();
    connect(showEditRooms,SIGNAL(signalInsertR()),this,SLOT(editingNuRoom()));
}
void EditMovie::editingNuRoom()
{
    roomid = showEditRooms->numbers();
    ui->lbl_Poster_3->setText("Зал № " + roomid);
}

void EditMovie::on_btn_choosePhoto_clicked()
{
    QString imageFile = QFileDialog::getOpenFileName(this, tr("Open File"), "C://", "JPEG file (*.JPG);;PNG file (*.PNG);;All files(*.*)");
    path = imageFile;
    //QFileInfo info(imageFile);
    QPixmap image (imageFile);
    Photo = image;
    int w = ui->label_moviePhoto->width();
    int h = ui->label_moviePhoto->height();
    ui->label_moviePhoto->setPixmap(image.scaled(w,h,Qt::KeepAspectRatio));
    ui->label_moviePhoto->show();
    moviePhoto = toByteArray(Photo);

}

void EditMovie::on_btn_addMovie_clicked()
{
    QString movieName;
    int movieLength;
    int timeSlot;
    int roomids;
    try {
        movieName   = ui->lineEdit_movieName->text().trimmed();               //name of movie
        movieLength     = ui->lineEdit_movieLength->text().toInt();     //length, which is minutes of movie
        timeSlot        = ui->comboBox_timeSlot->currentIndex() + 1;    //how many times the movie will be played per day
        roomids          = roomid.toInt();
        if (movieName.size() == 0){
            throw QString("Movie name must be specified");
        }
        if  (movieLength < 0 || ui->lineEdit_movieLength->text().isEmpty()){
            throw QString("Length must be > 0");
        }
        else if (movieLength > 150)
        {
            throw QString("Length < 150");
        }
        if(roomids == 0)
        {
            throw QString("PLS select ROOMS");
        }


    }  catch (QString err) {
        QMessageBox :: critical(this,"Error",err);
        return;
    }  catch (...){
        QMessageBox :: critical(this,"Error","Unhandled exception has occured");
        return;
    }
    QDateTime dt;
    dt.setDate(ui->dateTimeEdit->date());
    windowPT->requestInsert(movieName);
    m_db->insertMovie(movieName,movieLength,timeSlot,dt,moviePhoto,roomids);
    updateTable();

    ui->lineEdit_movieName->clear();
    ui->lineEdit_movieLength->clear();
    ui->comboBox_timeSlot->setCurrentIndex(-1);
    ui->label_moviePhoto->clear();
    ui->lbl_Poster_3->setText("Зал N/A");

}

void EditMovie::on_btn_removeMovie_clicked()
{
    if(ui->tableWidget->selectedItems().isEmpty()){
        QMessageBox::warning(0, "Выберите фильм", "Выберите фильм из таблицы");
        return;
    }

    m_db->deletFull(ui->tableWidget->selectedItems()[0]->text(),ui->tableWidget->selectedItems()[1]->text());

    ui->tableWidget->clear();
    updateTable();
}

void EditMovie::on_pushButton_export_clicked()
{

    int timeSlot = ui->comboBox_timeSlot->currentIndex()  + 1;
    QString t = ui->lineEdit_movieName->text() + "/n" + ui->lineEdit_movieLength->text() + "/n" + QString::number(timeSlot) + "/n" + roomid + "/n" + path;
    QStringList lst = t.split("/n");

    QString str = "";
    str = QFileDialog::getSaveFileName(0, str, "", "*.txt");
    if (!str.isEmpty()) {
        QFile file(str);
        if (file.open(QIODevice::WriteOnly)) {
            int i = 0;
            for (QStringList::iterator it = lst.begin(); it != lst.end(); ++it, ++i) {
                QTextStream(&file) << *it << "\n";
                if (i == 3) {
                    QTextStream(&file) << "*";
                }
            }
            file.close();
        }
    }

}



void EditMovie::on_pushButton_import_clicked()
{
    QString path = QFileDialog::getOpenFileName(0, "Открыть файл", "", "*.txt");
    if (path.isEmpty()) {
        return;
    }

    QFile file(path);
    if (file.open(QIODevice::ReadOnly)) {
        try {
            QTextStream stream(&file);
            QStringList lst = stream.readAll().split("*");
            if (lst.size() != 2)
            {
                throw("Error: incorrect file");
            }
            QStringList lst2 = lst.at(0).split("\n");
            qDebug()<<lst2;

            QString path = lst.at(1);
            path.remove(path.length() - 1, path.length());
            if (lst.size() > 1) {
                QPixmap image (path);
                moviePhoto = toByteArray(image);
                int w = ui->label_moviePhoto->width();
                int h = ui->label_moviePhoto->height();
                ui->label_moviePhoto->setPixmap(image.scaled(w,h,Qt::KeepAspectRatio));

            }
            else {
                ui->label_moviePhoto->clear();
            }

            for (int i = 0; i < lst2.size();i++) {
                 switch (i) {
                    case 0:
                        ui->lineEdit_movieName->setText(lst2.at(i));
                        break;
                    case 1:
                        ui->lineEdit_movieLength->setText(lst2.at(i));
                         break;
                    case 2:
                        ui->comboBox_timeSlot->setCurrentIndex(lst2.at(i).toInt() - 1);
                        break;
                    case 3:
                        roomid = lst2.at(i);
                        ui->lbl_Poster_3->setText("Rooms № " + roomid);
                        break;

                 }

            }
        }
        catch (...) {
            //ui->textEdit->setText("Error: Maybe ur file incorrect, if it's correct u need to call ur sysadmin");
        }
        file.close();
    }



}

void EditMovie::on_pushButton_clicked()
{
    hide();
    MainWindow* login = new MainWindow();
    login->show();
}

void EditMovie::on_pushButton_2_clicked()
{
    windowPT = new TimeandPrice(ui->comboBox_timeSlot->currentIndex() + 1 );
    windowPT->show();

}

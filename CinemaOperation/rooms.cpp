#include "rooms.h"
#include "ui_rooms.h"
#include "QMessageBox"
rooms::rooms(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rooms)
{
    ui->setupUi(this);

    m_db = BaseCompil::getInstance();
    m_db->open();
    initTable();
    getRooms();
}


void rooms::initTable(){
    QStringList headersList;
    headersList << "ID" << "Ряды" << "Колонки" << "Количество мест";
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(headersList);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

bool rooms::getRooms(){
    QSqlQuery q;

    q.prepare("SELECT * FROM ROOMS;");
    if(!q.exec()){
        QMessageBox::warning(0, "Ошибка запроса", q.lastError().text());
        return 0;
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

        for(int j = 0; j < 4; j++)
            items[i].push_back(new QTableWidgetItem);

        items[i][0]->setText(q.value(rec.indexOf("ID_ROOM")).toString());
        items[i][1]->setText(q.value(rec.indexOf("ROWS")).toString());
        items[i][2]->setText(q.value(rec.indexOf("COLS")).toString());
        items[i][3]->setText(QString::number(items[i][1]->text().toInt()
                             * items[i][2]->text().toInt()));

        for(int j = 0; j < 4; j++){
            ui->tableWidget->setItem(i, j, items[i][j]);
        }

        i++;
    }

    return 1;
}

void rooms::on_pbInsert_clicked()
{

    QString cols = ui->leCols->text();
    QString rows = ui->leRows->text();
    if(!(rows.length() * cols.length()))
    {
        QMessageBox::warning(0, "Заполните поля", "Введите данные в поля и нажмите снова");
        return;
    }
    m_db->insertRooms(cols,rows);
    getRooms();
}

void rooms::on_pbDelete_clicked()
{
    if(ui->tableWidget->selectedItems().isEmpty()){
        QMessageBox::warning(0, "Выберите зал", "Выберите зал из таблицы");
        return;
    }

    QSqlQuery q;

    q.prepare("DELETE FROM ROOMS WHERE ID_ROOM = :id_room;");
    q.bindValue(":id_room", ui->tableWidget->selectedItems()[0]->text());

    if(!q.exec()){
        QMessageBox::warning(0, "Ошибка запроса", q.lastError().text());
        return;
    }

    ui->tableWidget->clear();
    getRooms();

    emit signalDeleted();
}

void rooms::on_pbExit_clicked()
{
    this->close();
}

rooms::~rooms()
{
    delete ui;

    for(int i = 0; i < items.size(); i++){
        QVector<QTableWidgetItem*>().swap(items[i]);
        items[i].shrink_to_fit();
    }
    QVector<QVector<QTableWidgetItem*>>().swap(items);
    items.clear();
    items.shrink_to_fit();
}
void rooms::on_pbChoose_clicked()
{
    if(ui->tableWidget->selectedItems().isEmpty()){
        QMessageBox::warning(0, "Выберите зал", "Выберите зал из таблицы");
        return;
    }else {
        NumberRooms = ui->tableWidget->selectedItems()[0]->text();
    }

    emit signalInsertR();
    this->close();

}
QString rooms::numbers()
{
    return NumberRooms;
}



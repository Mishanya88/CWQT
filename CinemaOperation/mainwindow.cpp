#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QUrl>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    textBrowser = new QTextBrowser;
    ui->setupUi(this);
    m_db = BaseCompil::getInstance();
    m_db->open();    
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_login_clicked()
{

    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    QSqlQuery query;
    query.prepare("SELECT * FROM user WHERE username ='" + username + "' and password ='" + password + "'");
    if (query.exec()) {
        int count = 0;
        int accessLevel = -1;
        while (query.next()) {
            count++;
            QSqlRecord accountRecord = query.record();
            accessLevel = accountRecord.value(3).toInt();
        }
        qDebug()<<count;

        if(count != 0){
            if (accessLevel == 0){
                hide();
                EditMovie* showAdmin = new EditMovie();
                showAdmin->show();
            } else {
                hide();
                ShowFilms* showuser = new ShowFilms();
                showuser->show();
            }
        } else {
            QMessageBox::warning(this, "Wrong credentials", "Username or password is incorrect");
        }
    } else {
        qDebug()<< "SQL Query Error: " << query.lastError().text();
    }


    //~BaseCompil db(){};



}

void MainWindow::on_create_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM user WHERE username = :login");
    checkQuery.bindValue(":login", username);

    if (!checkQuery.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << checkQuery.lastError().text();
        return;
    }

    checkQuery.next();
    int count = checkQuery.value(0).toInt();

    if (count > 0) {
        QErrorMessage errorMessage;
        errorMessage.showMessage("Такой пользователь уже есть.");
        errorMessage.exec();
        return;
    }
    if (!username.isEmpty() && !password.isEmpty()) {
        m_db->insertUser(username, password);
    } else {

        QErrorMessage errorMessage;
        errorMessage.showMessage("Имя пользователя и пароль должны быть заполнены.");
        errorMessage.exec();
    }


}

void MainWindow::on_toolButton_clicked()
{

       textBrowser->setSource(QUrl::fromLocalFile(":/html/help.html"));
       textBrowser->setOpenExternalLinks(true);

       textBrowser->show();
       textBrowser->resize(800, 600);

}

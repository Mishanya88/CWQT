#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QErrorMessage>
#include "basecompil.h"
#include "editmovie.h"
#include "QMessageBox"
#include "showfilms.h"
#include <QTextBrowser>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_login_clicked();

    void on_create_clicked();

    void on_toolButton_clicked();

private:
    QTextBrowser *textBrowser;
    Ui::MainWindow *ui;
    BaseCompil *m_db;
};

#endif // MAINWINDOW_H

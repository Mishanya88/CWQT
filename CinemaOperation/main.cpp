#include "mainwindow.h"
#include <QApplication>
#include <basecompil.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BaseCompil db;
    db.open();
    QFile styleSheetFile(":/qss/styles2.css");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    a.setStyleSheet(styleSheet);
    styleSheetFile.close();


    MainWindow w;
    w.show();

    return a.exec();
}

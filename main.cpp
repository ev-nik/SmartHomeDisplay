#include "SmartHomeDisplay.h"
//----------------------------------------------------------------------

#include <QApplication>
#include <QDesktopWidget>
#include <QSqlDatabase>
#include <QtSql>
#include <QDebug>
#include <QMessageBox>
//----------------------------------------------------------------------

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QSqlDatabase dbase = QSqlDatabase::addDatabase("QPSQL");
//    dbase.setHostName("localhost");
//    dbase.setPort(5432);
//    dbase.setUserName("postgres");
//    dbase.setPassword("19871");
//    dbase.setDatabaseName("SmartHomeConfig");

//    if(!dbase.open())
//    {
//        QMessageBox::warning(nullptr,
//                             "Ошибка",
//                             QString("Нет соединения с БД: %1").arg(dbase.lastError().text()),
//                             QMessageBox::Close,
//                             QMessageBox::Close);
//        return 0;
//    }
//    qDebug() << "DB connect";











    SmartHomeDisplay w;
    w.show();
    return a.exec();
}
//----------------------------------------------------------------------

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

    SmartHomeDisplay w;
    w.show();

    return a.exec();
}
//----------------------------------------------------------------------

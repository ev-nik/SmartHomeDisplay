#include "SmartHomeDisplay.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SmartHomeDisplay w;
    w.show();
    return a.exec();
}

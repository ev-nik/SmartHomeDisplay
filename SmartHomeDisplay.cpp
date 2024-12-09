#include "SmartHomeDisplay.h"
#include "ui_SmartHomeDisplay.h"
//------------------------------------------------------------------------------------

#include <QMessageBox>
#include <QApplication>
#include <QtSql>
//------------------------------------------------------------------------------------

SmartHomeDisplay::SmartHomeDisplay(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SmartHomeDisplay)
{
    qApp->installEventFilter(this);

    ui->setupUi(this);

    nextBlockSize = 0;

    socket = new QTcpSocket(this);

    connectToServer();

    connect(socket, &QTcpSocket::stateChanged, this, &SmartHomeDisplay::stateChangeSocket);
    connect(socket, &QTcpSocket::readyRead,    this, &SmartHomeDisplay::readyRead);
}

SmartHomeDisplay::~SmartHomeDisplay()
{
    delete ui;
}
//------------------------------------------------------------------------------------

void SmartHomeDisplay::stateChangeSocket(QAbstractSocket::SocketState socketState)
{
    switch(socketState)
    {
        case QTcpSocket::ConnectedState:
        {
            readyRead();
            break;
        }
        case QTcpSocket::UnconnectedState:
        {
            messageOfUnconectedToServer();
            break;
        }
        default:
        {
            break;
        }
    }
}
//------------------------------------------------------------------------------------

void SmartHomeDisplay::messageOfUnconectedToServer()
{
    QMessageBox::warning(this,
                         "Предупреждение",
                         QString("Подключение к серверу не установлено"),
                         QMessageBox::Close);
}
//------------------------------------------------------------------------------------

void SmartHomeDisplay::connectToServer()
{
    socket->connectToHost("127.0.0.1", 3333);
}
//------------------------------------------------------------------------------------

void SmartHomeDisplay::readyRead()
{
    if(socket->state() != QTcpSocket::ConnectedState)
    {
        connectToServer();
        return;
    }

    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_15);

    if(in.status() == QDataStream::Ok)
    {
        for(;;)
        {
            if(nextBlockSize == 0)
            {
                if(socket->bytesAvailable() < 2)
                {
                    break;
                }

                in >> nextBlockSize;

                if(socket->bytesAvailable() < nextBlockSize)
                {
                    break;
                }

                QString nameSensor;
                QString dateTime;
                QString valSensor;
                in >> nameSensor >> dateTime >> valSensor;

                qDebug() << nameSensor << " " << dateTime << " " << valSensor;
                nextBlockSize = 0;
            }
        }
    }
}
//------------------------------------------------------------------------------------

void SmartHomeDisplay::init(QSqlDatabase* dbase)
{
    this->dbase = dbase;
}
//------------------------------------------------------------------------------------

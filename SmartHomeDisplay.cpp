#include "SmartHomeDisplay.h"
#include "ui_SmartHomeDisplay.h"
//------------------------------------------------------------------------------------

#include <QMessageBox>
#include <QApplication>
//------------------------------------------------------------------------------------

SmartHomeDisplay::SmartHomeDisplay(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SmartHomeDisplay)
{
    qApp->installEventFilter(this);

    ui->setupUi(this);

    isRequestSend = false;
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


void SmartHomeDisplay::connectToServer()
{
    socket->connectToHost("127.0.0.1", 3333);
}
//------------------------------------------------------------------------------------



void SmartHomeDisplay::stateChangeSocket(QAbstractSocket::SocketState socketState)
{
    switch(socketState)
    {
        case QTcpSocket::ConnectedState:
        {
            qDebug() << "Connect to SERVER";
            break;
        }
        case QTcpSocket::UnconnectedState:
        {
            if(isRequestSend)
            {
                messageOfUnconectedToServer();
            }
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


void SmartHomeDisplay::readyRead()
{
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

                QString name;
                QString dateTime;
                QString val;
                in >> name >> dateTime >> val;

                qDebug() << name << " " << dateTime << " " << val;
                nextBlockSize = 0;
                break;
            }
        }
    }
}
//------------------------------------------------------------------------------------


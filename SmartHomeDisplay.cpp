#include "SmartHomeDisplay.h"
#include "ui_SmartHomeDisplay.h"
//------------------------------------------------------------------------------------

#include <QMessageBox>
#include <QApplication>
#include <QtSql>
#include <QHeaderView>
#include <QHBoxLayout>
//------------------------------------------------------------------------------------

SmartHomeDisplay::SmartHomeDisplay(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SmartHomeDisplay)
{
    qApp->installEventFilter(this);

    ui->setupUi(this);

    tWidget = new QTableWidget(this);
    tWidget->setColumnCount(3);
    tWidget->setHorizontalHeaderLabels({"Дата и время", "Наименование датчика", "Значение"});
    tWidget->setRowCount(0);

    QHeaderView* headerView = tWidget->horizontalHeader();
    headerView->setSectionResizeMode(QHeaderView::Stretch);


    QHBoxLayout* hLayout = new QHBoxLayout(this);
    hLayout->addWidget(tWidget);

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
                int dateTime;
                int valSensor;

                in >> nameSensor >> dateTime >> valSensor;

                nextBlockSize = 0;

                insertValue(nameSensor, dateTime, valSensor);
            }
        }
    }
}
//------------------------------------------------------------------------------------

void SmartHomeDisplay::insertValue(QString& nameSensor, int& dateTime, int& valueSensor)
{
    QTableWidgetItem* nameSensorItem  = new QTableWidgetItem();
    QTableWidgetItem* dateTimeItem    = new QTableWidgetItem();
    QTableWidgetItem* valueSensorItem = new QTableWidgetItem();

    QDateTime dateTimeTable = QDateTime::fromSecsSinceEpoch(dateTime);

    nameSensorItem ->setData(Qt::DisplayRole, nameSensor);
    dateTimeItem   ->setData(Qt::DisplayRole, dateTimeTable);
    valueSensorItem->setData(Qt::DisplayRole, valueSensor);

    int row = tWidget->rowCount();
    tWidget->insertRow(row);

    tWidget->setItem(row, 0, nameSensorItem);
    tWidget->setItem(row, 1, dateTimeItem);
    tWidget->setItem(row, 2, valueSensorItem);
}

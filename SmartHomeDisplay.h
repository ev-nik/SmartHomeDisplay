#ifndef SMARTHOMEDISPLAY_H
#define SMARTHOMEDISPLAY_H

#include <QWidget>
#include <QTcpSocket>


struct PropSensor
{
    QString name;
    int typeSensor;
    QString id;
    QString idRoom;

    PropSensor()
    {
        name = "Датчик";
    }
};

QT_BEGIN_NAMESPACE
namespace Ui { class SmartHomeDisplay; }
QT_END_NAMESPACE

class SmartHomeDisplay : public QWidget
{
    Q_OBJECT

public:
    SmartHomeDisplay(QWidget *parent = nullptr);
    ~SmartHomeDisplay();

private:
    Ui::SmartHomeDisplay *ui;

    QTcpSocket* socket;
    QByteArray data;
    quint16 nextBlockSize;

    bool isRequestSend;

private:
    void messageOfUnconectedToServer();

private slots:
    void connectToServer();
    void stateChangeSocket(QAbstractSocket::SocketState socketState);

public slots:
    void readyRead();
};
#endif // SMARTHOMEDISPLAY_H

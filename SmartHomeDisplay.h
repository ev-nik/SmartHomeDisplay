#ifndef SMARTHOMEDISPLAY_H
#define SMARTHOMEDISPLAY_H

#include <QWidget>

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
};
#endif // SMARTHOMEDISPLAY_H

#include "SmartHomeDisplay.h"
#include "ui_SmartHomeDisplay.h"

SmartHomeDisplay::SmartHomeDisplay(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SmartHomeDisplay)
{
    ui->setupUi(this);
}

SmartHomeDisplay::~SmartHomeDisplay()
{
    delete ui;
}


#include "delaytab.h"
#include "ui_delaytab.h"

delayTab::delayTab(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::delayTab)
{
    ui->setupUi(this);
}

delayTab::~delayTab()
{
    delete ui;
}

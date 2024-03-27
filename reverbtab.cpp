#include "reverbtab.h"
#include "ui_reverbtab.h"

reverbTab::reverbTab(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::reverbTab)
{
    ui->setupUi(this);
}

reverbTab::~reverbTab()
{
    delete ui;
}

void reverbTab::on_horizontalSlider_2_valueChanged(int value)
{
    float actualVal = (float)value/2;
    ui->lcdNumber->display(actualVal);
    emit reverbDelChanged(actualVal);
}

void reverbTab::on_horizontalSlider_valueChanged(int value)
{
    float actualVal = (float)value/2;
    ui->lcdNumber_2->display(actualVal);
    emit reverbDecChanged(actualVal);
}

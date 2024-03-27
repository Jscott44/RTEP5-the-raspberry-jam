#include "distortiontab.h"
#include "ui_distortiontab.h"

distortionTab::distortionTab(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::distortionTab)
{
    ui->setupUi(this);
}

distortionTab::~distortionTab()
{
    delete ui;
}

void distortionTab::on_horizontalSlider_valueChanged(int value)
{
    float actualVal = (float)value/2;
    ui->lcdNumber->display(actualVal);
    emit distortionChanged(actualVal);
}

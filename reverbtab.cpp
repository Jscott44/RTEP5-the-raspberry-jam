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

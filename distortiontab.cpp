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

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "reverbtab.h"
#include "distortiontab.h"
#include "delaytab.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Populate QComboBoxQ
    ui->comboBox->addItem("Distortion");
    ui->comboBox->addItem("Reverb");
    ui->comboBox->addItem("Delay");

    //Set up tabs
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_badButton_2_pressed()
{
    ui->badButton_2->setStyleSheet("QPushButton{ background-color: rgb(233, 150, 122); border-color: rgb(233, 150, 122); color: white; border-width: 3px; border-style: solid; border-radius: 20px; margin: 5px}");
}


void MainWindow::on_badButton_2_released()
{
    ui->badButton_2->setStyleSheet("QPushButton{ background-color: rgb(158, 41, 82); border-color: rgb(158, 41, 82); color: white; border-width: 3px; border-style: solid; border-radius: 20px; margin: 5px}");
}


void MainWindow::on_badButton_3_pressed()
{
    ui->badButton_3->setStyleSheet("QPushButton{ background-color: rgb(233, 150, 122); border-color: rgb(233, 150, 122); color: white; border-width: 3px; border-style: solid; border-radius: 20px; margin: 5px}");
}


void MainWindow::on_badButton_3_released()
{
    ui->badButton_3->setStyleSheet("QPushButton{ background-color: rgb(158, 41, 82); border-color: rgb(158, 41, 82); color: white; border-width: 3px; border-style: solid; border-radius: 20px; margin: 5px}");
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if(index == 0)
    {
        ui->tabWidget->insertTab(ui->tabWidget->count(),new distortionTab(),QIcon(QString("")),"Distortion");
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
    }
    else if(index == 1)
    {
        ui->tabWidget->insertTab(ui->tabWidget->count(),new reverbTab(),QIcon(QString("")),"Reverb");
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
    }
    else if(index == 2)
    {
        ui->tabWidget->insertTab(ui->tabWidget->count(),new delayTab(),QIcon(QString("")),"Delay");
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
    }
}


void MainWindow::on_badButton_2_clicked()
{
    ui->tabWidget->removeTab(ui->tabWidget->currentIndex());
}

//NOT FUNCTIONING
void MainWindow::on_badButton_3_clicked()
{
    for(int i = 0; i >= ui->tabWidget->count(); ++i)
    {
        qInfo() << i;
        ui->tabWidget->removeTab(i);
    }
}


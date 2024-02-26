#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_badButton_clicked()
{

}


void MainWindow::on_badButton_pressed()
{
    ui->badButton->setStyleSheet("QPushButton{ background-color: rgb(233, 150, 122); border-color: rgb(233, 150, 122); color: white; border-width: 3px; border-style: solid; border-radius: 20px; margin: 5px}");
}



void MainWindow::on_badButton_released()
{
    ui->badButton->setStyleSheet("QPushButton{ background-color: rgb(158, 41, 82); border-color: rgb(158, 41, 82); color: white; border-width: 3px; border-style: solid; border-radius: 20px; margin: 5px}");
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


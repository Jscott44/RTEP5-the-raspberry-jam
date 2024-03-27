#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "reverbtab.h"
#include "distortiontab.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_2->show();

    //Populate QComboBox
    ui->comboBox->addItem("Distortion");
    ui->comboBox->addItem("Reverb");
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


void MainWindow::on_badButton_2_clicked()
{
    ui->tabWidget->removeTab(ui->tabWidget->currentIndex());

}


void MainWindow::on_badButton_3_clicked()
{
    ui->tabWidget->clear();
}


void MainWindow::on_comboBox_textActivated(const QString &arg1)
{
    if(arg1 == "Distortion")
    {
        distortionTab *newDisTab = new distortionTab;
        newDisTab = new distortionTab(this);
        ui->tabWidget->addTab(newDisTab, tr("Distortion"));
        connect(newDisTab, SIGNAL(distortionChanged(float)),this, SLOT(distortionChangedHandler(float)));

        //ui->tabWidget->insertTab(ui->tabWidget->count(),new distortionTab(),QIcon(QString("")),"Distortion");
        //ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);

    }
    else if(arg1 == "Reverb")
    {
        reverbTab *newRevTab = new reverbTab;
        newRevTab = new reverbTab(this);
        ui->tabWidget->addTab(newRevTab, tr("Reverb"));
        connect(newRevTab, SIGNAL(reverbDelChanged(float)),this, SLOT(reverbDelChangedHandler(float)));
        connect(newRevTab, SIGNAL(reverbDecChanged(float)),this, SLOT(reverbDecChangedHandler(float)));

        //ui->tabWidget->insertTab(ui->tabWidget->count(),new reverbTab(),QIcon(QString("")),"Reverb");
        //ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
    }
}

void MainWindow::on_pushButton_pressed()
{
    ui->pushButton->setStyleSheet("QPushButton{ background-color: rgb(233, 150, 122); border-color: rgb(233, 150, 122); color: white; border-width: 3px; border-style: solid; border-radius: 20px; margin: 5px}");
}


void MainWindow::on_pushButton_released()
{
    ui->pushButton->setStyleSheet("QPushButton{ background-color: rgb(158, 41, 82); border-color: rgb(158, 41, 82); color: white; border-width: 3px; border-style: solid; border-radius: 20px; margin: 5px}");
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::distortionChangedHandler(float value)
{
    qInfo() << value;
}

void MainWindow::reverbDelChangedHandler(float value)
{
    qInfo() << value;
}

void MainWindow::reverbDecChangedHandler(float value)
{
    qInfo() << value;
}

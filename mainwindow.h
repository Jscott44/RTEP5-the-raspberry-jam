#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_badButton_2_pressed();

    void on_badButton_2_released();

    void on_badButton_3_pressed();

    void on_badButton_3_released();

//    void on_comboBox_currentIndexChanged(int index);

    void on_badButton_2_clicked();

    void on_badButton_3_clicked();

    void on_comboBox_textActivated(const QString &arg1);

    void on_pushButton_pressed();

    void on_pushButton_released();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

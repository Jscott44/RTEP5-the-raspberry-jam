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
    void on_badButton_clicked();

    void on_badButton_pressed();

    void on_badButton_released();

    void on_badButton_2_pressed();

    void on_badButton_2_released();

    void on_badButton_3_pressed();

    void on_badButton_3_released();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

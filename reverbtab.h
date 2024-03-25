#ifndef REVERBTAB_H
#define REVERBTAB_H

#include <QWidget>

namespace Ui {
class reverbTab;
}

class reverbTab : public QWidget
{
    Q_OBJECT

public:
    explicit reverbTab(QWidget *parent = nullptr);
    ~reverbTab();

private slots:
    void on_horizontalSlider_2_valueChanged(int value);

    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::reverbTab *ui;
};

#endif // REVERBTAB_H

#ifndef DELAYTAB_H
#define DELAYTAB_H

#include <QWidget>

namespace Ui {
class delayTab;
}

class delayTab : public QWidget
{
    Q_OBJECT

public:
    explicit delayTab(QWidget *parent = nullptr);
    ~delayTab();

private:
    Ui::delayTab *ui;
};

#endif // DELAYTAB_H

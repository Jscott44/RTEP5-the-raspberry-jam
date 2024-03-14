#ifndef DISTORTIONTAB_H
#define DISTORTIONTAB_H

#include <QWidget>

namespace Ui {
class distortionTab;
}

class distortionTab : public QWidget
{
    Q_OBJECT

public:
    explicit distortionTab(QWidget *parent = nullptr);
    ~distortionTab();

private:
    Ui::distortionTab *ui;
};

#endif // DISTORTIONTAB_H

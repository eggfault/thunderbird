#ifndef MENU_H
#define MENU_H

#include <vector>
#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include "lightningFX.h"

using namespace std;

class Menu : public QWidget
{
    Q_OBJECT

    public:
    Menu();
    ~Menu();

    protected:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
    void keyPressEvent(QKeyEvent* event);
    void buySelectedItem();
    void randomLightning();

    private:
    int timerId_;
    int selected_;
    vector<LightningFX*> lightningFX_;
    bool displayInstructions_;
};

#endif // MENU_H

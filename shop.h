#ifndef SHOP_H
#define SHOP_H

#include <QWidget>
#include <QKeyEvent>
#include <QPainter>

class Shop : public QWidget
{
    Q_OBJECT

    public:
    Shop();
    ~Shop();

    protected:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
    void keyPressEvent(QKeyEvent* event);
    void buySelectedItem();

    private:
    int timerId_;
    int costs_[20];
    int selectedShopItem_;
    bool unlocked_[20];
    bool unlocked_bullet25mm_;
    bool unlocked_gatlingGuns_;
    bool unlocked_laserRifle_;
    bool unlocked_laserRed_;
    bool unlocked_laserBlue_;
    bool unlocked_laserYellow_;
};

#endif // SHOP_H

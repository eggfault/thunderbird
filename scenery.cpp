#include "scenery.h"

Scenery::Scenery(int x, int y, int speed, int type, int rotation)
{
    switch(type)
    {
        case 0 : image_.load(":img/island1.png"); break;
        case 1 : image_.load(":img/island2.png"); break;
        case 2 : image_.load(":img/island3.png"); break;
        case 3 : image_.load(":img/island4.png"); break;
        case 4 : image_.load(":img/island5.png"); break;
        case 5 : image_.load(":img/island6.png"); break;
        case 6 : image_.load(":img/island7.png"); break;
        case 7 : image_.load(":img/island8.png"); break;
        case 8 : image_.load(":img/island9.png"); break;
        case 9 : image_.load(":img/island10.png"); break;
        default : image_.load(":img/island1.png"); break;
    }
    QTransform imageRotate; imageRotate.rotate(rotation);
    image_ = image_.transformed(imageRotate);
    rect_ = image_.rect();
    x_ = x;
    y_ = y;
    rect_.translate(x_, y_);
    isDead_ = false;
    xdir_ = 0; ydir_ = 1;        // down
    speed_ = speed;
}

void Scenery::autoMove()
{
    x_ += xdir_*speed_;
    y_ += ydir_*speed_;
    autoUpdateRect();
}

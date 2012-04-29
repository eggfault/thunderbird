#include "credit.h"

Credit::Credit(int x, int y)
{
    image_.load(":img/credit.png");
    rect_ = image_.rect();
    x_ = x;
    y_ = y;
    rect_.translate(x_, y_);
    isDead_ = false;
    xdir_ = 0; ydir_ = 1;        // down
    speed_ = 2;
}

void Credit::autoMove()
{
    x_ += xdir_*speed_;
    y_ += ydir_*speed_;
    autoUpdateRect();
}


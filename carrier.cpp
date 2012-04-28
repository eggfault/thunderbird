#include "carrier.h"

Carrier::Carrier(int x, int y)
{
    health_ = 4420;
    maxHealth_ = health_;
    x_ = x;
    y_ = y;
    speed_ = 1;
    xdir_ = 0;
    ydir_ = 1;
    image_.load(":img/enemy_carrier.png");
    rect_ = image_.rect();
    isDead_ = false;
    healthBarColor_ = qRgb(64, 213, 43);
    healthBarColor_.setAlpha(204);
    healthBarBorderColor_ = qRgb(23, 78, 16);
    reward_ = 2000;
    movesRandomly_ = false;
    projectile_ = 0;
    fireRate_ = 0;
}


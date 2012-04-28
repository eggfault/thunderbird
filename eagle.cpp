#include "eagle.h"

Eagle::Eagle(int x, int y)
{
    health_ = 13300;
    maxHealth_ = health_;
    x_ = x;
    y_ = y;
    speed_ = 6;
    xdir_ = 0;
    ydir_ = 1;
    image_.load(":img/enemy_eagle.png");
    rect_ = image_.rect();
    isDead_ = false;
    healthBarColor_ = qRgb(64, 213, 43);
    healthBarColor_.setAlpha(204);
    healthBarBorderColor_ = qRgb(23, 78, 16);
    reward_ = 2700;
    movesRandomly_ = true;
    projectile_ = 2;
    fireRate_ = 300;
}


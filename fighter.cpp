#include "fighter.h"

Fighter::Fighter(int x, int y)
{
    health_ = 44;
    maxHealth_ = health_;
    x_ = x;
    y_ = y;
    speed_ = 2;
    xdir_ = 0;
    ydir_ = 1;
    image_.load(":img/enemy_fighter.png");
    rect_ = image_.rect();
    isDead_ = false;
    healthBarColor_ = qRgb(64, 213, 43);
    healthBarColor_.setAlpha(204);
    healthBarBorderColor_ = qRgb(23, 78, 16);
    reward_ = 41;
    movesRandomly_ = false;
    projectile_ = 1;
    fireRate_ = 1;
}

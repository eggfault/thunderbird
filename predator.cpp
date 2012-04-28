#include "predator.h"

Predator::Predator(int x, int y)
{
    health_ = 449;
    maxHealth_ = health_;
    x_ = x;
    y_ = y;
    speed_ = 3;
    xdir_ = 0;
    ydir_ = 1;
    image_.load(":img/enemy_predator.png");
    rect_ = image_.rect();
    isDead_ = false;
    healthBarColor_ = qRgb(64, 213, 43);
    healthBarColor_.setAlpha(204);
    healthBarBorderColor_ = qRgb(23, 78, 16);
    reward_ = 580;
    movesRandomly_ = true;
    projectile_ = 2;
    fireRate_ = 2;
}

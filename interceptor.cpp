#include "interceptor.h"

Interceptor::Interceptor(int x, int y)
{
    health_ = 80;
    maxHealth_ = health_;
    x_ = x;
    y_ = y;
    speed_ = 7;
    int directionIndex = rand() % 3;
    xdir_ = x_directions[directionIndex];
    ydir_ = y_directions[directionIndex];
    image_.load(":img/enemy_interceptor.png");
    rect_ = image_.rect();
    isDead_ = false;
    healthBarColor_ = qRgb(64, 213, 43);
    healthBarColor_.setAlpha(204);
    healthBarBorderColor_ = qRgb(23, 78, 16);
    reward_ = 10;
    movesRandomly_ = true;
    projectile_ = 3;
    fireRate_ = 6;
}


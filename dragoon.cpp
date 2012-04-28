#include "dragoon.h"

Dragoon::Dragoon(int x, int y)
{
    health_ = 425;
    maxHealth_ = health_;
    x_ = x;
    y_ = y;
    speed_ = 3;
    int directionIndex = rand() % 3;
    xdir_ = x_directions[directionIndex];
    ydir_ = y_directions[directionIndex];
    image_.load(":img/enemy_dragoon.png");
    rect_ = image_.rect();
    isDead_ = false;
    healthBarColor_ = qRgb(64, 213, 43);
    healthBarColor_.setAlpha(204);
    healthBarBorderColor_ = qRgb(23, 78, 16);
    reward_ = 132;
    movesRandomly_ = true;
    projectile_ = 2;
    fireRate_ = 5;
}

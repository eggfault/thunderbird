#include "jackal.h"

Jackal::Jackal(int x, int y)
{
    health_ = 222;
    maxHealth_ = health_;
    x_ = x;
    y_ = y;
    speed_ = 3;
    xdir_ = 0; ydir_ = 1;
    image_.load(":img/enemy_jackal.png");
    rect_ = image_.rect();
    isDead_ = false;
    healthBarColor_ = qRgb(64, 213, 43);
    healthBarColor_.setAlpha(204);
    healthBarBorderColor_ = qRgb(23, 78, 16);
    reward_ = 77;
    movesRandomly_ = false;
    projectile_ = 1;
    fireRate_ = 1;
}

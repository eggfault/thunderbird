#include "vector.h"

Vector::Vector(int x, int y, int xdir, int ydir)
{
    image_.load(":img/vector.png");
    rect_ = image_.rect();
    x_ = x;
    y_ = y;
    rect_.translate(x_, y_);
    isDead_ = false;
    xdir_ = xdir; ydir_ = ydir;
    speed_ = 3;
    damage_ = 10;
    isEnemyProjectile_ = true;
    isExplosive_ = false;
    isInvincible_ = false;
    isHoming_ = false;
}

#include "miniNuke.h"

MiniNuke::MiniNuke(int x, int y, int xdir, int ydir)
{
    image_.load(":img/miniNuke.png");
    rect_ = image_.rect();
    x_ = x;
    y_ = y;
    rect_.translate(x_, y_);
    isDead_ = false;
    xdir_ = xdir; ydir_ = ydir;
    damage_ = 666;
    speed_ = 2;
    isEnemyProjectile_ = false;
    isExplosive_ = true;
    isInvincible_ = false;
    isHoming_ = false;
}



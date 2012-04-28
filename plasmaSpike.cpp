#include "plasmaSpike.h"

PlasmaSpike::PlasmaSpike(int x, int y, int xdir, int ydir)
{
    image_.load(":img/plasmaSpike.png");
    rect_ = image_.rect();
    x_ = x;
    y_ = y;
    rect_.translate(x_, y_);
    isDead_ = false;
    xdir_ = xdir; ydir_ = ydir;
    speed_ = 5;
    damage_ = 48;
    isEnemyProjectile_ = false;
    isExplosive_ = false;
    isInvincible_ = false;
    isHoming_ = false;
}


#include "bullet450SMC.h"

Bullet450SMC::Bullet450SMC(int x, int y, int xdir, int ydir)
{
    image_.load(":img/bullet450SMC.png");
    rect_ = image_.rect();
    x_ = x;
    y_ = y;
    rect_.translate(x_, y_);
    isDead_ = false;
    xdir_ = xdir; ydir_ = ydir;
    speed_ = 3;
    damage_ = 7;
    isEnemyProjectile_ = false;
    isExplosive_ = false;
    isInvincible_ = false;
    isHoming_ = false;
}


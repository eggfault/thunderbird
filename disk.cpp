#include "disk.h"

Disk::Disk(int x, int y, int xdir, int ydir)
{
    image_.load(":img/disk.png");
    rect_ = image_.rect();
    x_ = x;
    y_ = y;
    rect_.translate(x_, y_);
    isDead_ = false;
    xdir_ = xdir; ydir_ = ydir;
    speed_ = 4;
    damage_ = 18;
    isEnemyProjectile_ = true;
    isExplosive_ = false;
    isInvincible_ = false;
    isHoming_ = false;
}


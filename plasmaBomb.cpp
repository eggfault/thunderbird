#include "plasmaBomb.h"

PlasmaBomb::PlasmaBomb(int x, int y, int xdir, int ydir)
{
    image_.load(":img/plasmaBomb.png");
    rect_ = image_.rect();
    x_ = x;
    y_ = y;
    rect_.translate(x_, y_);
    isDead_ = false;
    xdir_ = xdir; ydir_ = ydir;
    speed_ = 3;
    damage_ = 950;
    isEnemyProjectile_ = false;
    isExplosive_ = true;
    isInvincible_ = false;
    isHoming_ = false;
}

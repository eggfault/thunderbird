#include "hydraMissile.h"

HydraMissile::HydraMissile(int x, int y, int xdir, int ydir)
{
    image_.load(":img/hydraMissile.png");
    rect_ = image_.rect();
    x_ = x;
    y_ = y;
    rect_.translate(x_, y_);
    isDead_ = false;
    xdir_ = xdir; ydir_ = ydir;
    damage_ = 82;
    speed_ = 3;
    isEnemyProjectile_ = false;
    isExplosive_ = true;
    isInvincible_ = false;
    isHoming_ = true;
}

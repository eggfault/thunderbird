#include "laser.h"

Laser::Laser(int x, int y, int xdir, int ydir, int laserType)
{
    if(laserType == 0) { image_.load(":img/redLaser.png"); damage_ = 18; }
    else if(laserType == 1) { image_.load(":img/yellowLaser.png"); damage_ = 22; }
    else { image_.load(":img/blueLaser.png"); damage_ = 26; }
    rect_ = image_.rect();
    x_ = x;
    y_ = y;
    rect_.translate(x_, y_);
    isDead_ = false;
    xdir_ = xdir; ydir_ = ydir;
    speed_ = 4;
    isEnemyProjectile_ = false;
    isExplosive_ = false;
    isInvincible_ = false;
    isHoming_ = false;
}

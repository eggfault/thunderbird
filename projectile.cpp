#include "projectile.h"
#include "cmath"

void Projectile::autoMove()
{
    x_ += xdir_*speed_;
    y_ += ydir_*speed_;
    autoUpdateRect();
}

bool Projectile::isEnemyProjectile()
{
    return isEnemyProjectile_;
}

int Projectile::getDamage()
{
    return damage_;
}

bool Projectile::isInvincible()
{
    return isInvincible_;
}

bool Projectile::isExplosive()
{
    return isExplosive_;
}

bool Projectile::isHoming()
{
    return isHoming_;
}

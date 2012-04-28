#ifndef LIGHTNINGBALL_H
#define LIGHTNINGBALL_H

#include "projectile.h"

class LightningBall : public virtual Projectile
{
public:
    LightningBall(int x, int y, int xdir, int ydir);
    ~LightningBall();
};

#endif // LIGHTNINGBALL_H

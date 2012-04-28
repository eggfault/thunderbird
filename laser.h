#ifndef LASER_H
#define LASER_H

#include "projectile.h"

class Laser : public virtual Projectile
{
public:
    Laser(int x, int y, int xdir, int ydir, int laserType);
    ~Laser();
};

#endif // LASER_H

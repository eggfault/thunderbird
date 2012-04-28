#ifndef PLASMASPIKE_H
#define PLASMASPIKE_H

#include "projectile.h"

class PlasmaSpike : public virtual Projectile
{
public:
    PlasmaSpike(int x, int y, int xdir, int ydir);
    ~PlasmaSpike();
};

#endif // PLASMASPIKE_H

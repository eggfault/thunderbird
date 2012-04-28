#ifndef PLASMABOMB_H
#define PLASMABOMB_H

#include "projectile.h"

class PlasmaBomb : public virtual Projectile
{
public:
    PlasmaBomb(int x, int y, int xdir, int ydir);
    ~PlasmaBomb();
};

#endif // PLASMABOMB_H

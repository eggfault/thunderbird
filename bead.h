#ifndef BEAD_H
#define BEAD_H

#include "projectile.h"

class Bead : public virtual Projectile
{
public:
    Bead(int x, int y, int xdir, int ydir);
    ~Bead();
private:

};

#endif // BEAD_H

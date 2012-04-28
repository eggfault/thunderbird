#ifndef RAILBLAST_H
#define RAILBLAST_H

#include "projectile.h"

class RailBlast : public virtual Projectile
{
public:
    RailBlast(int x, int y, int xdir, int ydir);
    ~RailBlast();
private:
    int life_;
};

#endif // RAILBLAST_H

#ifndef MININUKE_H
#define MININUKE_H

#include "projectile.h"

class MiniNuke : public virtual Projectile
{
public:
    MiniNuke(int x, int y, int xdir, int ydir);
    ~MiniNuke();
};

#endif // MININUKE_H

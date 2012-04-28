#ifndef HYDRAMISSILE_H
#define HYDRAMISSILE_H

#include "projectile.h"

class HydraMissile : public virtual Projectile
{
public:
    HydraMissile(int x, int y, int xdir, int ydir);
    ~HydraMissile();
private:

};

#endif // HYDRAMISSILE_H

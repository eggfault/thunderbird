#ifndef BULLET450SMC_H
#define BULLET450SMC_H

#include "projectile.h"

class Bullet450SMC : public virtual Projectile
{
public:
    Bullet450SMC(int x, int y, int xdir, int ydir);
    ~Bullet450SMC();
private:

};

#endif // BULLET450SMC_H

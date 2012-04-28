#ifndef BULLET25MM_H
#define BULLET25MM_H

#include "projectile.h"

class Bullet25mm : public virtual Projectile
{
public:
    Bullet25mm(int x, int y, int xdir, int ydir);
	~Bullet25mm();
private:

};

#endif

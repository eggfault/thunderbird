#ifndef VECTOR_H
#define VECTOR_H

#include "projectile.h"

class Vector : public virtual Projectile
{
public:
    Vector(int x, int y, int xdir, int ydir);
	~Vector();
private:

};

#endif

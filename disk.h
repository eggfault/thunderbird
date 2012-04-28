#ifndef DISK_H
#define DISK_H

#include "projectile.h"

class Disk : public virtual Projectile
{
public:
    Disk(int x, int y, int xdir, int ydir);
    ~Disk();
private:

};

#endif // DISK_H

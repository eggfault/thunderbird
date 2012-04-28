#ifndef SCENERY_H
#define SCENERY_H

#include "object.h"

class Scenery : public virtual Object
{
    public:
        Scenery(int x, int y, int speed, int type, int rotation);
        ~Scenery();
        void autoMove();
    private:
};

#endif // SCENERY_H

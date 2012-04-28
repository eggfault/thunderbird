#ifndef LIGHTNINGFX_H
#define LIGHTNINGFX_H

#include "object.h"

class LightningFX : public virtual Object
{
public:
    LightningFX(int x1, int y1, int x2, int y2);
    ~LightningFX();
private:
};

#endif // LIGHTNINGFX_H

#ifndef CARRIER_H
#define CARRIER_H

#include "enemy.h"

class Carrier : public virtual Enemy
{

  public:
    Carrier(int x, int y);
    ~Carrier();

  private:
};

#endif // CARRIER_H

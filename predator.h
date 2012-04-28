#ifndef PREDATOR_H
#define PREDATOR_H

#include "enemy.h"

class Predator : public virtual Enemy
{

  public:
    Predator(int x, int y);
    ~Predator();

  private:

};

#endif // PREDATOR_H

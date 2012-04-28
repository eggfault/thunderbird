#ifndef FIGHTER_H
#define FIGHTER_H

#include "enemy.h"

class Fighter : public virtual Enemy
{

  public:
    Fighter(int x, int y);
    ~Fighter();

  private:

};

#endif // FIGHTER_H

#ifndef SCOUT_H
#define SCOUT_H

#include "enemy.h"

class Scout : public virtual Enemy
{

  public:
    Scout(int x, int y);
    ~Scout();

  private:

};

#endif
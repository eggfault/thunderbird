#ifndef INTERCEPTOR_H
#define INTERCEPTOR_H

#include "enemy.h"

class Interceptor : public virtual Enemy
{

  public:
    Interceptor(int x, int y);
    ~Interceptor();

  private:

};

#endif // INTERCEPTOR_H

#ifndef CREDIT_H
#define CREDIT_H

#include "object.h"

class Credit : public virtual Object
{
    public:
        Credit(int x, int y);
        ~Credit();
        void autoMove();
};

#endif // CREDIT_H

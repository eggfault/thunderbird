#ifndef MEDIPAK_H
#define MEDIPAK_H

#include "object.h"

class Medipak : public virtual Object
{
    public:
        Medipak(int x, int y);
        ~Medipak();
        void autoMove();
    private:

};

#endif

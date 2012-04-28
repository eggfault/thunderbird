#ifndef BUBBLESHIELD_H
#define BUBBLESHIELD_H

#include "object.h"

class BubbleShield : public virtual Object
{
    public:
        BubbleShield();
        ~BubbleShield();
        void activate();
        void deactivate();
        bool isActivated();
        int getRadius();
    private:
        bool activated_;
        int radius_;
};

#endif // BUBBLESHIELD_H

#include "bubbleShield.h"

BubbleShield::BubbleShield()
{
    image_.load(":img/bubbleShield.png");
    rect_ = image_.rect();
    x_ = 0;
    y_ = 0;
    rect_.translate(x_, y_);
    isDead_ = false;
    xdir_ = 0; ydir_ = 0;
    speed_ = 0;
    activated_ = false;
    radius_ = rect_.width()/2;
}

void BubbleShield::activate()
{
    activated_ = true;
}

void BubbleShield::deactivate()
{
    activated_ = false;
}

int BubbleShield::getRadius()
{
    return radius_;
}

bool BubbleShield::isActivated()
{
    return activated_;
}

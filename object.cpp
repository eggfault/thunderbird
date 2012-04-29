#include "object.h"

QImage &Object::getImage()
{
    return image_;
}

void Object::setRect(QRect rect)
{
    rect_ = rect;
}

QRect Object::getRect()
{
    return rect_;
}

int Object::getSpeed()
{
    return speed_;
}

bool Object::isDead()
{
    return isDead_;
}

void Object::setIsDead(bool isDead)
{
    isDead_ = isDead;
}

void Object::setXdir(int xdir)
{
    xdir_ = xdir;
}

void Object::setYdir(int ydir)
{
    ydir_ = ydir;
}

int Object::getXdir()
{
    return xdir_;
}

int Object::getYdir()
{
    return ydir_;
}

void Object::autoUpdateRect()
{
    rect_.moveTo(x_, y_);
}

#ifndef CHARACTER_H
#define CHARACTER_H

#include "object.h"
#include <QColor>

class Character : public virtual Object
{
  public:
    void modifyHealth(int amount);
    void setHealth(int health);
    int getHealth();
    int getMaxHealth();
    QColor getHealthBarColor();
    QColor getHealthBarBorderColor();
    QImage getHealthBarImage();
    QImage getHealthBarBackgroundImage();
    void teleport(int x, int y);

  protected:
    int health_;
    int maxHealth_;
    QColor healthBarColor_;
    QColor healthBarBorderColor_;
    QImage healthBarImage_;
    QImage healthBarBackgroundImage_;
};

#endif

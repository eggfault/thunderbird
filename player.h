#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"

class Player : public virtual Character
{

  public:
    Player(int x, int y, int currentHealth, int maxHealth);
    ~Player();
	void moveLeft(int amount);
	void moveRight(int amount);
    void moveUp(int amount);
    void moveDown(int amount);
    void resetState(int x, int y);
    void modifyPower(int amount);
    void setMaxPower(int maxPower);
    int getPower();
    int getMaxPower();
    QColor getPowerBarColor();
    QColor getPowerBarBorderColor();
    QImage getPowerBarImage();
    QImage getPowerBarBackgroundImage();
  private:
    int power_;
    int maxPower_;
    QColor powerBarColor_;
    QColor powerBarBorderColor_;
    QImage powerBarImage_;
    QImage powerBarBackgroundImage_;
};

#endif

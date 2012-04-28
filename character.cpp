#include "character.h"

int Character::getHealth()
{
	return health_;
}

void Character::modifyHealth(int amount)
{
	health_ += amount;
}

void Character::setHealth(int health)
{
    health_ = health;
}

int Character::getMaxHealth()
{
	return maxHealth_;
}

QColor Character::getHealthBarColor()
{
	return healthBarColor_;
}

QColor Character::getHealthBarBorderColor()
{
	return healthBarBorderColor_;
}

QImage Character::getHealthBarImage()
{
	return healthBarImage_;
}

QImage Character::getHealthBarBackgroundImage()
{
	return healthBarBackgroundImage_;
}

void Character::teleport(int x, int y)
{
    x_ = x;
    y_ = y;
}

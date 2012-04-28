#include "scout.h"

Scout::Scout(int x, int y)
{
    health_ = 16;
	maxHealth_ = health_;
	x_ = x;
	y_ = y;
	speed_ = 2;
    xdir_ = 0;
	ydir_ = 1;
    image_.load(":img/enemy_scout.png");
	rect_ = image_.rect();
	isDead_ = false;
	healthBarColor_ = qRgb(64, 213, 43);
	healthBarColor_.setAlpha(204);
	healthBarBorderColor_ = qRgb(23, 78, 16);
    reward_ = 26;
    movesRandomly_ = false;
    projectile_ = 1;
    fireRate_ = 1;
}

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "object.h"

class Projectile : public virtual Object
{
public:
	void autoMove();
	bool isEnemyProjectile();
	int getDamage();
    bool isInvincible();
    bool isExplosive();
    bool isHoming();
protected:
	int damage_;
    bool isEnemyProjectile_;
    bool isExplosive_;
    bool isInvincible_;
    bool isHoming_;
};

#endif

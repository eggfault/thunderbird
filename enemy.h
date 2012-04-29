#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"
#include "projectile.h"

class Enemy : public virtual Character
{
    public:
        void autoMove();
        int getReward();
        bool movesRandomly();
        void modifyX(int amount);
        void modifyY(int amount);
        int getProjectile();
        int getFireRate();
    protected:
        int reward_;
        bool movesRandomly_;
        int projectile_;
        int fireRate_;
};

#endif

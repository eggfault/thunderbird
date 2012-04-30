#include "enemy.h"

void Enemy::autoMove()
{
    x_ += xdir_*speed_;
    y_ += ydir_*speed_;
    autoUpdateRect();
}

int Enemy::getReward()
{
    return reward_;
}

bool Enemy::movesRandomly()
{
    return movesRandomly_;
}

void Enemy::modifyX(int amount)
{
    x_ += amount;
}

void Enemy::modifyY(int amount)
{
    y_ += amount;
}

int Enemy::getProjectile()
{
    return projectile_;
}

int Enemy::getFireRate()
{
    return fireRate_;
}

#include "player.h"
#include <iostream>

Player::Player(int x, int y, int currentHealth, int maxHealth)
{
    x_ = x;
    y_ = y;
    speed_ = 3;
    xdir_ = 0;
    ydir_ = 0;
    image_.load(":img/player.png");
    healthBarImage_.load("img/playerHealthBar.png");
    healthBarBackgroundImage_.load("img/playerHealthBarBackground.png");
    rect_ = image_.rect();
    health_ = currentHealth;
    maxHealth_ = maxHealth;
    healthBarColor_ = qRgb(6, 113, 220);
    healthBarColor_.setAlpha(204);
    healthBarBorderColor_ = qRgb(124, 179, 242);
    powerBarColor_ = qRgb(159, 10, 245);
    powerBarColor_.setAlpha(180);
    powerBarBorderColor_ = qRgb(78, 6, 120);
    power_ = maxPower;
    maxPower_ = power_;
}

Player::~Player()
{
}

void Player::moveLeft(int speed)
{
    x_ -= speed;
}

void Player::moveRight(int speed)
{
    x_ += speed;
}

void Player::moveUp(int speed)
{
    y_ -= speed;
}

void Player::moveDown(int speed)
{
    y_ += speed;
}

void Player::resetState(int x, int y)
{
    x_ = x;
    y_ = y;
    health_ = maxHealth_;
}

void Player::setMaxPower(int maxPower)
{
    maxPower_ = maxPower;
}

int Player::getPower()
{
    return power_;
}

int Player::getMaxPower()
{
    return maxPower_;
}

void Player::modifyPower(int amount)
{
    power_ += amount;
}

QColor Player::getPowerBarColor()
{
    return powerBarColor_;
}

QColor Player::getPowerBarBorderColor()
{
    return powerBarBorderColor_;
}

QImage Player::getPowerBarImage()
{
    return powerBarImage_;
}

QImage Player::getPowerBarBackgroundImage()
{
    return powerBarBackgroundImage_;
}

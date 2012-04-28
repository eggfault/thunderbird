#ifndef BAKOOM_H
#define BAKOOM_H

#include "scout.h"
#include "medipak.h"
#include "player.h"
#include "bullet25mm.h"
#include "bullet450SMC.h"
#include "laser.h"
#include "vector.h"
#include "fighter.h"
#include "credit.h"
#include "jackal.h"
#include "dragoon.h"
#include "disk.h"
#include "plasmaSpike.h"
#include "hydraMissile.h"
#include "miniNuke.h"
#include "predator.h"
#include "plasmaBomb.h"
#include "lightningBall.h"
#include "railBlast.h"
#include "carrier.h"
#include "interceptor.h"
#include "eagle.h"
#include "bead.h"
#include "bubbleShield.h"
#include "scenery.h"
#include <QWidget>
#include <QKeyEvent>
#include <vector>
#include <ctime>

using namespace std;

class Bakoom : public QWidget
{
  public:
    Bakoom(vector<Enemy*> enemies, QWidget *parent = 0);
    ~Bakoom();

  protected:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
    void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);

    void startGame();
    void pauseGame();
    void stopGame();
    void victory();
    void checkCollision();
	void checkOutOfBounds();
	void deleteDead();
	void spawnMedipaks();
	void playerKeyEvents();
    void shootProjectile();
    void moveEnemies();
	void createEnemyProjectiles();
    void activateBubbleShield();
    void deactivateBubbleShield();
    void createRandomScenery();
    void autoHeal();
	friend bool objectIsDead(Object* o);
    Enemy* nearestEnemyTo(int x, int y);
    double distanceBetween(int x1, int y1, int x2, int y2);

  private:
    int timerId_;
    vector<Medipak*> medipaks_;
    vector<Projectile*> projectiles_;
    vector<Enemy*> enemies_;
    vector<Credit*> credits_;
    vector<Scenery*> scenery_;
    Player *player_;
    bool gameOver_;
    bool gameWon_;
    bool gameStarted_;
    bool paused_;
    clock_t shootCooldown_;
    clock_t powerRechargeTimer_;
    clock_t autoHealTimer_;
    BubbleShield *bubbleShield_;
    int ammunition_[20];

    int currentWeapon_;
    int selectedShopItem_;

    int cooldowns_[20];
    int powerRechargeCooldown_;
    int autoHealCooldown_;
	
    bool aKeyPressed_;
    bool dKeyPressed_;
    bool wKeyPressed_;
    bool sKeyPressed_;
    bool spacebarKeyPressed_;
    bool shiftKeyPressed_;

    int enemyMovementTimer_;
    int const autoHealAmount_;
    int const medipakHealAmount_;
    int const minCreditAmount_;
    int const maxCreditAmount_;
};

#endif

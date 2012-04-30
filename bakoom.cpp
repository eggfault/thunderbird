#include "bakoom.h"
#include "global.h"
#include <QPainter>
#include <QApplication>
#include <algorithm>
#include <iostream>
#include <cmath>

bool objectIsDead(Object* o)
{
    return o->isDead();
}

Bakoom::Bakoom(vector<Enemy*> enemies, QWidget *parent) : QWidget(parent), medipakHealAmount_(25),
    minCreditAmount_(15), maxCreditAmount_(25), autoHealAmount_(1)
{
    gameOver_ = false;
    gameWon_ = false;
    paused_ = false;
    gameStarted_ = false;
    player_  = new Player (windowWidth/2, windowHeight-lowerUIHeight-50, shield, maxShield);
    bubbleShield_ = new BubbleShield();
    shootCooldown_ = 0;
    powerRechargeTimer_ = 0;
    autoHealTimer_ = 0;
    enemyMovementTimer_ = 0;
    restarting = false;
    enemies_ = enemies;

    currentWeapon_ = 0;

    // used to be needed because Unix OS and Windows OS operate on different clocks when using clock() function (which is no longer used)
    double clockFactor = 4.14; // calibrated to be same as clock() on Unix, may still need adjusting since Windows is reference environment
                               // formula: (12650-2852)/(10520000-3420000)*3000 (timed by Andrew on Unix)
                               //          QTime time   clock() time       old clockFactor for Unix
    // CHANGE THIS IN LATER VER
    if(hasItem[3]) cooldowns_[0] = 7*clockFactor;                       // check if has gatling gun upgrade
    else            cooldowns_[0] = 14*clockFactor;                     // bullet 450 SMC
    if(hasItem[3]) cooldowns_[1] = 6*clockFactor;
    else            cooldowns_[1] = 12*clockFactor;                     // bullet 25mm
    cooldowns_[5] = 8*clockFactor;                      // red laser
    cooldowns_[6] = 8*clockFactor;                      // yellow laser
    cooldowns_[7] = 8*clockFactor;                      // blue laser
    cooldowns_[9] = 70*clockFactor;                     // hydra missile
    cooldowns_[10] = 200*clockFactor;                   // mininuke
    cooldowns_[13] = 12*clockFactor;                    // plasma spike
    cooldowns_[14] = 130*clockFactor;                   // plasma bomb
    cooldowns_[18] = 6*clockFactor;                     // tesla coil
    cooldowns_[19] = 60*clockFactor;                    // railgun
    powerRechargeCooldown_ = 2*clockFactor;
    autoHealCooldown_ = 25*clockFactor;

    ammunition_[0] = 9999;
    ammunition_[1] = 350;
    ammunition_[5] = 100;
    ammunition_[6] = 100;
    ammunition_[7] = 100;
    ammunition_[9] = 26;
    ammunition_[10] = 6;
    ammunition_[13] = 60;
    ammunition_[14] = 8;
    ammunition_[18] = 66;
    ammunition_[19] = 4;

    aKeyPressed_ = false;
    dKeyPressed_ = false;
    wKeyPressed_ = false;
    sKeyPressed_ = false;
    spacebarKeyPressed_ = false;

    startGame();
}

Bakoom::~Bakoom()
{
    delete player_ ;
}

void Bakoom::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if(gameOver_)
    {
        QFont font("Arial", 10, QFont::DemiBold);
        int text_x = 0; int text_y = windowHeight/4;
        painter.setFont(font);
        painter.setPen(Qt::white);
        painter.drawText(text_x,text_y,windowWidth,16,Qt::AlignCenter,"You were eaten alive by the Bruins :-(");
        text_y += 70;
        painter.drawText(text_x,text_y,windowWidth,16,Qt::AlignCenter,"Final score: " + QString::number(score));
        text_y += 70;
        painter.drawText(text_x,text_y,windowWidth,16,Qt::AlignCenter,"Press [R] to Restart");
        text_y += 70;
        painter.drawText(text_x,text_y,windowWidth,16,Qt::AlignCenter,"(You keep your stuff)");
    }
    else
    {
        QRect healthRect, powerRect;
        QFont scoreFont("Arial", 8, QFont::Normal);
        QFont noAmmo("Arial",16, QFont::Normal);
        // draw scenery
        for(int i = 0; i < scenery_.size(); i++)
            painter.drawImage(scenery_.at(i)->getRect(), scenery_.at(i)->getImage());
        // draw enemies and enemy health
        for(int i = 0; i < enemies_.size(); i++)
        {
            painter.drawImage(enemies_.at(i)->getRect(), enemies_.at(i)->getImage());
                healthRect.setX(enemies_.at(i)->getRect().x());
                healthRect.setY(enemies_.at(i)->getRect().y()-15);
                healthRect.setWidth(enemies_.at(i)->getRect().width());
                healthRect.setHeight(8);
            painter.setBrush(Qt::NoBrush);
            painter.setPen(enemies_.at(i)->getHealthBarBorderColor());
            painter.drawRect(healthRect);
                healthRect.setWidth(enemies_.at(i)->getRect().width()*enemies_.at(i)->getHealth()/enemies_.at(i)->getMaxHealth());
            painter.setBrush(enemies_.at(i)->getHealthBarColor());
            painter.setPen(Qt::NoPen);
            painter.drawRect(healthRect);
        }
        // draw medipaks
        for(int i = 0; i < medipaks_.size(); i++)
            painter.drawImage(medipaks_.at(i)->getRect(), medipaks_.at(i)->getImage());
        // draw credits
        for(int i = 0; i < credits_.size(); i++)
            painter.drawImage(credits_.at(i)->getRect(), credits_.at(i)->getImage());
        // draw projectiles
        for(int i = 0; i < projectiles_.size(); i++)
            painter.drawImage(projectiles_.at(i)->getRect(), projectiles_.at(i)->getImage());
        // draw player
        painter.drawImage(player_ ->getRect(), player_ ->getImage());
        // draw bubble shield
        if(bubbleShield_->isActivated()) painter.drawImage(QRect(player_ ->getRect().x()-18, player_ ->getRect().y()-25,
            bubbleShield_->getRect().width(), bubbleShield_->getRect().height()), bubbleShield_->getImage());
        // draw score, credits, ammo
        painter.setFont(scoreFont);
        painter.setPen(Qt::white);
        painter.drawText(10,10,200,16,Qt::AlignLeft,"Score: " + QString::number(score));
        painter.setPen(Qt::yellow);
        painter.drawText(10,24,200,16,Qt::AlignLeft,"Credits: " + QString::number(credits));
        if(ammunition_[currentWeapon_] > 0) painter.setPen(Qt::white);
        else painter.setPen(Qt::red);
        painter.drawText(10,38,200,16,Qt::AlignLeft,"Ammo: " + QString::number(ammunition_[currentWeapon_]));
        // draw NO AMMO message
        if(ammunition_[currentWeapon_] <= 0 && time.elapsed() % 100 < 50)
        {
            painter.setFont(noAmmo);
            painter.setPen(Qt::red);
            painter.drawText(0,windowHeight/2,windowWidth,30,Qt::AlignCenter,"NO AMMO! SWITCH WEAPONS!");
        }
        // draw player health
            healthRect.setX(windowWidth-206);
            healthRect.setY(10);
            healthRect.setWidth(196);
            healthRect.setHeight(24);
        painter.setBrush(Qt::NoBrush);
        painter.setPen(player_ ->getHealthBarBorderColor());
        painter.drawRect(healthRect);
            healthRect.setWidth(196*player_ ->getHealth()/player_ ->getMaxHealth());
        painter.setBrush(player_ ->getHealthBarColor());
        painter.setPen(Qt::NoPen);
        painter.drawRect(healthRect);
        // draw player power
            powerRect.setX(windowWidth-206);
            powerRect.setY(36);
            powerRect.setWidth(196);
            powerRect.setHeight(8);
        painter.setBrush(Qt::NoBrush);
        painter.setPen(player_ ->getPowerBarBorderColor());
        painter.drawRect(powerRect);
            powerRect.setWidth(196*player_ ->getPower()/player_ ->getMaxPower());
        painter.setBrush(player_ ->getPowerBarColor());
        painter.setPen(Qt::NoPen);
        painter.drawRect(powerRect);
        // draw lower UI
        painter.setBrush(Qt::gray);
        painter.drawRect(0,windowHeight-lowerUIHeight,windowWidth,lowerUIHeight);
        // draw weapon icons
        int icon_x = 10; int icon_y = windowHeight-lowerUIHeight+10;
        int offset = 40;
        painter.drawImage(icon_x,icon_y,QImage(":img/icon_bullet450SMC.png"));
        if(currentWeapon_ == 0) painter.drawImage(icon_x,icon_y,QImage(":img/icon_selection.png"));
        icon_x += offset;
        if(hasItem[1]) painter.drawImage(icon_x,icon_y,QImage(":img/icon_bullet25mm.png"));
        else painter.drawImage(icon_x,icon_y,QImage(":img/icon_locked.png"));
        if(currentWeapon_ == 1) painter.drawImage(icon_x,icon_y,QImage(":img/icon_selection.png"));
        icon_x += offset;
        if(hasItem[5]) painter.drawImage(icon_x,icon_y,QImage(":img/icon_redLaser.png"));
        else painter.drawImage(icon_x,icon_y,QImage(":img/icon_locked.png"));
        if(currentWeapon_ == 5) painter.drawImage(icon_x,icon_y,QImage(":img/icon_selection.png"));
        icon_x += offset;
        if(hasItem[6]) painter.drawImage(icon_x,icon_y,QImage(":img/icon_yellowLaser.png"));
        else painter.drawImage(icon_x,icon_y,QImage(":img/icon_locked.png"));
        if(currentWeapon_ == 6) painter.drawImage(icon_x,icon_y,QImage(":img/icon_selection.png"));
        icon_x += offset;
        if(hasItem[7]) painter.drawImage(icon_x,icon_y,QImage(":img/icon_blueLaser.png"));
        else painter.drawImage(icon_x,icon_y,QImage(":img/icon_locked.png"));
        if(currentWeapon_ == 7) painter.drawImage(icon_x,icon_y,QImage(":img/icon_selection.png"));
        icon_x += offset;
        if(hasItem[9]) painter.drawImage(icon_x,icon_y,QImage(":img/icon_hydraMissile.png"));
        else painter.drawImage(icon_x,icon_y,QImage(":img/icon_locked.png"));
        if(currentWeapon_ == 9) painter.drawImage(icon_x,icon_y,QImage(":img/icon_selection.png"));
        icon_x += offset;
        if(hasItem[10]) painter.drawImage(icon_x,icon_y,QImage(":img/icon_miniNuke.png"));
        else painter.drawImage(icon_x,icon_y,QImage(":img/icon_locked.png"));
        if(currentWeapon_ == 10) painter.drawImage(icon_x,icon_y,QImage(":img/icon_selection.png"));
        icon_x += offset;
        if(hasItem[13]) painter.drawImage(icon_x,icon_y,QImage(":img/icon_plasmaSpike.png"));
        else painter.drawImage(icon_x,icon_y,QImage(":img/icon_locked.png"));
        if(currentWeapon_ == 13) painter.drawImage(icon_x,icon_y,QImage(":img/icon_selection.png"));
        icon_x += offset;
        if(hasItem[14]) painter.drawImage(icon_x,icon_y,QImage(":img/icon_plasmaBomb.png"));
        else painter.drawImage(icon_x,icon_y,QImage(":img/icon_locked.png"));
        if(currentWeapon_ == 14) painter.drawImage(icon_x,icon_y,QImage(":img/icon_selection.png"));
        icon_x += offset;
        if(hasItem[18]) painter.drawImage(icon_x,icon_y,QImage(":img/icon_teslaCoil.png"));
        else painter.drawImage(icon_x,icon_y,QImage(":img/icon_locked.png"));
        if(currentWeapon_ == 18) painter.drawImage(icon_x,icon_y,QImage(":img/icon_selection.png"));
        icon_x += offset;
        if(hasItem[19]) painter.drawImage(icon_x,icon_y,QImage(":img/icon_railgun.png"));
        else painter.drawImage(icon_x,icon_y,QImage(":img/icon_locked.png"));
        if(currentWeapon_ == 19) painter.drawImage(icon_x,icon_y,QImage(":img/icon_selection.png"));
        icon_x += offset;
    }
}

void Bakoom::timerEvent(QTimerEvent *event)
{
    // create random scenery
    createRandomScenery();
    // level 6 and 7 enemy spawns
    if(level >= 6)
        for(int i = 0; i < enemies_.size(); i++)
            if(rand()%1000 < 5 && enemies_.size() <= 12) enemies_.push_back(new Interceptor(enemies_.at(i)->getRect().x(), enemies_.at(i)->getRect().y()));
    // move scenery
    for(int i = 0; i < scenery_.size(); i++)
        scenery_.at(i)->autoMove();
    // move enemies
    moveEnemies();
    // make enemies shoot
    createEnemyProjectiles();
    // automove credits
    for(int i = 0; i < credits_.size(); i++)
        credits_.at(i)->autoMove();
    // automove medipaks
    for(int i = 0; i < medipaks_.size(); i++)
        medipaks_.at(i)->autoMove();
    // automove projectiles
    for(int i = 0; i < projectiles_.size(); i++)
    {
        // homing projectiles
        if(projectiles_.at(i)->isHoming())
        {
            int proj_x = projectiles_.at(i)->getRect().x(), proj_y = projectiles_.at(i)->getRect().y();
            int enem_x = nearestEnemyTo(proj_x, proj_y)->getRect().x(), enem_y = nearestEnemyTo(proj_x, proj_y)->getRect().y();
            if(distanceBetween(enem_x, enem_y, proj_x, proj_y) < 250)
            {
                if(projectiles_.at(i)->isEnemyProjectile())
                    enem_x = player_ ->getRect().x();
                if(enem_x+40 > proj_x) projectiles_.at(i)->setXdir(1);
                else if(enem_x-40 < proj_x) projectiles_.at(i)->setXdir(-1);
                else projectiles_.at(i)->setXdir(0);
            }
        }
        projectiles_.at(i)->autoMove();
    }
    checkCollision();
    checkOutOfBounds();
    deleteDead();
    // check for win condition
    if(enemies_.size() == 0 && credits_.size() == 0)
    {
        shield = player_ ->getHealth();     // update shield variable before exiting
        qApp->exit();
    }
    // auto heal if applicable
    if(hasItem[15])
        autoHeal();
    playerKeyEvents();
    //deleteDead();
    // move player
    player_->autoUpdateRect();
    spawnMedipaks();
    repaint();
}

void Bakoom::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
        case Qt::Key_A:
            aKeyPressed_ = true;
            break;
        case Qt::Key_D:
            dKeyPressed_ = true;
            break;
        case Qt::Key_W:
            wKeyPressed_ = true;
            break;
        case Qt::Key_S:
            sKeyPressed_ = true;
            break;
        case Qt::Key_Space:
            spacebarKeyPressed_ = true;
            break;
        case Qt::Key_1:
            currentWeapon_ = 0;
            break;
        case Qt::Key_2:
            if(hasItem[1]) currentWeapon_ = 1;
            break;
        case Qt::Key_3:
            if(hasItem[5]) currentWeapon_ = 5;
            break;
        case Qt::Key_4:
            if(hasItem[6]) currentWeapon_ = 6;
            break;
        case Qt::Key_5:
            if(hasItem[7]) currentWeapon_ = 7;
            break;
        case Qt::Key_6:
            if(hasItem[9]) currentWeapon_ = 9;
            break;
        case Qt::Key_7:
            if(hasItem[10]) currentWeapon_ = 10;
            break;
        case Qt::Key_8:
            if(hasItem[13]) currentWeapon_ = 13;
            break;
        case Qt::Key_9:
            if(hasItem[14]) currentWeapon_ = 14;
            break;
        case Qt::Key_0:
            if(hasItem[18]) currentWeapon_ = 18;
            break;
        case Qt::Key_Minus:
            if(hasItem[19]) currentWeapon_ = 19;
            break;
        case Qt::Key_P:
            pauseGame();
            break;
        case Qt::Key_Shift:
            if(hasItem[17])
                bubbleShield_->activate();
            break;
        case Qt::Key_Control:
            if(hasItem[17])
                bubbleShield_->activate();
            break;
        /*
        case Qt::Key_Tab:
            qApp->exit();
            break;
        */
        case Qt::Key_R:
            if(gameOver_)
            {
                restarting = true;
                qApp->exit();
            }
            break;
        case Qt::Key_Escape:
            restarting = true;
            qApp->exit();
        default:
            QWidget::keyPressEvent(event);
    }
}

void Bakoom::playerKeyEvents()
{
    if(spacebarKeyPressed_)
        shootProjectile();
    if(wKeyPressed_ && player_ ->getRect().top() > (windowHeight-lowerUIHeight)*3/4)
        player_ ->moveUp(player_ ->getSpeed());
    if(sKeyPressed_ && player_ ->getRect().bottom() < windowHeight-lowerUIHeight)
        player_ ->moveDown(player_ ->getSpeed());
    if(dKeyPressed_ && !aKeyPressed_ && player_ ->getRect().x()+player_ ->getRect().width() < windowWidth)
        player_ ->moveRight(player_ ->getSpeed());
    if(aKeyPressed_ && !dKeyPressed_ && player_ ->getRect().x() > 0)
        player_ ->moveLeft(player_ ->getSpeed());
    if(time.elapsed() - powerRechargeTimer_ >= powerRechargeCooldown_)
    {
        if(bubbleShield_->isActivated() && player_ ->getPower() > 0) player_ ->modifyPower(-2);
        else if(!bubbleShield_->isActivated() && player_ ->getPower() < player_ ->getMaxPower()) player_ ->modifyPower(1);
        else if(bubbleShield_->isActivated() && player_ ->getPower() <= 0) bubbleShield_->deactivate();
        powerRechargeTimer_ = time.elapsed();
    }
}

void Bakoom::keyReleaseEvent(QKeyEvent* event)
{
    switch (event->key())
    {
        case Qt::Key_A:
            aKeyPressed_ = false;
            break;
        case Qt::Key_D:
            dKeyPressed_ = false;
            break;
        case Qt::Key_W:
            wKeyPressed_ = false;
            break;
        case Qt::Key_S:
            sKeyPressed_ = false;
            break;
        case Qt::Key_Space:
            spacebarKeyPressed_ = false;
            break;
        case Qt::Key_Shift:
            bubbleShield_->deactivate();
            break;
        case Qt::Key_Control:
            bubbleShield_->deactivate();
            break;
        default:
            QWidget::keyPressEvent(event);
    }
}

void Bakoom::startGame()
{ 
    if (!gameStarted_)
    {
        gameOver_ = FALSE;
        gameWon_ = FALSE;
        gameStarted_ = TRUE;
        time.start();
        timerId_ = startTimer(10);
    }
}

void Bakoom::pauseGame()
{
    if (paused_)
    {
        timerId_ = startTimer(10);
        paused_ = FALSE;
    }
    else
    {
        paused_ = TRUE;
        killTimer(timerId_);
    }
}

void Bakoom::stopGame()
{   
    gameOver_ = TRUE;
    gameStarted_ = FALSE;
}

void Bakoom::victory()
{
    killTimer(timerId_);
    gameWon_ = TRUE;
    gameStarted_ = FALSE;
}

void Bakoom::shootProjectile()
{
    if(time.elapsed() - shootCooldown_ >= cooldowns_[currentWeapon_])   // cooldown timer
    {
        if(ammunition_[currentWeapon_] <= 0)
            return;
        int projLeft_x = player_ ->getRect().x()+14;
        int projLeft_y = player_ ->getRect().y()-6;
        int projRight_x = player_ ->getRect().x()+44;
        int projRight_y = projLeft_y;
        int projCenter_x = player_ ->getRect().x()+player_ ->getRect().width()/2 - 12;
        int projCenter_y = projLeft_y;
        switch(currentWeapon_)
        {
            case 0:
                projectiles_.push_back(new Bullet450SMC(projLeft_x, projLeft_y, 0, -1));
                projectiles_.push_back(new Bullet450SMC(projRight_x, projRight_y, 0, -1));
            break;
            case 1:
                projectiles_.push_back(new Bullet25mm(projLeft_x, projLeft_y, 0, -1));
                projectiles_.push_back(new Bullet25mm(projRight_x, projRight_y, 0, -1));
                ammunition_[1] -= 2;
            break;
            case 5:
                projectiles_.push_back(new Laser(projLeft_x, projLeft_y, 0, -1, 0));
                projectiles_.push_back(new Laser(projRight_x, projRight_y, 0, -1, 0));
                ammunition_[5] -= 2;
            break;
            case 6:
                projectiles_.push_back(new Laser(projLeft_x, projLeft_y, 0, -1, 1));
                projectiles_.push_back(new Laser(projRight_x, projRight_y, 0, -1, 1));
                ammunition_[6] -= 2;
            break;
            case 7:
                projectiles_.push_back(new Laser(projLeft_x, projLeft_y, 0, -1, 2));
                projectiles_.push_back(new Laser(projRight_x, projRight_y, 0, -1, 2));
                ammunition_[7] -= 2;
            break;
            case 9:
                projectiles_.push_back(new HydraMissile(projLeft_x, projLeft_y, 0, -1));
                projectiles_.push_back(new HydraMissile(projRight_x, projRight_y, 0, -1));
                ammunition_[9] -= 2;
                break;
            case 10:
                projectiles_.push_back(new MiniNuke(projLeft_x, projLeft_y, 0, -1));
                projectiles_.push_back(new MiniNuke(projRight_x, projRight_y, 0, -1));
                ammunition_[10] -= 2;
                break;
            case 13:
                projectiles_.push_back(new PlasmaSpike(projLeft_x, projLeft_y, 0, -1));
                projectiles_.push_back(new PlasmaSpike(projRight_x, projRight_y, 0, -1));
                ammunition_[13] -= 2;
                break;
            case 14:
                projectiles_.push_back(new PlasmaBomb(projCenter_x, projCenter_y, 0, -1));
                ammunition_[18] -= 1;
                break;
            case 18:
                projectiles_.push_back(new LightningBall(projCenter_x, projCenter_y, -1, -1));
                projectiles_.push_back(new LightningBall(projCenter_x, projCenter_y, 0, -1));
                projectiles_.push_back(new LightningBall(projCenter_x, projCenter_y, 1, -1));
                ammunition_[18] -= 3;
                break;
            case 19:
                projectiles_.push_back(new RailBlast(projCenter_x, projCenter_y, 0, -1));
                ammunition_[19] -= 1;
            break;
            default:
                projectiles_.push_back(new Bullet450SMC(projLeft_x, projLeft_y, 0, -1));
                projectiles_.push_back(new Bullet450SMC(projRight_x, projRight_y, 0, -1));
        }
        shootCooldown_ = time.elapsed();
    }
}

void Bakoom::moveEnemies()
{
    // uniform movement
    if(enemyMovementTimer_ >= 20)        // same as == 20
    {
        for(int i = 0; i < enemies_.size(); i++)
        {
            if(!enemies_.at(i)->movesRandomly())
            {
                int currentXdir = enemies_.at(i)->getXdir();
                int currentYdir = enemies_.at(i)->getYdir();
                enemies_.at(i)->setXdir(currentYdir);
                enemies_.at(i)->setYdir(-1*currentXdir);
            }
        }
        enemyMovementTimer_ = 0;
    }
    else
        enemyMovementTimer_ ++;
    if(enemyMovementTimer_ <= 10)
        for(int i = 0; i < enemies_.size(); i++)
            enemies_.at(i)->autoMove();
    // random movmement
    for(int i = 0; i < enemies_.size(); i++)
    {
        if(enemies_.at(i)->movesRandomly())
        {
            if(rand() % 1000 == 0)
            {
                int directionIndex = rand() % 8;
                enemies_.at(i)->setXdir(x_directions[directionIndex]);
                enemies_.at(i)->setYdir(y_directions[directionIndex]);
            }
            if(enemies_.at(i)->getRect().left() <= 0 || enemies_.at(i)->getRect().right() >= windowWidth)
            {
                enemies_.at(i)->modifyX(-50*enemies_.at(i)->getXdir());
                enemies_.at(i)->setXdir(-1*enemies_.at(i)->getXdir());
            }
            if(enemies_.at(i)->getRect().top() <= 0 || enemies_.at(i)->getRect().bottom() >= 300)
            {
                enemies_.at(i)->modifyY(-50*enemies_.at(i)->getYdir());
                enemies_.at(i)->setYdir(-1*enemies_.at(i)->getYdir());
            }
            enemies_.at(i)->autoMove();
        }
    }
}

void Bakoom::createEnemyProjectiles()
{
    for(int i = 0; i < enemies_.size(); i++)
        if(rand()%1000 < enemies_.at(i)->getFireRate())
        {
            int proj_x = enemies_.at(i)->getRect().x()+enemies_.at(i)->getRect().width()/2;
            int proj_y = enemies_.at(i)->getRect().y();
            int proj_xdir = 0;
            int proj_ydir = 1;
            if(enemies_.at(i)->movesRandomly())
            {
                if(player_ ->getRect().x() > enemies_.at(i)->getRect().x()+player_ ->getRect().width())
                    proj_xdir = 1;
                else if(player_ ->getRect().x() < enemies_.at(i)->getRect().x()-player_ ->getRect().width())
                    proj_xdir = -1;
                else
                    proj_xdir = 0;
            }
            switch(enemies_.at(i)->getProjectile())
            {
                case 0 : break;     // no projectile
                case 1 : projectiles_.push_back(new Vector(proj_x, proj_y, proj_xdir, proj_ydir)); break;
                case 2 : projectiles_.push_back(new Disk(proj_x, proj_y, proj_xdir, proj_ydir)); break;
                case 3 : projectiles_.push_back(new Bead(proj_x, proj_y, proj_xdir, proj_ydir)); break;
                default : projectiles_.push_back(new Bead(proj_x, proj_y, proj_xdir, proj_ydir)); break;
            }
        }
}

void Bakoom::checkCollision()
{
    for(int i = 0; i < projectiles_.size(); i++)
    {
        // kill projectiles that collide with bubble shield
        if(projectiles_.at(i)->isEnemyProjectile() && bubbleShield_->isActivated() && projectiles_.at(i)->getRect().intersects(player_ ->getRect()))
            projectiles_.at(i)->setIsDead(true);
        else if(projectiles_.at(i)->isEnemyProjectile())
        {
            if(projectiles_.at(i)->getRect().intersects(player_ ->getRect()))        // collide with enemy projectile
            {
                player_ ->modifyHealth(-1*projectiles_.at(i)->getDamage());            // damage player
                projectiles_.at(i)->setIsDead(true);
            }
        }
        else
        {
            for(int j = 0; j < enemies_.size(); j++)                                // enemy collides with player projectile
                if(!enemies_.at(j)->isDead() && projectiles_.at(i)->getRect().intersects(enemies_.at(j)->getRect()))
                {
                    enemies_.at(j)->modifyHealth(-1*projectiles_.at(i)->getDamage());    // damage enemy
                    // explosive?
                    if(projectiles_.at(i)->isExplosive())
                        for(int k = 0; k < enemies_.size(); k++)        // damage all enemies in vicinity
                        {
                            int distance = distanceBetween(projectiles_.at(i)->getRect().x(),projectiles_.at(i)->getRect().y(),
                                                           enemies_.at(k)->getRect().x(),enemies_.at(k)->getRect().y());
                            if(distance <= areaOfEffectRadius)
                                enemies_.at(k)->modifyHealth(-1*projectiles_.at(i)->getDamage()*20/distance);
                        }
                    if(!projectiles_.at(i)->isInvincible()) projectiles_.at(i)->setIsDead(true);
                }
        }
        if(player_ ->getHealth() <= 0)
            stopGame();
    }
    // dead enemies?
    for(int i = 0; i < enemies_.size(); i++)
    {
        if(enemies_.at(i)->getHealth() <= 0)                                // kill enemy if health <= 0
        {
            enemies_.at(i)->setIsDead(true);
            score += enemies_.at(i)->getReward();
            credits += enemies_.at(i)->getReward()/3;
            if(rand() % 7 == 0) credits_.push_back(new Credit(enemies_.at(i)->getRect().x(), enemies_.at(i)->getRect().y()));
        }
    }
    // only worry about medipak collision if player is not at full health
    if(player_ ->getHealth() < player_ ->getMaxHealth())
        for(int i = 0; i < medipaks_.size(); i++)
        {
            if(medipaks_.at(i)->getRect().intersects(player_ ->getRect()))
            {
                player_ ->modifyHealth(medipakHealAmount_);
                medipaks_.at(i)->setIsDead(true);
            }
        }
    // credit collision
    for(int i = 0; i < credits_.size(); i++)
    {
        if(credits_.at(i)->getRect().intersects(player_ ->getRect()))
        {
            credits += level*(rand() % (maxCreditAmount_-minCreditAmount_+1) + minCreditAmount_);
            credits_.at(i)->setIsDead(true);
        }
    }
}

void Bakoom::checkOutOfBounds()            // delete objects outside of window
{
    for(int i = 0; i < projectiles_.size(); i++)
    {
        int proj_x = projectiles_.at(i)->getRect().x();
        int proj_y = projectiles_.at(i)->getRect().y();
        if(proj_y > (windowHeight-lowerUIHeight) || proj_y < 0 || proj_x > windowWidth || proj_x < 0)
            projectiles_.at(i)->setIsDead(true);
    }
    for(int i = 0; i < medipaks_.size(); i++)
    {
        int medi_x = medipaks_.at(i)->getRect().x();
        int medi_y = medipaks_.at(i)->getRect().y();
        if(medi_y > (windowHeight-lowerUIHeight) || medi_y < 0 || medi_x > windowWidth || medi_x < 0)
            medipaks_.at(i)->setIsDead(true);
    }
    for(int i = 0; i < credits_.size(); i++)
    {
        int cred_x = credits_.at(i)->getRect().x();
        int cred_y = credits_.at(i)->getRect().y();
        if(cred_y > (windowHeight-lowerUIHeight) || cred_y < 0 || cred_x > windowWidth || cred_x < 0)
            credits_.at(i)->setIsDead(true);
    }
    for(int i = 0; i < scenery_.size(); i++)
    {
        int scen_y = scenery_.at(i)->getRect().y();
        if(scen_y > windowHeight-lowerUIHeight)
            scenery_.at(i)->setIsDead(true);
    }
    for(int i = 0; i < enemies_.size(); i++)        // it's unlikely that enemies will go out of bounds, this is just in case
    {
        int enem_x = enemies_.at(i)->getRect().y();
        int enem_y = enemies_.at(i)->getRect().x();
        if(enem_y > (windowHeight-lowerUIHeight+20) || enem_y < -20 || enem_x > windowWidth+20 || enem_x < -20)
            enemies_.at(i)->setIsDead(true);
    }
}

void Bakoom::autoHeal()
{
    if(time.elapsed() - autoHealTimer_ >= autoHealCooldown_)
    {
        if(player_ ->getHealth() < player_ ->getMaxHealth()) player_ ->modifyHealth(autoHealAmount_);
        if(player_ ->getHealth() > player_ ->getMaxHealth()) player_ ->setHealth(player_ ->getMaxHealth());
        autoHealTimer_ = time.elapsed();
    }
}

void Bakoom::createRandomScenery()
{
    if(rand() % 100 < islandQuality)    // probability of generating island
    {
        int speed = 2;
        int scen_x = rand()%windowWidth;
        int islandTypeA = rand()%10;
        int islandTypeB = rand()%10;
        scenery_.push_back(new Scenery(scen_x,-100,speed,islandTypeA,rand()%360));
        scenery_.push_back(new Scenery(scen_x+rand()%40,-100-rand()%40,speed,islandTypeB,rand()%360));
        if(rand() % 5 < 1)              // 3 islands?
        {
            int islandTypeC = rand()%10;
            scenery_.push_back(new Scenery(scen_x+rand()%80,-100-rand()%80,speed,islandTypeC,rand()%360));
        }
        if(rand() % 10 < 1)             // 4 islands!
        {
            int islandTypeD = rand()%10;
            scenery_.push_back(new Scenery(scen_x+rand()%150,-100-rand()%150,speed,islandTypeD,rand()%360));
        }
    }
}

// make sure to check enemies size > 0 (more than 0 enemies) before calling this function or it will cause exception
Enemy* Bakoom::nearestEnemyTo(int x, int y)
{
    int shortestDistance = distanceBetween(x, y, enemies_.at(0)->getRect().x(), enemies_.at(0)->getRect().y());
    int nearestEnemyIndex = 0;
    for(int i = 0; i < enemies_.size(); i++)
    {
        int currentEnemyDistance = distanceBetween(x, y, enemies_.at(i)->getRect().x(), enemies_.at(i)->getRect().y());
        if(currentEnemyDistance < shortestDistance)
        {
            shortestDistance = currentEnemyDistance;
            nearestEnemyIndex = i;
        }
    }
    return enemies_.at(nearestEnemyIndex);
}

// returns distance between (x1,y1) and (y2,x2)
double Bakoom::distanceBetween(int x1, int y1, int x2, int y2)
{
    return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

void Bakoom::deleteDead()
{
    enemies_.erase(std::remove_if(enemies_.begin(),enemies_.end(),objectIsDead),enemies_.end());
    projectiles_.erase(std::remove_if(projectiles_.begin(),projectiles_.end(),objectIsDead),projectiles_.end());
    medipaks_.erase(std::remove_if(medipaks_.begin(),medipaks_.end(),objectIsDead),medipaks_.end());
    credits_.erase(std::remove_if(credits_.begin(),credits_.end(),objectIsDead),credits_.end());
    scenery_.erase(std::remove_if(scenery_.begin(),scenery_.end(),objectIsDead),scenery_.end());
}

void Bakoom::spawnMedipaks()
{
    if(rand() % 10000 < 5)
        medipaks_.push_back(new Medipak(rand() % windowWidth, 5));
}

#include "shop.h"
#include "global.h"
#include <QApplication>
#include <iostream>

using namespace std;

Shop::Shop()
{
    selectedShopItem_ = 0;
    timerId_ = startTimer(10);

    const int tier1LevelRequirement = 0;
    const int tier2LevelRequirement = 2;
    const int tier3LevelRequirement = 3;
    const int tier4LevelRequirement = 4;
    const int tier5LevelRequirement = 5;

    unlocked_[0] = (level >= tier1LevelRequirement);
    unlocked_[1] = (level >= tier1LevelRequirement);
    unlocked_[2] = (level >= tier1LevelRequirement);
    unlocked_[3] = (level >= tier1LevelRequirement);
    unlocked_[4] = (level >= tier2LevelRequirement);
    unlocked_[5] = (level >= tier2LevelRequirement);
    unlocked_[6] = (level >= tier2LevelRequirement);
    unlocked_[7] = (level >= tier2LevelRequirement);
    unlocked_[8] = (level >= tier3LevelRequirement);
    unlocked_[9] = (level >= tier3LevelRequirement);
    unlocked_[10] = (level >= tier3LevelRequirement);
    unlocked_[11] = (level >= tier3LevelRequirement);
    unlocked_[12] = (level >= tier4LevelRequirement);
    unlocked_[13] = (level >= tier4LevelRequirement);
    unlocked_[14] = (level >= tier4LevelRequirement);
    unlocked_[15] = (level >= tier4LevelRequirement);
    unlocked_[16] = (level >= tier5LevelRequirement);
    unlocked_[17] = (level >= tier5LevelRequirement);
    unlocked_[18] = (level >= tier5LevelRequirement);
    unlocked_[19] = (level >= tier5LevelRequirement);

    costs_[0] = 75;         // shield
    costs_[1] = 100;        // bullet 25mm
    costs_[2] = 175;        // max shield
    costs_[3] = 220;        // gatling guns
    costs_[4] = 360;        // laser rifle
    costs_[5] = 130;        // red laser
    costs_[6] = 170;        // yellow laser
    costs_[7] = 220;        // blue laser
    costs_[8] = 380;        // missile launcher
    costs_[9] = 310;        // hydra missile
    costs_[10] = 1250;      // mini nuke
    costs_[11] = 165;       // area of effect
    costs_[12] = 540;       // plasma cannon
    costs_[13] = 390;       // plasma spike
    costs_[14] = 1420;      // plasma bomb
    costs_[15] = 5000;      // autorepair
    costs_[16] = 730;       // fission battery
    costs_[17] = 600;      // bubble shield
    costs_[18] = 2330;      // tesla coil
    costs_[19] = 2770;      // railgun
}

Shop::~Shop()
{
}

void Shop::timerEvent(QTimerEvent *event)
{
    repaint();
}

void Shop::paintEvent(QPaintEvent *event)
{
    int const offset = 110;
    QPainter painter(this);
    QImage shopTitle;
    QImage shopItem;
    QImage shopItemSelection;
    QImage tierTitle;
    int tierTitle_x, tierTitle_y;
    int shopItem_x, shopItem_y;
    int stats_x, stats_y;
    int itemIndex;
    int tierLevelRequirement;
    QFont statsFont("Courier New", 10, QFont::DemiBold);
    QColor notEnoughCredits = qRgb(255, 0, 0);
    notEnoughCredits.setAlpha(75);
    QColor outOfStock = qRgb(36, 36, 36);
    outOfStock.setAlpha(200);

    // Title
    shopTitle.load(":img/title_thundershop.png");
    painter.drawImage((largeWindowWidth-shopTitle.rect().width())/2, shopTitle.rect().height()/2, shopTitle);

    shopItemSelection.load(":img/buy_selection.png");

    // TIER 1
    tierTitle.load(":img/title_tier1.png");
    tierTitle_x = (windowWidth-375)/2; tierTitle_y = shopTitle.rect().height()*2;
    painter.drawImage(tierTitle_x, tierTitle_y, tierTitle);
    itemIndex = 0;
    shopItem.load(":img/buy_shield.png");
    shopItem_x = (windowWidth-390)/2; shopItem_y = shopTitle.rect().height()*3;
    painter.drawImage(shopItem_x, shopItem_y, shopItem);
    if(credits < costs_[itemIndex]) { painter.setBrush(notEnoughCredits); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    if(selectedShopItem_ == itemIndex) painter.drawImage(shopItem_x, shopItem_y, shopItemSelection);
    itemIndex++;
    shopItem.load(":img/buy_bullet25mm.png");
    shopItem_y += offset;
    painter.drawImage(shopItem_x, shopItem_y, shopItem);
    if(hasItem[itemIndex]) { painter.setBrush(outOfStock); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    else if(credits < costs_[itemIndex]) { painter.setBrush(notEnoughCredits); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    if(selectedShopItem_ == itemIndex) painter.drawImage(shopItem_x, shopItem_y, shopItemSelection);
    itemIndex++;
    shopItem.load(":img/buy_maxShield.png");
    shopItem_y += offset;
    painter.drawImage(shopItem_x, shopItem_y, shopItem);
    if(credits < costs_[itemIndex]) { painter.setBrush(notEnoughCredits); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    if(selectedShopItem_ == itemIndex) painter.drawImage(shopItem_x, shopItem_y, shopItemSelection);
    itemIndex++;
    shopItem.load(":img/buy_gatlingGuns.png");
    shopItem_y += offset;
    painter.drawImage(shopItem_x, shopItem_y, shopItem);
    if(hasItem[itemIndex]) { painter.setBrush(outOfStock); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    else if(credits < costs_[itemIndex]) { painter.setBrush(notEnoughCredits); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    if(selectedShopItem_ == itemIndex) painter.drawImage(shopItem_x, shopItem_y, shopItemSelection);
    itemIndex++;

    // TIER 2
    tierTitle.load(":img/title_tier2.png");
    tierTitle_x += offset;
    painter.drawImage(tierTitle_x, tierTitle_y, tierTitle);
    shopItem_x += offset; shopItem_y = shopTitle.rect().height()*3;
    if(unlocked_[itemIndex]) shopItem.load(":img/buy_laserRifle.png");
    else shopItem.load(":img/buy_locked.png");
    painter.drawImage(shopItem_x, shopItem_y, shopItem);
    if(hasItem[itemIndex]) { painter.setBrush(outOfStock); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    else if(credits < costs_[itemIndex]) { painter.setBrush(notEnoughCredits); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    if(selectedShopItem_ == itemIndex) painter.drawImage(shopItem_x, shopItem_y, shopItemSelection);
    itemIndex++;
    if(unlocked_[itemIndex] && hasItem[4]) shopItem.load(":img/buy_redLaser.png");
    else shopItem.load(":img/buy_locked.png");
    shopItem_y += offset;
    painter.drawImage(shopItem_x, shopItem_y, shopItem);
    if(hasItem[itemIndex]) { painter.setBrush(outOfStock); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    else if(credits < costs_[itemIndex]) { painter.setBrush(notEnoughCredits); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    if(selectedShopItem_ == itemIndex) painter.drawImage(shopItem_x, shopItem_y, shopItemSelection);
    itemIndex++;
    if(unlocked_[itemIndex] && hasItem[4]) shopItem.load(":img/buy_yellowLaser.png");
    else shopItem.load(":img/buy_locked.png");
    shopItem_y += offset;
    painter.drawImage(shopItem_x, shopItem_y, shopItem);
    if(hasItem[itemIndex]) { painter.setBrush(outOfStock); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    else if(credits < costs_[itemIndex]) { painter.setBrush(notEnoughCredits); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    if(selectedShopItem_ == itemIndex) painter.drawImage(shopItem_x, shopItem_y, shopItemSelection);
    itemIndex++;
    if(unlocked_[itemIndex] && hasItem[4]) shopItem.load(":img/buy_blueLaser.png");
    else shopItem.load(":img/buy_locked.png");
    shopItem_y += offset;
    painter.drawImage(shopItem_x, shopItem_y, shopItem);
    if(hasItem[itemIndex]) { painter.setBrush(outOfStock); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    else if(credits < costs_[itemIndex]) { painter.setBrush(notEnoughCredits); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    if(selectedShopItem_ == itemIndex) painter.drawImage(shopItem_x, shopItem_y, shopItemSelection);
    itemIndex++;

    // TIER 3
    tierTitle.load(":img/title_tier3.png");
    tierTitle_x += offset;
    painter.drawImage(tierTitle_x, tierTitle_y, tierTitle);
    shopItem_x += offset; shopItem_y = shopTitle.rect().height()*3;
    if(unlocked_[itemIndex]) shopItem.load(":img/buy_missileLauncher.png");
    else shopItem.load(":img/buy_locked.png");
    painter.drawImage(shopItem_x, shopItem_y, shopItem);
    if(hasItem[itemIndex]) { painter.setBrush(outOfStock); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    else if(credits < costs_[itemIndex]) { painter.setBrush(notEnoughCredits); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    if(selectedShopItem_ == itemIndex) painter.drawImage(shopItem_x, shopItem_y, shopItemSelection);
    itemIndex++;
    if(unlocked_[itemIndex] && hasItem[8]) shopItem.load(":img/buy_hydraMissile.png");
    else shopItem.load(":img/buy_locked.png");
    shopItem_y += offset;
    painter.drawImage(shopItem_x, shopItem_y, shopItem);
    if(hasItem[itemIndex]) { painter.setBrush(outOfStock); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    else if(credits < costs_[itemIndex]) { painter.setBrush(notEnoughCredits); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    if(selectedShopItem_ == itemIndex) painter.drawImage(shopItem_x, shopItem_y, shopItemSelection);
    itemIndex++;
    if(unlocked_[itemIndex] && hasItem[8]) shopItem.load(":img/buy_miniNuke.png");
    else shopItem.load(":img/buy_locked.png");
    shopItem_y += offset;
    painter.drawImage(shopItem_x, shopItem_y, shopItem);
    if(hasItem[itemIndex]) { painter.setBrush(outOfStock); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    else if(credits < costs_[itemIndex]) { painter.setBrush(notEnoughCredits); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    if(selectedShopItem_ == itemIndex) painter.drawImage(shopItem_x, shopItem_y, shopItemSelection);
    itemIndex++;
    if(unlocked_[itemIndex]) shopItem.load(":img/buy_areaOfEffect.png");
    else shopItem.load(":img/buy_locked.png");
    shopItem_y += offset;
    painter.drawImage(shopItem_x, shopItem_y, shopItem);
    if(hasItem[itemIndex]) { painter.setBrush(outOfStock); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    else if(credits < costs_[itemIndex]) { painter.setBrush(notEnoughCredits); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    if(selectedShopItem_ == itemIndex) painter.drawImage(shopItem_x, shopItem_y, shopItemSelection);
    itemIndex++;

    // TIER 4
    tierTitle.load(":img/title_tier4.png");
    tierTitle_x += offset;
    painter.drawImage(tierTitle_x, tierTitle_y, tierTitle);
    shopItem_x += offset; shopItem_y = shopTitle.rect().height()*3;
    if(unlocked_[itemIndex]) shopItem.load(":img/buy_plasmaCannon.png");
    else shopItem.load(":img/buy_locked.png");
    painter.drawImage(shopItem_x, shopItem_y, shopItem);
    if(hasItem[itemIndex]) { painter.setBrush(outOfStock); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    else if(credits < costs_[itemIndex]) { painter.setBrush(notEnoughCredits); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    if(selectedShopItem_ == itemIndex) painter.drawImage(shopItem_x, shopItem_y, shopItemSelection);
    itemIndex++;
    if(unlocked_[itemIndex] && hasItem[12]) shopItem.load(":img/buy_plasmaSpike.png");
    else shopItem.load(":img/buy_locked.png");
    shopItem_y += offset;
    painter.drawImage(shopItem_x, shopItem_y, shopItem);
    if(hasItem[itemIndex]) { painter.setBrush(outOfStock); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    else if(credits < costs_[itemIndex]) { painter.setBrush(notEnoughCredits); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    if(selectedShopItem_ == itemIndex) painter.drawImage(shopItem_x, shopItem_y, shopItemSelection);
    itemIndex++;
    if(unlocked_[itemIndex] && hasItem[12]) shopItem.load(":img/buy_plasmaBomb.png");
    else shopItem.load(":img/buy_locked.png");
    shopItem_y += offset;
    painter.drawImage(shopItem_x, shopItem_y, shopItem);
    if(hasItem[itemIndex]) { painter.setBrush(outOfStock); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    else if(credits < costs_[itemIndex]) { painter.setBrush(notEnoughCredits); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    if(selectedShopItem_ == itemIndex) painter.drawImage(shopItem_x, shopItem_y, shopItemSelection);
    itemIndex++;
    if(unlocked_[itemIndex]) shopItem.load(":img/buy_autoRepair.png");
    else shopItem.load(":img/buy_locked.png");
    shopItem_y += offset;
    painter.drawImage(shopItem_x, shopItem_y, shopItem);
    if(hasItem[itemIndex]) { painter.setBrush(outOfStock); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    else if(credits < costs_[itemIndex]) { painter.setBrush(notEnoughCredits); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    if(selectedShopItem_ == itemIndex) painter.drawImage(shopItem_x, shopItem_y, shopItemSelection);
    itemIndex++;

    // TIER 5
    tierTitle.load(":img/title_tier5.png");
    tierTitle_x += offset;
    painter.drawImage(tierTitle_x, tierTitle_y, tierTitle);
    shopItem_x += offset; shopItem_y = shopTitle.rect().height()*3;
    if(unlocked_[itemIndex]) shopItem.load(":img/buy_fissionBattery.png");
    else shopItem.load(":img/buy_locked.png");
    painter.drawImage(shopItem_x, shopItem_y, shopItem);
    if(hasItem[itemIndex]) { painter.setBrush(outOfStock); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    else if(credits < costs_[itemIndex]) { painter.setBrush(notEnoughCredits); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    if(selectedShopItem_ == itemIndex) painter.drawImage(shopItem_x, shopItem_y, shopItemSelection);
    itemIndex++;
    if(unlocked_[itemIndex]) shopItem.load(":img/buy_bubbleShield.png");
    else shopItem.load(":img/buy_locked.png");
    shopItem_y += offset;
    painter.drawImage(shopItem_x, shopItem_y, shopItem);
    if(hasItem[itemIndex]) { painter.setBrush(outOfStock); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    else if(credits < costs_[itemIndex]) { painter.setBrush(notEnoughCredits); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    if(selectedShopItem_ == itemIndex) painter.drawImage(shopItem_x, shopItem_y, shopItemSelection);
    itemIndex++;
    if(unlocked_[itemIndex] && hasItem[16]) shopItem.load(":img/buy_teslaCoil.png");
    else shopItem.load(":img/buy_locked.png");
    shopItem_y += offset;
    painter.drawImage(shopItem_x, shopItem_y, shopItem);
    if(hasItem[itemIndex]) { painter.setBrush(outOfStock); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    else if(credits < costs_[itemIndex]) { painter.setBrush(notEnoughCredits); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    if(selectedShopItem_ == itemIndex) painter.drawImage(shopItem_x, shopItem_y, shopItemSelection);
    itemIndex++;
    if(unlocked_[itemIndex] && hasItem[16]) shopItem.load(":img/buy_railgun.png");
    else shopItem.load(":img/buy_locked.png");
    shopItem_y += offset;
    painter.drawImage(shopItem_x, shopItem_y, shopItem);
    if(hasItem[itemIndex]) { painter.setBrush(outOfStock); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    else if(credits < costs_[itemIndex]) { painter.setBrush(notEnoughCredits); painter.drawRect(shopItem_x, shopItem_y, shopItem.rect().width(), shopItem.rect().height()); }
    if(selectedShopItem_ == itemIndex) painter.drawImage(shopItem_x, shopItem_y, shopItemSelection);
    itemIndex++;

    // other info
    stats_x = (windowWidth-375)/2; stats_y = shopItem_y + 1.25*offset;
    painter.setFont(statsFont);
    painter.setPen(Qt::white);
    painter.drawText(stats_x,stats_y,200,16,Qt::AlignLeft,"Shields: " + QString::number(shield) + "/" + QString::number(maxShield));
    stats_x += 200;
    painter.setPen(Qt::yellow);
    painter.drawText(stats_x,stats_y,200,16,Qt::AlignLeft,"Credits: " + QString::number(credits));
    stats_x += 150;
    painter.setPen(Qt::red);
    painter.drawText(stats_x,stats_y,200,16,Qt::AlignLeft,"([TAB] to continue)");
}

void Shop::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
        case Qt::Key_W:
            if(selectedShopItem_%4 != 0) selectedShopItem_ -= 1;
            break;
        case Qt::Key_S:
            if((selectedShopItem_+1)%4 != 0) selectedShopItem_ += 1;
            break;
        case Qt::Key_A:
            if(selectedShopItem_ >= 4) selectedShopItem_ -= 4;
            break;
        case Qt::Key_D:
            if(selectedShopItem_ <= 15) selectedShopItem_ += 4;
            break;
        case Qt::Key_Space:
            buySelectedItem();
            break;
        case Qt::Key_Tab:
            qApp->exit();
            break;
        case Qt::Key_Escape:
            restarting = true;
            qApp->exit();
            break;
        default:
            QWidget::keyPressEvent(event);
    }
}

void Shop::buySelectedItem()
{
    if(unlocked_[selectedShopItem_] && credits >= costs_[selectedShopItem_])      // item is unlocked and can be bought
    {
        if(selectedShopItem_ == 0)
            if(shield < maxShield)
                if(shield <= maxShield - 50) shield += 50;
                else shield = maxShield;
            else
                return;
        else if(selectedShopItem_ == 2) { maxShield += 100; shield += 100; }
        else if(hasItem[selectedShopItem_]) return;
        else if(selectedShopItem_ >= 5 && selectedShopItem_ <= 7 && !hasItem[4]) return;
        else if(selectedShopItem_ >= 9 && selectedShopItem_ <= 10 && !hasItem[8]) return;
        else if(selectedShopItem_ >= 13 && selectedShopItem_ <= 14 && !hasItem[12]) return;
        else if(selectedShopItem_ >= 18 && selectedShopItem_ <= 19 && !hasItem[16]) return;
        else hasItem[selectedShopItem_] = true;
        credits -= costs_[selectedShopItem_];
        if(hasItem[11]) areaOfEffectRadius = 160;
        if(hasItem[16]) maxPower = 175;
        if(hasItem[17]) maxPower = 280;
    }
}

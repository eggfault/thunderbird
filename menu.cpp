#include <QApplication>
#include <iostream>
#include "menu.h"
#include "global.h"

Menu::Menu()
{
    timerId_ = startTimer(10);
    selected_ = 0;
    displayInstructions_ = false;
}

Menu::~Menu()
{

}

void Menu::randomLightning()
{
    if(rand() % 2 == 0)
    {
        int lightningFX_x1 = rand() % largeWindowWidth;
        int lightningFX_y1 = rand() % largeWindowHeight;
        int lightningFX_x2 = rand() % 30 - rand() % 30 + lightningFX_x1;
        int lightningFX_y2 = rand() % 100 + 100;
        lightningFX_.push_back(new LightningFX(lightningFX_x1, lightningFX_y1, lightningFX_x2, lightningFX_y2));
    }
}

void Menu::timerEvent(QTimerEvent *event)
{
    randomLightning();
    repaint();
    lightningFX_.clear();
}

void Menu::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    // draw background
    for(int i = 0; i < lightningFX_.size(); i++)
        painter.drawImage(lightningFX_.at(i)->getRect(), lightningFX_.at(i)->getImage());
    // draw menu
    int draw_x, draw_y;
    QImage menuTitle;
    menuTitle.load(":img/menu_title.png");
    draw_x = largeWindowWidth/2-menuTitle.rect().width()/2;
    draw_y = menuTitle.rect().height();
    painter.drawImage(draw_x, draw_y, menuTitle);
    QImage menuItem;
    menuItem.load(":img/menu_play.png");
    if(selected_ == 0)
        menuItem.load(":img/menu_play_selected.png");
    draw_x = largeWindowWidth/2-menuItem.rect().width()/2;
    draw_y += 200;
    painter.drawImage(draw_x, draw_y, menuItem);
    menuItem.load(":img/menu_instructions.png");
    if(selected_ == 1)
        menuItem.load(":img/menu_instructions_selected.png");
    draw_x = largeWindowWidth/2-menuItem.rect().width()/2;
    draw_y += 75;
    painter.drawImage(draw_x, draw_y, menuItem);
    menuItem.load(":img/menu_settings.png");
    if(selected_ == 2)
        menuItem.load(":img/menu_settings_selected.png");
    draw_x = largeWindowWidth/2-menuItem.rect().width()/2;
    draw_y += 75;
    painter.drawImage(draw_x, draw_y, menuItem);
    menuItem.load(":img/menu_quit.png");
    if(selected_ == 3)
        menuItem.load(":img/menu_quit_selected.png");
    draw_x = largeWindowWidth/2-menuItem.rect().width()/2;
    draw_y += 75;
    painter.drawImage(draw_x, draw_y, menuItem);
    // draw quality
    QFont qualityFont("Arial", 10, QFont::DemiBold);
    painter.setPen(Qt::white);
    painter.setFont(qualityFont);
    painter.drawText(10,largeWindowHeight-30,200,24,Qt::AlignLeft,"Quality: " + QString::number(islandQuality));
    // draw name
    painter.drawText(largeWindowWidth-95,largeWindowHeight-30,100,24,Qt::AlignLeft,"George Li");
    // draw instructions
    QImage instructions; instructions.load(":img/instructions.png");
    if(displayInstructions_)
        painter.drawImage(0,0,instructions);
}

void Menu::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
        case Qt::Key_W:
            if(selected_ > 0)
                selected_--;
            break;
        case Qt::Key_S:
            if(selected_ < 4)
                selected_++;
            break;
        case Qt::Key_A:
            if(selected_ > 0)
                selected_--;
            break;
        case Qt::Key_D:
            if(selected_ < 3)
                selected_++;
            break;
        case Qt::Key_Space:
            if(selected_ == 0)
                qApp->exit();
            else if(selected_ == 1)
                displayInstructions_ = !displayInstructions_;
            else if(selected_ == 2)
            {
                islandQuality++;
                if(islandQuality == 11)
                    islandQuality = 0;
            }
            else if(selected_ == 3)
                exit(0);
            break;
        case Qt::Key_Tab:
            if(selected_ == 1)
                displayInstructions_ = false;
            else
                qApp->exit();
            break;
        case Qt::Key_Escape:
            if(selected_ == 1)
                displayInstructions_ = false;
            else
                exit(0);
        default:
            QWidget::keyPressEvent(event);
    }
}

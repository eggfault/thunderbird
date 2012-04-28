#include "bakoom.h"
#include "shop.h"
#include "menu.h"
#include "global.h"
#include <QDesktopWidget>
#include <QApplication>
#include <ctime>
#include <iostream>

using namespace std;

int windowWidth = 480;
int windowHeight = 640;
int largeWindowWidth = 640;
int largeWindowHeight = 640;
int lowerUIHeight = 80;
int credits = 200;
int score;
int level;
int shield = 100;
int maxShield = 100;
int maxPower = 100;
int areaOfEffectRadius = 100;
bool hasItem[20];
bool restarting;
int islandQuality = 6;

int menu(int argc, char *argv[]);
int shop(int argc, char *argv[]);
int playLevel(int argc, char *argv[], vector<Enemy *> wave);
void initializeHasItem();
void centerRoom(QWidget &widget, int roomWidth, int roomHeight);
void initializeEnemies(vector<vector<Enemy *> > &vectorOfWaves);

void initializeHasItem()
{
    hasItem[0] = true;
    for(int i = 1; i < 20; i ++)
        hasItem[i] = false;
}

void centerRoom(QWidget &widget, int roomWidth, int roomHeight)
{
	int x, y;
	int screenWidth;
	int screenHeight;
	QDesktopWidget *desktop = QApplication::desktop();
	screenWidth = desktop->width();
	screenHeight = desktop->height();
    x = (screenWidth - roomWidth)/2;
    y = (screenHeight - roomHeight)/2;
    widget.setGeometry(x, y, roomWidth, roomHeight);
    widget.setFixedSize(roomWidth, roomHeight);
}

int menu(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Menu room;
    room.setWindowTitle("Thunderbird");
    room.setStyleSheet("background-color: rgb(0,0,40)");//(29,51,130)");
    room.show();
    centerRoom(room, largeWindowWidth, largeWindowHeight);
    return app.exec();
}

int shop(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Shop room;
    room.setWindowTitle("Thundershop");
    room.setStyleSheet("background-color: rgb(9,21,74)");
    room.show();
    centerRoom(room, largeWindowWidth, largeWindowHeight);
    return app.exec();
}

int playLevel(int argc, char *argv[], vector<Enemy*> wave)
{
    QApplication app(argc, argv);
    Bakoom room(wave);
    room.setWindowTitle("Thunderbird");
    room.setStyleSheet("background-color: rgb(9,21,74)");
    room.show();
    centerRoom(room, windowWidth, windowHeight);
    return app.exec();
}

void initializeEnemies(vector<vector<Enemy*> > &vectorOfWaves)
{
    vectorOfWaves.clear();
    vector<Enemy*> wave;
    // level 1
    for(int j = 25; j < 425; j += 50)
        for(int k = 50; k < 300; k += 50)
            wave.push_back(new Scout(j, k));
    vectorOfWaves.push_back(wave);
    wave.clear();
    // level 2
    for(int j = 25; j < 425; j += 50)
        for(int k = 50; k < 300; k += 50)
            wave.push_back(new Fighter(j, k));
    vectorOfWaves.push_back(wave);
    wave.clear();
    // level 3
    for(int j = 25; j < 425; j += 50)
        for(int k = 50; k < 300; k += 50)
            wave.push_back(new Jackal(j, k));
    vectorOfWaves.push_back(wave);
    wave.clear();
    // level 4
    for(int j = 25; j < 425; j += 100)
        for(int k = 50; k < 350; k += 100)
            wave.push_back(new Dragoon(j, k));
    vectorOfWaves.push_back(wave);
    wave.clear();
    // level 5
    for(int j = 25; j < 425; j += 50)
        for(int k = 50; k < 300; k += 50)
            wave.push_back(new Predator(j, k));
    vectorOfWaves.push_back(wave);
    wave.clear();
    // level 6
    wave.push_back(new Carrier(windowWidth/4,50));
    wave.push_back(new Carrier(windowWidth/2,50));
    vectorOfWaves.push_back(wave);
    wave.clear();
    // level 7
    wave.push_back(new Eagle(windowWidth/2,80));
    vectorOfWaves.push_back(wave);
    wave.clear();
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
    vector<vector<Enemy*> > vectorOfWaves;
    initializeHasItem();

    while(true)
    {
        score = 0;
        shield = maxShield;
        maxPower = 100;
        areaOfEffectRadius = 100;
        initializeEnemies(vectorOfWaves);
        restarting = false;
        menu(argc, argv);
        for(level = 1; level <= vectorOfWaves.size(); level++)
        {
            if(restarting) break;
            playLevel(argc, argv, vectorOfWaves.at(level-1));
            if(restarting) break;
            shop(argc, argv);
        }
    }
    return 0;
}

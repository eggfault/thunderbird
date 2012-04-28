#ifndef GLOBAL_H
#define GLOBAL_H

extern int windowWidth;
extern int windowHeight;
extern int largeWindowWidth;
extern int largeWindowHeight;
extern int lowerUIHeight;
extern int shield;
extern int maxShield;
extern int credits;
extern int score;
extern int level;
extern int maxPower;
extern int areaOfEffectRadius;
extern bool hasItem[20];
extern bool restarting;
extern int islandQuality;
int const x_directions[8] = {-1,-1,0,0,1,1,1,-1};
int const y_directions[8] = {1,0,1,-1,1,-1,0,-1};

#endif

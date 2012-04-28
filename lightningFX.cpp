#include "lightningFX.h"
#include "cmath"
#include "iostream"

using namespace std;

LightningFX::LightningFX(int x1, int y1, int x2, int y2)
{
    image_.load(":img/chainLightning1.png");
    rect_ = QRect(x1,y2,image_.rect().width(),y1-y2);
    double imageAngle = 90;
    if(x2 != x1)
        imageAngle = 180+180/M_PI*atan2((y2-y1),(x2-x1));
    QTransform rotateImage; rotateImage.rotate(imageAngle);
    image_ = image_.transformed(rotateImage);
    x_ = rect_.x();
    y_ = rect_.y();
    isDead_ = false;
}

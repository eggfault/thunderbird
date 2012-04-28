#ifndef OBJECT_H
#define OBJECT_H

#include <QImage>
#include <QRect>
#include "global.h"

class Object
{
public:
	virtual QImage &getImage();
	virtual QRect getRect();
	virtual int getSpeed();
	virtual bool isDead();
	virtual void setIsDead(bool isDead);
	virtual void setRect(QRect rect);
	virtual void setXdir(int xdir);
	virtual void setYdir(int ydir);
	virtual int getXdir();
	virtual int getYdir();
	virtual void autoUpdateRect();
protected:
	QImage image_;
	QRect rect_;
	int x_;
	int y_;
	int xdir_;
	int ydir_;
	int speed_;
	bool isDead_;
};

#endif

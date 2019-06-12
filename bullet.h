#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QPoint>
#include <QPixmap>
#include "point.h"

#include "rpgobj.h"

class Bullet : public RPGObj
{
public:
    Bullet();
    ~Bullet(){}
    Point getEnd(){return _end ;}
    void setEnd(double x,double y)
    {
        _end.setPoint(x,y);
    }
    int getkind(){return _kind;}
    void setkind(int kind){_kind=kind;}

private:
    Point _start ;
    Point _end ;
    int _kind;

};

#endif // BULLET_H

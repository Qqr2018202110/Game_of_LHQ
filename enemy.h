#ifndef ENEMY_H
#define ENEMY_H

#include "rpgobj.h"

class Enemy: public RPGObj
{
public:
    Enemy(){}
    ~Enemy(){}

    void enemy_move(int direction,double steps = 1.0) ;


    double getX() {return _pos_x ;}
    double getY() {return _pos_y ;}
    void life_loss(RPGObj *r);
    void show(QPainter * painter,int x=0);

};

#endif // ENEMY_H

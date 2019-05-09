#ifndef ENEMY_H
#define ENEMY_H

#include "rpgobj.h"

class Enemy: public RPGObj
{
public:
    Enemy(){}
    ~Enemy(){}

    void enemy_move(int direction,int steps = 1) ;


    int getX() {return _pos_x ;}
    int getY() {return _pos_y ;}

};

#endif // ENEMY_H

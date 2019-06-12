#ifndef MONSTER_H
#define MONSTER_H

#include "rpgobj.h"

class Monster : public RPGObj
{
public:
    Monster(){}
    ~Monster(){}
    void move(int direction, int steps=1);
        //direction =1,2,3,4 for 上下左右
    int getX() {return _pos_x ;}
    int getY() {return _pos_y ;}
};

#endif // MONSTER_H

#ifndef SOLDIER_H
#define SOLDIER_H
#include "rpgobj.h"

class Soldier: public RPGObj
{
public:
    Soldier(){}
    ~Soldier(){}

    void soldier_move(int direction,int step = 1) ;


    int getX() {return _pos_x ;}
    int getY() {return _pos_y ;}

};

#endif // SOLDIER_H


#ifndef SOLDIER_H
#define SOLDIER_H
#include "rpgobj.h"
#include "qlabel.h"
#include"qmovie.h"

class Soldier: public RPGObj
{
public:
    Soldier(){}
    ~Soldier(){}

    void soldier_move(int direction,double step = 1) ;


    double getX() {return _pos_x ;}
    double getY() {return _pos_y ;}
    void SoldierAttack(int x,int y);
    int get_kind();
    void set_kind(int n);
    void life_loss(RPGObj *r);

private:
    int _kind=0;
};

#endif // SOLDIER_H


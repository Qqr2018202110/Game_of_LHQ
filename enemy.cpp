#include "enemy.h"

//direction =1,2,3,4 for 上下左右
void Enemy::enemy_move(int direction, double step)
{
    if ( direction == 1 )
        _pos_y -= step ;
    else if ( direction == 2 )
        _pos_y += step ;
    else if ( direction == 3 )
        _pos_x -= step ;
    else if ( direction == 4 )
        _pos_x += step ;
}

void Enemy::life_loss(RPGObj *r)
{
    const char* s=r->getType();
    int lose=0;
    if(strcmp(s,"Soldier1"))
        lose=2;
    if(strcmp(s,"Soldier2"))
        lose=4;
    if(strcmp(s,"Soldier3"))
        lose=1;
    if(strcmp(s,"Base"))
        lose=1;
    _life=_life-lose;

}

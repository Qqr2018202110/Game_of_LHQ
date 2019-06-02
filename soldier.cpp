#include "soldier.h"
#include "world.h"

//direction =1,2,3,4 for 上下左右
void Soldier::soldier_move(int direction, double step)
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

void Soldier::SoldierAttack(int x,int y)
{
    QMovie* movie = new QMovie(":/images/camEffectTarget.gif");
    QLabel* label = new QLabel;
    label->setMovie(movie);
    label->setGeometry(x,y,5,5);
    movie->start();
    label->show();
}
void Soldier::set_kind(int n)
{
    _kind=n;
}

int Soldier::get_kind()
{
   return _kind;
}

void Soldier::life_loss(RPGObj *r)
{
    const char* s=r->getType();
    int lose=0;
    if(strcmp(s,"Enemy1"))
        lose=2;
    if(strcmp(s,"Enemy2"))
        lose=4;
    if(strcmp(s,"Enemy3"))
        lose=1;
    if(strcmp(s,"Tower"))
        lose=1;
        _life=_life-lose;
}


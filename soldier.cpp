#include "soldier.h"
#include "world.h"
static const int Health_Bar_Width = 80;
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
    int lose = 0;
    int rank=r->get_rank();
    if(rank==1)
        lose=2;
    if(rank==2)
        lose=4;
    if(rank==3)
        lose=1;
        _life=_life-lose;
}

void Soldier::show(QPainter *painter, int x)
{
    painter->save();
    QPoint m_pos(this->getPosX() * 32,(this->getPosY()+0.3*x) * 32);
    QPoint healthBarPoint = m_pos + QPoint(-Health_Bar_Width / 2 + 25,  - 10);
    // 绘制血条
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, 2));
    painter->drawRect(healthBarBackRect);

    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint, QSize((double)this->getLife() / _maxlife * Health_Bar_Width, 2));
    painter->drawRect(healthBarRect);

    // 绘制偏转坐标,由中心+偏移=左上
    static const QPoint offsetPoint(32, 32);
    painter->translate(m_pos);
    //painter->rotate(m_rotationSprite);
    // 绘制敌人
    //painter->drawPixmap(offsetPoint, m_sprite);
    painter->drawImage(0,0,this->_pic);

    painter->restore();
}


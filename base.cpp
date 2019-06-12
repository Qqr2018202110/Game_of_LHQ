#include "base.h".h"
#include "world.h"
#include "rpgobj.h"
static const int Health_Bar_Width = 80;
Base::Base()
{

}

Base::~Base()
{

}

void Base::life_loss(RPGObj *r)
{
    int lose=0;
    int rank=r->get_rank();
    if(rank==1)
        lose=2;
    if(rank==2)
        lose=1;
    if(rank==3)
        lose=4;
        _life=_life-lose;
}


void Base::show(QPainter *painter, int x)
{
    painter->save();
    QPoint m_pos(this->getPosX() * 32,(this->getPosY()-0.1*x) * 32);
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

    painter->translate(m_pos);
    // 绘制敌人
    painter->drawImage(0,0,this->_pic);

    painter->restore();
}



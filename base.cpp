#include "base.h".h"
#include "world.h"
#include "rpgobj.h"

Base::Base()
{

}

Base::~Base()
{

}

void Base::onErase()
{
    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/sounds/crash.mp3"));
    player->setVolume(30);
    player->play();
}

void Base::life_loss(RPGObj *r)
{
    const char* s=r->getType();
    int lose=0;
    if(strcmp(s,"Enemy1"))
        lose=2;
    if(strcmp(s,"Enemy2"))
        lose=1;
    if(strcmp(s,"Enemy3"))
        lose=4;
        _life=_life-lose;
}

const char* Base::getType()
{
    const char*s="Base";
    return (s);
}

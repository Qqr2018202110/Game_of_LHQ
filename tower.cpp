#include "tower.h"
#include "world.h"
#include "rpgobj.h"

Tower::Tower()
{

}

Tower::~Tower()
{

}

void Tower::onErase()
{
    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/sounds/crash.mp3"));
    player->setVolume(30);
    player->play();
}

void Tower::life_loss(RPGObj *r)
{
    const char* s=r->getType();
    int lose=0;
    char* s1= "Soldier1";
    if(strcmp(s,s1))
        lose=2;
    if(strcmp(s,"Soldier2"))
        lose=1;
    if(strcmp(s,"Soldier3"))
        lose=4;
    _life=_life-lose;
}

const char* Tower::getType()
{
    const char*s="Tower";
    return (s);
}

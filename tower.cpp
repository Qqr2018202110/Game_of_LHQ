#include "tower.h"
#include "world.h"
#include "rpgobj.h"

Tower::Tower()
{

}

Tower::~Tower()
{

}

void Tower::onErase(){
    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/sounds/crash.mp3"));
    player->setVolume(30);
    player->play();
}



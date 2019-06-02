#include "rpgobj.h"
#include "world.h"
#include <iostream>

void RPGObj::initObj(string type)
{


    this->_icon = ICON::findICON(type);//这一行代码不用管，反正没问题
    QImage all;
    all.load(":/pics/objects.png");//导入一张图片，图片上有所有我们需要的图标
                                 //这就是为什么我一开始想要所有的在一张图上，这样这个函数好写，否则还要判断
    this->_pic = all.copy(QRect(_icon.getSrcX()*ICON::GRID_SIZE, _icon.getSrcY()*ICON::GRID_SIZE, _icon.getWidth()*ICON::GRID_SIZE, _icon.getHeight()*ICON::GRID_SIZE));
                                 //从导入的图片上把图标抠出来
}

//下面的代码不用管，反正是对的
void RPGObj::show(QPainter * pa)
{
    int gSize = ICON::GRID_SIZE;
    pa->drawImage(this->_pos_x*gSize,this->_pos_y*gSize,this->_pic);
}

double RPGObj::getNextX(int direction){
    switch (direction){
        case 1:
            return this->_pos_x;
        case 2:
           return this->_pos_x;
        case 3:
           return this->_pos_x-1;
        case 4:
           return this->_pos_x+1;
    }
}

double RPGObj::getNextY(int direction){
    switch (direction){
        case 1:
            return this->_pos_y - 1;
        case 2:
           return this->_pos_y + 1;
        case 3:
           return this->_pos_y;
        case 4:
           return this->_pos_y;
    }
}

void RPGObj::onErase()
{
    QMediaPlayer * player = new QMediaPlayer;
    //player->setMedia(":/sounds/2953.mp3");
    player->setMedia(QUrl("qrc:/sounds/2953.mp3"));
    player->setVolume(30);
    player->play();
}



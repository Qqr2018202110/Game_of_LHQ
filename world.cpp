#include "world.h"
#include "icon.h"
#include "rpgobj.h"
#include "soldier.h"

#include <QMediaPlayer>
#include <QTime>
#include <QTimer>

World::~World(){

}

void World::addRuins(int x, int y)
{
    RPGObj * p = new RPGObj ;
    p->initObj("ruins") ;
    p->setPosX(x) ;
    p->setPosY(y) ;

    this->_others.push_back(p) ;
}


void World::addEne1(int x,int y)
{
    if ( _qi_of_enemy > 0 )
    {
        Enemy *p = new Enemy;
        p->initObj("enemy");
        p->setPosX(x);
        p->setPosY(y);
        (*p).set_life(20);

        this->_enemy.push_back(p) ;

        _qi_of_enemy -- ;
    }
}


void World::addSol1(int x,int y)
{
    if (_qi_of_me>0)
    {
        Soldier * p = new Soldier ;
        p->initObj("soldier") ;
        p->setPosX(x) ;
        p->setPosY(y) ;
        (*p).set_life(20);

        this->_soldier.push_back(p) ;

        _qi_of_me -- ;
    }
}

bool World::can_move(Soldier* s)
{
    int x = s->getX() ; int y = s->getY() ;

    if ( x == 7 && y == 2 )
        return 0 ;
    else if ( x == 12 && y ==2 )
        return 0 ;

    vector<Tower *> v1 = this->_tower ;
    vector<Tower *>::iterator it1 ;

    for ( it1 = v1.begin() ; it1 != v1.end() ; it1++ )
    {
        int x1 = (*it1)->getPosX() ; int y1 = (*it1)->getPosY() ;

        if ( x == x1 && y == y1 + 2 )
            return 0 ;
    }



    vector<Enemy *> v2 = this->_enemy ;
    vector<Enemy *>::iterator it2 ;

    for ( it2 = v2.begin() ; it2 != v2.end() ; it2++ )
    {
        int x1 = (*it2)->getPosX() ; int y1 = (*it2)->getPosY() ;

        if ( x == x1 && y == y1 - 1 )
            return 0 ;

    }

    return 1 ;

}

bool World::can_move(Enemy* s)
{
    int x = s->getX() ; int y = s->getY() ;

    if ( x == 7 && y == 23 ) return 0 ;
    if ( x == 12 && y == 23 ) return 0 ;


    vector<Base *> v1 = this->_base ;
    vector<Base *>::iterator it1 ;

    for ( it1 = v1.begin() ; it1 != v1.end() ; it1++ )
    {
        int x1 = (*it1)->getPosX() ; int y1 = (*it1)->getPosY() ;

        if ( x == x1 && y == y1 - 1 )
            return 0 ;
    }



    vector<Soldier *> v2 = this->_soldier ;
    vector<Soldier *>::iterator it2 ;

    for ( it2 = v2.begin() ; it2 != v2.end() ; it2++ )
    {
        int x1 = (*it2)->getPosX() ; int y1 = (*it2)->getPosY() ;

        if ( x == x1 && y == y1 + 1 )
            return 0 ;

    }

    return 1 ;

}

void World::initWrold0()
{
    QImage start ;
    start.load(":/pics/start.jpg") ;
    this->_background = start.copy(QRect(0,0,640,864)) ;

}

void World::initWorld1()
{

    _rank = 1 ;

    QImage background ;
    background.load(":/pics/Background.jpg") ;
    _background = background.copy(QRect(0,16,640,864)) ;


    Tower *p1 = new Tower;
    p1->initObj("tower");
    p1->setPosX(4);
    p1->setPosY(7);
    (*p1).set_life(50);

    Tower *p2 = new Tower;
    p2->initObj("tower");
    p2->setPosX(15);
    p2->setPosY(7);
    (*p2).set_life(50);

    this->_tower.push_back(p1);
    this->_tower.push_back(p2);
    //生成塔

    Base *p7 = new Base ;
    p7->initObj("base") ;
    p7->setPosX(4) ;
    p7->setPosY(18) ;
    (*p7).set_life(50);

    Base *p8 = new Base ;
    p8->initObj("base") ;
    p8->setPosX(15) ;
    p8->setPosY(18) ;
    (*p8).set_life(50);

    this->_base.push_back(p7);
    this->_base.push_back(p8);
    //生成基地

    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/sounds/hdl.mp3"));
    player->setVolume(30);
    player->play();


}

void World::initWorld2()
{
    _rank = 2 ;

    _qi_of_me = 10 ;
    _qi_of_enemy = 10 ;

    _life_of_me = 100 ;
    _life_of_enemy = 100 ;

    QImage background ;
    background.load(":/pics/backg.jpg") ;//这里导入的应该是第二关的地图文件
    _background = background.copy(QRect(0,0,640,864)) ;

    Tower *p1 = new Tower;
    p1->initObj("tower");
    p1->setPosX(4);
    p1->setPosY(7);
    (*p1).set_life(50);

    Tower *p2 = new Tower;
    p2->initObj("tower");
    p2->setPosX(15);
    p2->setPosY(7);
    (*p2).set_life(50);

    this->_tower.push_back(p1);
    this->_tower.push_back(p2);
    //生成塔

    Base *p7 = new Base ;
    p7->initObj("base") ;
    p7->setPosX(4) ;
    p7->setPosY(18) ;
    (*p7).set_life(50);

    Base *p8 = new Base ;
    p8->initObj("base") ;
    p8->setPosX(15) ;
    p8->setPosY(18) ;
    (*p8).set_life(50);

    this->_base.push_back(p7);
    this->_base.push_back(p8);
    //生成基地

    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/sounds/hdl.mp3"));
    player->setVolume(30);
    player->play();


}



void World::show(QPainter * painter){

    painter->drawImage(0,0,_background) ;

    int n1 = this->_tower.size();
    for (int i=0;i<n1;i++){
        this->_tower[i]->show(painter);
    }

    int n2 = this->_soldier.size();
    for (int i=0;i<n2;i++){
        this->_soldier[i]->show(painter);
    }

    int n3 = this->_enemy.size();
    for (int i=0;i<n3;i++){
        this->_enemy[i]->show(painter);
    }

    int n4 = this->_others.size();
    for (int i=0;i<n4;i++){
        this->_others[i]->show(painter);
    }

    int n5 = this->_base.size();
    for (int i=0;i<n5;i++){
        this->_base[i]->show(painter);
    }

    if ( this->get_life_of_enemy() == 0 )
    {
        QImage win ;
        QImage _win ;
        win.load(":/pics/river.jpg") ;
        _win = win.copy(QRect(0,0,640,864)) ;//这里导入的应该是一个表示 you win 的图片

        painter->drawImage(0,0,_win) ;
    }

    if ( this->get_life_of_me() == 0 )
    {
        QImage lose ;
        QImage _lose ;
        lose.load((":/pics/TileB.png")) ;
        _lose = lose.copy(QRect(0,0,640,864)) ;

        painter->drawImage(0,0,_lose) ;
    }
}


void World::eraseObj(int x, int y){
    vector<Tower*>::iterator it1;
    for(it1 = this->_tower.begin() ; it1 != this->_tower.end() ; )
    {
       if ( ((*it1)->getPosX() == x) && ((*it1)->getPosY() == y) )
       {
            (*it1)->onErase();
            this->_tower.erase(it1);
            //delete (*it);
            break;
        }
       else it1++ ;
    }

    vector<Soldier *>::iterator it2 ;
    for(it2 = this->_soldier.begin() ; it2 != this->_soldier.end() ; )
    {
       if ( ((*it2)->getPosX() == x) && ((*it2)->getPosY() == y) )
       {
            (*it2)->onErase();
            this->_soldier.erase(it2);
            //delete (*it);
            break;
        }
       else it2++ ;
    }

    vector<Enemy *>::iterator it3 ;
    for(it3 = this->_enemy.begin() ; it3 != this->_enemy.end() ; )
    {
       if ( ((*it3)->getPosX() == x) && ((*it3)->getPosY() == y) )
       {
            (*it3)->onErase();
            this->_enemy.erase(it3);
            //delete (*it);
            break;
        }
       else it3++ ;
    }

    vector<Base *>::iterator it4 ;
    for(it4 = this->_base.begin() ; it4 != this->_base.end() ; )
    {
       if ( ((*it4)->getPosX() == x) && ((*it4)->getPosY() == y) )
       {
            (*it4)->onErase();
            this->_base.erase(it4);
            //delete (*it);
            break;
        }
       else it4++ ;
    }
}

void World::delete_world()
{

    this->_tower.clear() ;
    this->_soldier.clear() ;
    this->_base.clear() ;
    this->_enemy.clear() ;
    this->_others.clear() ;


}

bool World::tower_safe(Tower *tower)
{
    int x = tower->getPosX() ;
    int y = tower->getPosY() ;

    vector<Enemy *> v = _enemy ;

    vector<Enemy *>::iterator it ;

    for ( it = v.begin() ; it != v.end() ; it++ )
    {
        int x1 = (*it)->getX() ; int y1 = (*it)->getY() ;
        if ( x1 == x && y1 == y+3 ) return 0 ;
    }
    return 1 ;
}

bool World::base_safe(Base *base)
{
    int x = base->getPosX() ;
    int y = base->getPosY() ;

    vector<Soldier *> v = _soldier ;

    vector<Soldier *>::iterator it ;

    for ( it = v.begin() ; it != v.end() ; it++ )
    {
        int x1 = (*it)->getX() ; int y1 = (*it)->getY() ;
        if ( x1 == x && y1 == y-2) return 0 ;
    }
    return 1 ;
}




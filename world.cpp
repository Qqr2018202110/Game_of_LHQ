#include "world.h"
#include "icon.h"
#include "rpgobj.h"
#include "soldier.h"
#include <QMediaPlayer>
#include <QTime>
#include <QTimer>
#include <math.h>
#include <map>
#include <iostream>
#include <QProgressBar>
#include <QPushButton>
#include <QLabel>

World::~World()
{

}

void World::addRuins(double x, double y)
{
    RPGObj * p = new RPGObj ;
    p->initObj("ruins") ;
    p->setPosX(x) ;
    p->setPosY(y) ;
    this->_others.push_back(p) ;
}

void World::addEne1(double x,double y)
{
    if (fabs(x) > 0.1 && fabs(y) > 0.1)
    {
        if ( _qi_of_enemy > 0 )
        {
            Enemy *p = new Enemy;
            p->initObj("enemy1");
            p->set_rank(1);
            p->setPosX(x);
            p->setPosY(y);
            (*p).set_life(20);
            this->_enemy.push_back(p) ;
            _qi_of_enemy -=1 ;
        }
    }
}

void World::addEne2(double x,double y)
{
    if (fabs(x) > 0.1 && fabs(y) > 0.1)
    {
        if ( _qi_of_enemy > 0 )
        {
            Enemy *p = new Enemy;
            p->initObj("enemy2");
            p->set_rank(2);
            p->setPosX(x);
            p->setPosY(y);
            (*p).set_life(20);

            this->_enemy.push_back(p) ;
            _qi_of_enemy -=2 ;
        }
    }
}


void World::addEne3(double x,double y)
{
    if (fabs(x) > 0.1 && fabs(y) > 0.1)
    {
        if ( _qi_of_enemy > 0 )
        {
            Enemy *p = new Enemy;
            p->set_rank(3);
            p->initObj("enemy3");
            p->setPosX(x);
            p->setPosY(y);
            (*p).set_life(20);
            this->_enemy.push_back(p) ;
            _qi_of_enemy -=3 ;
        }
    }
}



bool World::can_move(Soldier* s)
{
    double x = s->getX() ; double y = s->getY() - 3 ;

    if ( 6 - x > -0.1 && 6 - x < 2.1 && y < 2 )
        return 0 ;
    else if ( 12 - x < -0.1 && 14 - x > 0.1 && y < 2 )
        return 0 ;

    vector<Tower *> v1 = this->_tower ;
    vector<Tower *>::iterator it1 ;

    for ( it1 = v1.begin() ; it1 != v1.end() ; it1++ )
    {
        double x1 = (*it1)->getPosX() ; double y1 = (*it1)->getPosY() ;

        if ( fabs(x1 - x) < 2 && fabs(y-y1) < 0.1 )
            return 0 ;
    }



    vector<Enemy *> v2 = this->_enemy ;
    vector<Enemy *>::iterator it2 ;

    for ( it2 = v2.begin() ; it2 != v2.end() ; it2++ )
    {
        double x1 = (*it2)->getPosX() ; double y1 = (*it2)->getPosY() ;

        if ( fabs(x-x1) < 0.1 && (y-y1 < 0.1&&y-y1>(-3.1) ))
            return 0 ;

    }

    return 1 ;

}



bool World::can_move(Enemy* s)
{
    double x = s->getX() ; double y = s->getY() + 3 ;

    if ( fabs(x-6) < 0.01 && fabs(y-24.5) < 0.1 ) return 0 ;
    if ( x - 12 > -0.1 && x - 12 < 2.1 && fabs(y-24.5) < 0.1 ) return 0 ;
    if(6-x>-0.1&&6-x<2.1&&fabs(y-24.5) < 0.1 ) return 0 ;


    vector<Base *> v1 = this->_base ;
    vector<Base *>::iterator it1 ;

    for ( it1 = v1.begin() ; it1 != v1.end() ; it1++ )
    {
        double x1 = (*it1)->getPosX() ; double y1 = (*it1)->getPosY() ;

        if ( fabs(x1 - x) < 2 && fabs(y-y1) < 0.05 )
            return 0 ;
    }



    vector<Soldier *> v2 = this->_soldier ;
    vector<Soldier *>::iterator it2 ;

    for ( it2 = v2.begin() ; it2 != v2.end() ; it2++ )
    {
        double x1 = (*it2)->getPosX() ; double y1 = (*it2)->getPosY() ;

        if ( fabs(x-x1) < 0.1 && y-y1 < 3.1&&y-y1>(-0.1) )
            return 0 ;

    }

    return 1 ;

}

void World::initWrold0()
{
    QImage start ;
    start.load(":/pics/Start.png") ;
    this->_background = start.copy(QRect(0,0,640,864)) ;
    QImage All ;
    All.load(":/pics/ICON.png") ;

    _Ali = All.copy(4 * 32,0,4 * 32,3 * 32) ;
    _Tencent = All.copy(4 * 32, 3 * 32,4 * 32,3 * 32) ;

    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/sounds/START_BGM.mp3"));
    player->setVolume(300);
    player->play();

}

void World::initWorld1()
{

    _rank = 1 ;
    QImage background ;
    background.load(":/pics/background.png") ;
    _background = background.copy(QRect(0,0,640,864)) ;


    Tower *p1 = new Tower;
    p1->initObj("tower");
    p1->setPosX(3);
    p1->setPosY(5);
    (*p1).set_life(50);

    Tower *p2 = new Tower;
    p2->initObj("tower");
    p2->setPosX(14);
    p2->setPosY(5);
    (*p2).set_life(50);

    this->_tower.push_back(p1);
    this->_tower.push_back(p2);
    //生成塔

    Base *p7 = new Base ;
    p7->initObj("base") ;
    p7->setPosX(3) ;
    p7->setPosY(17) ;
    (*p7).set_life(50);

    Base *p8 = new Base ;
    p8->initObj("base") ;
    p8->setPosX(14) ;
    p8->setPosY(17) ;
    (*p8).set_life(50);

    this->_base.push_back(p7);
    this->_base.push_back(p8);
    //生成基地

    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/sounds/PLAY_BGM.mp3"));
    player->setVolume(30);
    player->play();

    this->_life_of_me = 100 ;
    this->_life_of_enemy = 100 ;

}



void World::initWorld2()
{
    _rank = 2 ;

    _qi_of_me = 10 ;
    _qi_of_enemy = 10 ;

    _life_of_me = 100 ;
    _life_of_enemy = 100 ;

    QImage background ;
    background.load(":/pics/Background2.png") ;//这里导入的应该是第二关的地图文件
    _background = background.copy(QRect(0,0,640,864)) ;

    Tower *p1 = new Tower;
    p1->initObj("tower");
    p1->setPosX(3);
    p1->setPosY(5);
    (*p1).set_life(50);

    Tower *p2 = new Tower;
    p2->initObj("tower");
    p2->setPosX(14);
    p2->setPosY(5);
    (*p2).set_life(50);

    this->_tower.push_back(p1);
    this->_tower.push_back(p2);
    //生成塔

    Base *p7 = new Base ;
    p7->initObj("base") ;
    p7->setPosX(3) ;
    p7->setPosY(17) ;
    (*p7).set_life(50);

    Base *p8 = new Base ;
    p8->initObj("base") ;
    p8->setPosX(14) ;
    p8->setPosY(17) ;
    (*p8).set_life(50);

    this->_base.push_back(p7);
    this->_base.push_back(p8);
    //生成基地

    //生成基地

    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/sounds/PLAY_BGM.mp3"));
    player->setVolume(30);
    player->play();


}

void World::initWorld3()
{
    _rank = 3 ;

    _qi_of_me = 10 ;
    _qi_of_enemy = 10 ;

    _life_of_me = 100 ;
    _life_of_enemy = 100 ;

    QImage background ;
    background.load(":/pics/Background3.png") ;//这里导入的应该是第二关的地图文件
    _background = background.copy(QRect(0,0,640,864)) ;

    Tower *p1 = new Tower;
    p1->initObj("tower");
    p1->setPosX(3);
    p1->setPosY(5);
    (*p1).set_life(50);

    Tower *p2 = new Tower;
    p2->initObj("tower");
    p2->setPosX(14);
    p2->setPosY(5);
    (*p2).set_life(50);

    this->_tower.push_back(p1);
    this->_tower.push_back(p2);
    //生成塔

    Base *p7 = new Base ;
    p7->initObj("base") ;
    p7->setPosX(3) ;
    p7->setPosY(17) ;
    (*p7).set_life(50);

    Base *p8 = new Base ;
    p8->initObj("base") ;
    p8->setPosX(14) ;
    p8->setPosY(17) ;
    (*p8).set_life(50);

    this->_base.push_back(p7);
    this->_base.push_back(p8);
    //生成基地

    //生成基地

    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/sounds/PLAY_BGM.mp3"));
    player->setVolume(30);
    player->play();


}



void World::show(QPainter * painter)
{
    painter->drawImage(0,0,_background);
    if(this->get_life_of_enemy()>0&&this->get_life_of_me()>0&&this->get_rank() > 0)
    {
           painter->drawImage(256,672,_Ali);
           painter->drawImage(256,32,_Tencent);
    }
    int j,r;
    int n1 = this->_tower.size();
    for (int i=0;i<n1;i++)
    {
        this->_tower[i]->show(painter);
    }

    int n2 = this->_soldier.size();
    for (int i=0;i<n2;i++)
    {
        r=0;
        double _x=_soldier[i]->getPosX();
        double _y=_soldier[i]->getPosY();
        for(j=0;j<i;j++)
        {
            double x=_soldier[j]->getPosX();
            double y=_soldier[j]->getPosY();
            if(x==_x&&y==_y)
                r++;
        }
        this->_soldier[i]->show(painter,r);
    }

    int n3 = this->_enemy.size();
    for (int i=0;i<n3;i++)
    {
        r=0;
        double _x=_enemy[i]->getPosX();
        double _y=_enemy[i]->getPosY();
        for(j=0;j<i;j++)
        {
            double x=_enemy[j]->getPosX();
            double y=_enemy[j]->getPosY();
            if(x==_x&&y==_y)
                r++;
        }
        this->_enemy[i]->show(painter,-r);
    }

    int n4 = this->_others.size();
    for (int i=0;i<n4;i++){
        this->_others[i]->show(painter);
    }

    int n5 = this->_base.size();
    for (int i=0;i<n5;i++){
        this->_base[i]->show(painter);
    }

    int n6 = this->_bullet.size() ;
    for (int i = 0 ; i < n6 ; i++)
    {
        this->_bullet[i]->show(painter);
        if (this->_bullet[i]->getPosY() > this->_bullet[i]->getEnd().getY() + 0.1)
        {

            _bullet[i]->setPosY(_bullet[i]->getPosY() - 0.05);
        }
        else if (this->_bullet[i]->getPosX() > this->_bullet[i]->getEnd().getX() + 0.1)
        {
            _bullet[i]->setPosX(_bullet[i]->getPosX() - 0.05);
        }
        else if (this->_bullet[i]->getPosY() < this->_bullet[i]->getEnd().getY()- 0.1)
        {
            _bullet[i]->setPosY(_bullet[i]->getPosY() + 0.05);
        }
        else if (this->_bullet[i]->getPosX() < this->_bullet[i]->getEnd().getX() - 0.1)
        {
            _bullet[i]->setPosX(_bullet[i]->getPosX() + 0.05);
        }
        else eraseObj(_bullet[i]->getPosX(),_bullet[i]->getPosY());

    }
}


void World::eraseObj(double x, double y)
{
    vector<Tower*>::iterator it1;
    for(it1 = this->_tower.begin() ; it1 != this->_tower.end() ; )
    {
       if ( fabs((*it1)->getPosX() - x) < 0.1 && fabs((*it1)->getPosY() - y) < 0.1 && (*it1)->getLife() <= 0)
       {
            (*it1)->onErase();
            this->_tower.erase(it1);
            //delete (*it1); it1 = it1++ ;
            break;
        }
       else it1++ ;
    }

    vector<Soldier *>::iterator it2 ;
    for(it2 = this->_soldier.begin() ; it2 != this->_soldier.end() ; )
    {
       if ( fabs((*it2)->getPosX() - x) < 0.1 && fabs((*it2)->getPosY() - y) < 0.1 && (*it2)->getLife() <= 0)
       {
            (*it2)->onErase();
            this->_soldier.erase(it2);
            //delete (*it2); it2 = it2++ ;
           //_soldier.pop_back();
            break;
        }
       else it2++ ;
    }

    vector<Enemy *>::iterator it3 ;
    for(it3 = this->_enemy.begin() ; it3 != this->_enemy.end() ; )
    {
       if ( fabs((*it3)->getPosX() - x) < 0.1 && fabs((*it3)->getPosY() - y) < 0.1 && (*it3)->getLife() <= 0)
       {
            (*it3)->onErase();
            this->_enemy.erase(it3);
            //delete (*it3); it3 = it3++ ;
            break;
        }
       else it3++ ;
    }

    vector<Base *>::iterator it4 ;
    for(it4 = this->_base.begin() ; it4 != this->_base.end() ; )
    {
       if ( fabs((*it4)->getPosX() - x) < 0.1 && fabs((*it4)->getPosY() - y) < 0.1 && (*it4)->getLife() <= 0)
       {
            (*it4)->onErase();
            this->_base.erase(it4);
            //delete (*it4); it4 = it4++ ;
            break;

        }
       else it4++ ;
    }
   // exit(0);

    vector<Bullet *>::iterator it5 ;
    int size=_bullet.size();
    for(it5 = this->_bullet.begin() ; it5 != this->_bullet.end() ; )
    {
       if ( fabs((*it5)->getPosX() - x) < 0.1 && fabs((*it5)->getPosY() - y) < 0.1 )
       {
            (*it5)->onErase();
            //this->_bullet.erase(it5);
            //delete (*it5); it5 = it5++ ;
            _bullet.pop_back();
            int size2=_bullet.size();
            break;
        }
       else it5++ ;
    }
}

void World::delete_world()
{
    this->_tower.clear() ;
    this->_soldier.clear() ;
    this->_base.clear() ;
    this->_enemy.clear() ;
    this->_others.clear() ;
    if(this->get_life_of_me()<=0)
    {
        QImage win ;
        int rank=this->get_rank();
        switch (rank)
        {
        case 1: win.load(":/pics/1_WIN_LOSE.png");break;
        case 2: win.load(":/pics/2_WIN_LOSE.png");break;
        case 3: if(this->get_myscore()>this->get_yourscore())
            {win.load(":/pics/RESULT_LOSE_WIN.png");}
            else {win.load(":/pics/RESULT_WIN_LOSE.png");};break;
        }
        _background= win.copy(QRect(0,0,640,864)) ;
    }
    else
    {
        QImage win ;
        int rank=this->get_rank();
        switch (rank)
        {
        case 1: win.load(":/pics/1_LOSE_WIN.png");break;
        case 2: win.load(":/pics/2_LOSE_WIN.png");break;
        case 3: if(this->get_myscore()>this->get_yourscore())
            {win.load(":/pics/RESULT_LOSE_WIN.png");}
            else {win.load(":/pics/RESULT_WIN_LOSE.png");};break;
        }
        _background= win.copy(QRect(0,0,640,864)) ;
    }
}

bool World::tower_safe(Tower *tower)
{
    double x = tower->getPosX() ;
    double y = tower->getPosY() ;

    vector<Enemy *> v = _enemy ;

    vector<Enemy *>::iterator it ;

    for ( it = v.begin() ; it != v.end() ; it++ )
    {
        double x1 = (*it)->getX() ; double y1 = (*it)->getY() ;
        if ( fabs(x-x1) < 0.1 && fabs(y-y1-3) < 0.01 ) return 0 ;
    }
    return 1 ;
}

bool World::base_safe(Base *base)
{
    double x = base->getPosX() ;
    double y = base->getPosY() ;

    vector<Soldier *> v = _soldier ;

    vector<Soldier *>::iterator it ;

    for ( it = v.begin() ; it != v.end() ; it++ )
    {
        double x1 = (*it)->getX() ; double y1 = (*it)->getY() ;
        if ( fabs(x-x1) < 0.1 && fabs(y-y1-3) < 0.01 ) return 0 ;
    }
    return 1 ;
}

void World::addSol1(double x,double y)
{
    if (fabs(x) > 0.1 && fabs(y) > 0.1)
    {
        if ( _qi_of_me > 0 )
        {
            Soldier *p = new Soldier;
            p->initObj("soldier1");
            p->set_rank(1);
            p->setPosX(x);
            p->setPosY(y);
            (*p).set_life(20);

            this->_soldier.push_back(p) ;
            _qi_of_me -=1 ;
        }
    }
}
void World::addSol2(double x, double y)
{
    if (fabs(x) > 0.1 && fabs(y) > 0.1)
    {
        if ( _qi_of_me > 0 )
        {
            Soldier *p = new Soldier;
            p->initObj("soldier2");
            p->set_rank(2);
            p->setPosX(x);
            p->setPosY(y);
            (*p).set_life(20);

            this->_soldier.push_back(p) ;
            _qi_of_me -=2 ;
        }
    }
}

void World::addSol3(double x, double y)
{
    if (fabs(x) > 0.1 && fabs(y) > 0.1)
    {
        if ( _qi_of_me > 0 )
        {
            Soldier *p = new Soldier;
            p->initObj("soldier3");
            p->set_rank(3);
            p->setPosX(x);
            p->setPosY(y);
            (*p).set_life(20);

            this->_soldier.push_back(p) ;
            _qi_of_me -=3 ;
        }
    }
}








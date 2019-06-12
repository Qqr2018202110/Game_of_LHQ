#include "mw1.h"
#include "ui_mw1.h"
#include "icon.h"
#include "bullet.h"
#include <QTime>
#include<QTimer>
#include <map>
#include <iostream>
#include <QProgressBar>
#include <QPushButton>
#include <QLabel>
#include <math.h>

#define percession 0.1

using namespace std;

MW1::MW1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MW1)
{
    ui->setupUi(this);
    _game.initWrold0();
    setWindowTitle("Tencent&Ali") ;


    ui->life_me->hide() ;
    ui->life_enemy->hide() ;
    ui->qi_enemy->hide() ;
    ui->qi_me->hide() ;

    ui->life_me->setRange(0,100) ;
    ui->life_me->setValue(100) ;

    ui->life_enemy->setRange(0,100) ;
    ui->life_enemy->setValue(100) ;

    ui->qi_me->setRange(0,10);
    ui->qi_me->setValue(10);

    ui->qi_enemy->setRange(0,10) ;
    ui->qi_enemy->setValue(10) ;

    connect(ui->start_button,SIGNAL(on_start_button_clicked()),this,SLOT(on_start_button_clicked())) ;



    timer1 = new QTimer(this);
    connect(timer1,SIGNAL(timeout()),this,SLOT(march_of_soldiers()));
    timer1->start(50);
    timer1->setInterval(5);

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    timer2 = new QTimer(this);
    connect(timer2,SIGNAL(timeout()),this,SLOT(march_of_enemy()));
    timer2->start(50);
    timer2->setInterval(5);

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));


    timer3 = new QTimer(this);
    connect(timer3,SIGNAL(timeout()),this,SLOT(add_qi()));//timeout 是函数调用的信号（条件）
                                                          //slot 里面的函数（槽函数）在 SIGNAL 成立时调用
    timer3->start(50);
    timer3->setInterval(5000);

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));//设置随机种子

    timer4 = new QTimer(this);
    connect(timer4,SIGNAL(timeout()),this,SLOT(show_qi()));
    timer4->start(0);
    timer4->setInterval(5);

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

}

MW1::~MW1()
{
    delete ui;
}

void MW1::paintEvent(QPaintEvent *)
{
    QPainter *pa;
    pa = new QPainter();
    pa->begin(this);
    pa->translate(32,32);
    this->_game.show(pa);
    drawScore(pa);
    pa->end();
    delete pa;

    QPainter painter(this) ;
    painter.translate(32,32);
    painter.setPen(QPen(Qt::blue,4)) ;
    this->_rec_of_me.show(painter) ;
    painter.setPen(QPen(Qt::red,4)) ;
    this->_rec_of_enemy.show(painter) ;


}

void MW1::keyPressEvent(QKeyEvent *e)
{

    if(e->key() == Qt::Key_J)//左路放小兵
    {
        Point p1(6,23.5) ; Point p2(8,21.5) ;
        Rectangle rec(p1,p2) ;
        this->setRect_of_me(rec) ;
    }
    else if (e->key() == Qt::Key_L)//右路放小兵
    {
        Point p1(12,23.5),p2(14,21.5) ;
        Rectangle rec(p1,p2) ;
        this->setRect_of_me(rec) ;
    }
    else if (e->key() == Qt::Key_A) {this->_rec_of_me.move_rec(3) ; if (!this->can_put_me(_rec_of_me)) this->_rec_of_me.move_rec(4) ;}
    else if (e->key() == Qt::Key_D) {this->_rec_of_me.move_rec(4) ; if (!this->can_put_me(_rec_of_me)) this->_rec_of_me.move_rec(3) ;}
    else if (e->key() == Qt::Key_S) {this->_rec_of_me.move_rec(2) ; if (!this->can_put_me(_rec_of_me)) this->_rec_of_me.move_rec(1) ;}
    else if (e->key() == Qt::Key_W) {this->_rec_of_me.move_rec(1) ; if (!this->can_put_me(_rec_of_me)) this->_rec_of_me.move_rec(2) ;}
    else if (e->key() == Qt::Key_U) //矩形框移动到应该放小兵的位置
    {
        double x = this->_rec_of_me.getLT().getX() ;
        double y = this->_rec_of_me.getLT().getY() ;
        this->_game.addSol1(x,y) ;
        Point a(0,0),b(0,0) ; Rectangle null(a,b) ;
        this->setRect_of_me(null) ;
    }
    else if(e->key()==Qt::Key_I)
    {
        double x = this->_rec_of_me.getLT().getX();
        double y = this->_rec_of_me.getLT().getY();
        this->_game.addSol2(x,y);
        Point a(0,0),b(0,0) ; Rectangle null(a,b) ;
        this->setRect_of_me(null) ;
    }
    else if(e->key()==Qt::Key_O)
    {
        double x = this->_rec_of_me.getLT().getX();
        double y = this->_rec_of_me.getLT().getY();
        this->_game.addSol3(x,y);
        Point a(0,0),b(0,0) ; Rectangle null(a,b) ;
        this->setRect_of_me(null) ;
    }
    else if(e->key()==Qt::Key_K)
    {
        Point a(0,0),b(0,0) ; Rectangle null(a,b) ;
        this->setRect_of_me(null) ;
    }
    //自己放小兵


    else if (e->key() == Qt::Key_1)//左路放小兵
    {
        Point p1(6,3.5),p2(8,1.5) ;
        Rectangle rec(p1,p2) ;
        this->setRect_of_enemy(rec) ;
    }
    else if (e->key() == Qt::Key_3)//右路放小兵
    {
        Point p1(12,3.5),p2(14,1.5) ;
        Rectangle rec(p1,p2) ;
        this->setRect_of_enemy(rec) ;
    }
    else if (e->key() == Qt::Key_Up) {this->_rec_of_enemy.move_rec(1) ; if (!this->can_put_enemy(_rec_of_enemy)) this->_rec_of_enemy.move_rec(2) ;}
    else if (e->key() == Qt::Key_Down) {this->_rec_of_enemy.move_rec(2) ; if (!this->can_put_enemy(_rec_of_enemy)) this->_rec_of_enemy.move_rec(1) ;}
    else if (e->key() == Qt::Key_Right) {this->_rec_of_enemy.move_rec(4) ; if (!this->can_put_enemy(_rec_of_enemy)) this->_rec_of_enemy.move_rec(3) ;}
    else if (e->key() == Qt::Key_Left) {this->_rec_of_enemy.move_rec(3) ; if (!this->can_put_enemy(_rec_of_enemy)) this->_rec_of_enemy.move_rec(4) ;}
    else if (e->key() == Qt::Key_4) //矩形框移动到应该放小兵的位置
    {
        double x = this->_rec_of_enemy.getLT().getX() ;
        double y = this->_rec_of_enemy.getLT().getY() ;
        this->_game.addEne1(x,y) ;
        Point a(0,0),b(0,0) ; Rectangle rec(a,b) ;
        this->setRect_of_enemy(rec) ;
    }
    else if (e->key() == Qt::Key_5) //矩形框移动到应该放小兵的位置
    {
        double x = this->_rec_of_enemy.getLT().getX() ;
        double y = this->_rec_of_enemy.getLT().getY() ;
        this->_game.addEne2(x,y) ;
        Point a(0,0),b(0,0) ; Rectangle rec(a,b) ;
        this->setRect_of_enemy(rec) ;
    }
    else if (e->key() == Qt::Key_6) //矩形框移动到应该放小兵的位置
    {
        double x = this->_rec_of_enemy.getLT().getX() ;
        double y = this->_rec_of_enemy.getLT().getY() ;
        this->_game.addEne3(x,y) ;
        Point a(0,0),b(0,0) ; Rectangle rec(a,b) ;
        this->setRect_of_enemy(rec) ;
    }
    else if (e->key() == Qt::Key_2) //矩形框移动到应该放小兵的位置
    {
        Point a(0,0),b(0,0) ; Rectangle rec(a,b) ;
        this->setRect_of_enemy(rec) ;
    }
    //敌人放小兵



    else if(e->key() == Qt::Key_P) //如果某一关结束，按 p 进入下一关
    {
        if(this->_game.get_life_of_me()<=0||this->_game.get_life_of_enemy()<=0)
        {
            this->_game.delete_world() ;
            int r = this->_game.get_rank() ;//根据当前关卡，生成下一关
            switch(r)
            {
            case 1 : this->_game.initWorld2() ; break ;
            case 2 : this->_game.initWorld3() ; break ;
            case 3 :     QPainter *pa;
                pa = new QPainter();
                pa->begin(this);
                pa->translate(32,32);
                draw_dead_choose(pa);
                pa->end();
                delete pa;
              }
            if(r!=3)
            {

            this->ui->qi_me->show() ;
            this->ui->qi_enemy->show() ;
            this->ui->life_me->show() ;
            this->ui->life_enemy->show() ;
        }
            }
    }


    if(this->_game.get_rank()==3&&(this->_game.get_life_of_me()<=0||this->_game.get_life_of_enemy()<=0))
    {
        if(e->key() == Qt::Key_Y)
        {
            this->_game.initWorld1();
            this->ui->qi_me->show() ;
            this->ui->qi_enemy->show() ;
            this->ui->life_me->show() ;
            this->ui->life_enemy->show() ;
            this->_game.set_myscore(0) ;
            this->_game.set_yourscore(0) ;
            this->_game.set_qi_of_me(10);
            this->_game.set_qi_of_enemy(10);
        }
         if(e->key() == Qt::Key_N)
         {
             exit(1);
         }
    }


    this->repaint();

}


//下面是整个游戏的逻辑核心，最复杂的地方！！！
void MW1::march_of_soldiers()
{
    bool _over = 0 ;
    //this->_game.delete_world() ;
    //判断小兵这一下能不能结束游戏

    vector <Soldier*> v = this->_game.getSol() ;
    vector <Soldier*>::iterator it ;
    //iterator 是迭代器，具体怎么回事看 note.cpp

    //对每个小兵单独进行操作
    for ( it = v.begin() ; it != v.end() ; )
    {
        double x = (*it)->getX() ; double y = (*it)->getY() ;//得到小兵的当前位置
        if ( this->_game.can_move((*it)) ) //小兵可移动，即没有遇到 Tower 和 Enemy 和敌人大本营
                {                    
                    if ( fabs(y-21.5) < 0.02 && x <= 6 && x > 3.5)
                        (*it)->soldier_move(3,0.01) ;
                    else if ( fabs(x-3.5) < 0.02 && y <= 21.5 && y >= 1.5)
                        (*it)->soldier_move(1,0.01) ;
                    else if ( fabs(y-1.5) < 0.02 && x >= 3.4 && x < 6 )
                        (*it)->soldier_move(4,0.01) ;
                    else if ( fabs(y-21.5) < 0.02 && x < 14.5 && x >= 12)
                        (*it)->soldier_move(4,0.01) ;
                    else if ( x < 15 && y <= 21.6 && y >= 1.5)
                        (*it)->soldier_move(1,0.01) ;
                    else if ( y > 1 && x < 15 && x > 12)
                        (*it)->soldier_move(3,0.01) ;
                }//限定小兵的行进路线
        else
        {
            (*it)->set_attackcount();
            if((*it)->get_attackcount()==100)
            {
            this->attack_enemy((*it)) ;
            this->attack_tower((*it)) ;
            {
                if ( 6 - x > -0.1 && 6 - x < 2.1 && y < 2 && this->_game.get_life_of_enemy() > 0 ) //（7,2）和（12,2）是可以攻击敌人大本营的小兵的坐标
                {
                    Bullet* b = new Bullet ;
                    b->initObj("bullet");
                    b->setkind(1);
                    b->setPosX(x+1); b->setPosY(y+1);
                    Point end(8,2.5) ;
                    b->setEnd(end.getX(),end.getY());
                    this->_game.getBullet().push_back(b);

                    QTime time = QTime::currentTime() ;

                    if ( time.second()%2 == 1 ) this->_game.life_loss_of_enemy() ;
                }
                else if ( 12 - x < -0.1 && x - 12 < 2.1 && y < 2 && this->_game.get_life_of_enemy() > 0 )
                {
                    Bullet* b = new Bullet ;
                    b->initObj("bullet");
                    b->setkind(1);
                    b->setPosX(x+1); b->setPosY(y+1);
                    Point end(12,2.5) ;
                    b->setEnd(end.getX(),end.getY());
                    this->_game.getBullet().push_back(b);

                    QTime time = QTime::currentTime() ;

                    if ( time.second()%2 == 1 ) this->_game.life_loss_of_enemy() ;
                }
                else if ( 6 - x > -0.1 && 6 - x < 2.1 && y < 2 && this->_game.get_life_of_enemy() <= 0 )
                {
                    _over = 1 ;//如果敌人大本营被干掉，这一关结束，后面 _over 有代码实现
                    break ;
                }
                else if ( 12 - x < -0.1 && x - 12 < 2.1 && y < 2 && this->_game.get_life_of_enemy() <= 0 )
                {
                    _over = 1 ;
                    break ;
                }
            }

        }
    }
        it++ ;

    }

    if (_over)
    {
        this->ui->qi_me->hide() ;
        this->ui->qi_enemy->hide() ;
        this->ui->life_me->hide() ;
        this->ui->life_enemy->hide() ;
        int x=this->_game.get_myscore();
        x++;
        this->_game.set_myscore(x);
        this->_game.delete_world() ;
    }
    this->repaint();
}

void MW1::march_of_enemy() //和上面同理，但是被敌人把老家端掉的函数我还没有实现，反正道理是一样的
{

    {
        bool _over = 0 ;

        vector <Enemy *> v = this->_game.getEnemy() ;
        vector <Enemy *>::iterator it ;

            for ( it = v.begin() ; it != v.end() ; it++ )
            {
                double x = (*it)->getPosX() ; double y = (*it)->getPosY() ;
                if (this->_game.can_move((*it)))
                {
                    if ( fabs(y-21.6) < 0.02 && x <= 6 && x >= 3.5)
                        (*it)->enemy_move(4,0.01) ;
                    else if ( fabs(x-3.5) < 0.02 && y <= 21.6 && y >= 1.5)
                        (*it)->enemy_move(2,0.01) ;
                    else if ( fabs(y-1.5) < 0.02 && x >= 3.4 && x <= 6 )
                        (*it)->enemy_move(3,0.01) ;
                    else if ( fabs(y-21.6) < 0.02 && x <= 14.5 && x >= 12)
                        (*it)->enemy_move(3,0.01) ;
                    else if ( x > 14.499 && y <= 21.6 && y >= 1.5)
                        (*it)->enemy_move(2,0.01) ;
                    else if ( fabs(y-1.5) < 0.02 && x < 15 && x > 11.9)
                        (*it)->enemy_move(4,0.01) ;
                }
                else
                {
                    (*it)->set_attackcount();
                    if((*it)->get_attackcount()==100)
                    {
                    this->attack_soldier((*it)) ;
                    this->attack_base((*it)) ;

                    if ( 6 - x > -0.1 && 6 - x < 2.1 && fabs(y-21.5) < 0.1 && this->_game.get_life_of_me() >0 )
                    {
                        Bullet* b = new Bullet ;
                        b->initObj("bullet");
                        b->setkind(1);
                        b->setPosX(x+1); b->setPosY(y+1);
                        Point end(8,22.5) ;
                        b->setEnd(end.getX(),end.getY());
                        this->_game.getBullet().push_back(b);

                        QTime time = QTime::currentTime() ;

                        if ( time.second()%2 == 1 )
                            this->_game.life_loss_of_me() ;
                    }
                    else if ( x - 12 > -0.1 && x - 12 < 2.1 && fabs(y-21.5) < 0.1 && this->_game.get_life_of_me() >0 )
                    {
                        Bullet* b = new Bullet ;
                        b->initObj("bullet");
                        b->setkind(1);
                        b->setPosX(x+1); b->setPosY(y+1);
                        Point end(12,22.5) ;
                        b->setEnd(end.getX(),end.getY());
                        this->_game.getBullet().push_back(b);

                        QTime time = QTime::currentTime() ;

                        if ( time.second()%2 == 1 )
                            this->_game.life_loss_of_me() ;
                    }
                    else if ( 6 - x > -0.1 && 6 - x < 2.1 && fabs(y-21.5) < 0.1 ) { _over = 1 ; break ;}
                    else if ( x - 12 > -0.1 && x - 12 < 2.1 && fabs(y-21.5) < 0.1 ) { _over = 1 ; break ;}

                }
                }
            }
            if (_over)
            {
                this->ui->qi_me->hide() ;
                this->ui->qi_enemy->hide() ;
                this->ui->life_me->hide() ;
                this->ui->life_enemy->hide() ;
                this->_game.delete_world() ;
                int x=this->_game.get_yourscore();
                x++;
                this->_game.set_yourscore(x);
            }
        this->repaint() ;
    }
}

void MW1::show_qi()
{
    int l1 = this->_game.get_life_of_me() ;
    int l2 = this->_game.get_life_of_enemy() ;
    this->ui->life_me->setValue(l1) ;
    this->ui->life_enemy->setValue(l2) ;

    int q1 = this->_game.get_qi_of_me() ;
    int q2 = this->_game.get_qi_of_enemy() ;
    this->ui->qi_me->setValue(q1) ;
    this->ui->qi_enemy->setValue(q2) ;
}

bool MW1::can_put_me(Rectangle rec)
{
    double x = rec.getLT().getX() ;
    double y = rec.getLT().getY() ;

    if ( fabs(x-3.5) < 0.1 && y <= 21.5 && y >= 14 ) return 1 ;
    else if ( fabs(y-21.5) < 0.1 && x >= 4 && x <= 6 ) return 1 ;
    else if (fabs(x-14.5) < 0.1 && y <= 21.5 && y >= 14 ) return 1 ;
    else if ( fabs(y-21.5) < 0.1 && x >= 12 && x <= 14.5) return 1 ;
    return 0 ;
}

bool MW1::can_put_enemy(Rectangle rec)
{
    double x = rec.getLT().getX() ;
    double y = rec.getLT().getY() ;

    if ( fabs(x-3.5) < 0.1 && y <= 10&& y >= 1.5 ) return 1 ;
    else if ( fabs(y-1.5) < 0.1 && x >= 3.5 && x <= 6 ) return 1 ;
    else if ( fabs(x-14.5) < 0.1 && y <= 10 && y >= 1.5 ) return 1 ;
    else if ( fabs(y-1.5) < 0.1 && x >= 12 && x <= 14.5 ) return 1 ;
    return 0 ;
}

void MW1::attack_enemy(Soldier *s)
{
    double x = s->getX() ;
    double y = s->getY() ;

    vector<Enemy *> v = this->_game.getEnemy() ;
    vector<Enemy *>::iterator it ;
    for ( it = v.begin() ; it != v.end() ; it++ )
    {
        double x1 = (*it)->getX() ; double y1 = (*it)->getY() ;
        if ((*it)->getLife() >= 0 && fabs(x-x1) < 0.1 && y-y1<3.1&&y-y1>-0.1)//判断攻击范围的同时判断敌兵还有多少血                                                             //如果敌兵只有一滴血，直接被秒，不用 _life-- 了
        {
                (*it)->life_loss(s) ;
                Bullet* b = new Bullet ;
                b->setkind(1);
                b->initObj("bullet");
                b->setPosX(s->getPosX()+1); b->setPosY(s->getPosY()+1);
                b->setEnd((*it)->getPosX()+1,(*it)->getPosY()+1);
                this->_game.getBullet().push_back(b);
        }
        else if ( fabs(x-x1) < 0.1 &&  y-y1<3.1&&y-y1>-0.1 )
            this->_game.eraseObj((*it)->getX(),(*it)->getY()) ; //敌兵被干掉

    }
}

void MW1::attack_tower(Soldier *s)
{
    double x = s->getX() ;
    double y = s->getY() ;

    vector<Tower *> v = this->_game.getTow() ;
    vector<Tower *>::iterator it ;

    for ( it = v.begin() ; it != v.end() ; it++)
    {
        //if ( !this->_game.tower_safe((*it)) )
        {
            double x1 = (*it)->getPosX() ; double y1 = (*it)->getPosY() ;
            if ((*it)->getLife() >= 0 && fabs(x-x1) < 1.5 && y-y1<3.1&&y-y1>-0.1 )
            {
                    (*it)->life_loss(s) ;
                    Bullet* b = new Bullet ;
                    b->setkind(1);
                    b->initObj("bullet");
                    b->setPosX(s->getPosX()+1); b->setPosY(s->getPosY()+1);
                    b->setEnd((*it)->getPosX()+1.5,(*it)->getPosY()+1.5);
                    this->_game.getBullet().push_back(b);

            }
            else if ( fabs(x-x1) < 1.5 &&  y-y1<3.1&&y-y1>-0.1 )
            {
                this->_game.eraseObj((*it)->getPosX(),(*it)->getPosY()) ;
                //this->_game.delete_world() ;
                this->_game.addRuins((*it)->getPosX(),(*it)->getPosY()) ;
            }
        }
    }
}

void MW1::attack_base(Enemy *e)
{
    double x = e->getX() ;
    double y = e->getY() ;

    vector<Base *> v = this->_game.getBase() ;
    vector<Base *>::iterator it ;

    for ( it = v.begin() ; it != v.end() ; it++)
    {
        //if ( !this->_game.base_safe((*it)) )
        {
            double x1 = (*it)->getPosX() ; double y1 = (*it)->getPosY() ;
            if ((*it)->getLife() >= 0 && fabs(x-x1) < 1.5 && y-y1 < 0.1 &&y-y1>-3.1 )
            {
                    (*it)->life_loss(e) ;
                    Bullet* b = new Bullet ;
                    b->setkind(2);
                    b->initObj("bullet");
                    b->setPosX(e->getPosX()+1); b->setPosY(e->getPosY()+1);
                    b->setEnd((*it)->getPosX()+1.5,(*it)->getPosY()+1.5);
                    this->_game.getBullet().push_back(b);

            }
            else if ( fabs(x-x1) < 1.5 && y-y1 < 0.1 &&y-y1>-3.1 )
            {
                this->_game.eraseObj((*it)->getPosX(),(*it)->getPosY()) ;
                this->_game.addRuins((*it)->getPosX(),(*it)->getPosY()) ;
            }
        }
    }
}

void MW1::attack_soldier(Enemy *e)
{
    double x = e->getX() ;
    double y = e->getY() ;

    vector<Soldier *> v = this->_game.getSol() ;
    vector<Soldier *>::iterator it ;

    for ( it = v.begin() ; it != v.end() ; it++)
    {
        double x1 = (*it)->getPosX() ; double y1 = (*it)->getPosY() ;
        if ((*it)->getLife() >= 0 &&fabs(x-x1) < 0.1 && y-y1 < 0.1 &&y-y1>-3.1)
        {
                (*it)->life_loss(e) ;
                Bullet* b = new Bullet ;
                b->setkind(1);
                b->initObj("bullet");
                b->setPosX(e->getPosX()+1); b->setPosY(e->getPosY()+1);
                b->setEnd((*it)->getPosX()+1,(*it)->getPosY()+1);
                this->_game.getBullet().push_back(b);

        }

        else if ( fabs(x-x1) < 0.1 && y - y1 > -3.1 && y - y1 < 0.1 )
        {
            double _x=(*it)->getX();
            double _y=(*it)->getY();
            this->_game.eraseObj((*it)->getX(),(*it)->getY()) ;
        }

    }
}

void MW1::on_start_button_clicked()
{
    ui->life_me->show() ;
    ui->life_enemy->show() ;
    ui->qi_me->show() ;
    ui->qi_enemy->show() ;

    this->_game.initWorld1() ;
    ui->start_button->deleteLater() ;
}

void MW1::drawScore(QPainter *pa)
{
    pa->setPen(QPen(Qt::red));
    QFont font;
    font.setPointSize(30);
    font.setBold(true);
    pa->setFont(font);
    pa->drawText(QRect(640, 200, 300, 300), QString("Score : %1").arg(this->_game.get_yourscore()));
    pa->setPen(QPen(Qt::blue));
    pa->drawText(QRect(640, 600, 300, 300), QString("Score : %1").arg(this->_game.get_myscore()));
    pa->setPen((QPen(Qt::green)));
    pa->drawText(QRect(640, 400, 300, 300), QString("Round : %1").arg(this->_game.get_rank()));
}

void MW1::draw_dead_choose(QPainter *pa)
{
    pa->setPen(QPen(Qt::black));
    QFont font;
    font.setPointSize(10);
    font.setBold(true);
    pa->setFont(font);
    pa->drawText(QRect(200, 200, 300, 300), QString("Another game? Please press Y"));
    pa->drawText(QRect(200, 300, 300, 300), QString("Quit game? Please press N"));
}


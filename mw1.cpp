#include "mw1.h"
#include "ui_mw1.h"
#include "icon.h"


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
    setWindowTitle("what a fuck") ;


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
    else if (e->key() == Qt::Key_K) //矩形框移动到应该放小兵的位置
    {
        double x = this->_rec_of_me.getLT().getX() ;
        double y = this->_rec_of_me.getLT().getY() ;
        this->_game.addSol1(x,y) ;
        Point a(0,0),b(0,0) ; Rectangle null(a,b) ;
        this->setRect_of_me(null) ;
    }
    else if(e->key()==Qt::Key_O)
    {
        double x = this->_rec_of_me.getLT().getX();
        double y = this->_rec_of_me.getLT().getY();
        this->_game.addSol2(x,y);
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
    else if (e->key() == Qt::Key_2) //矩形框移动到应该放小兵的位置
    {
        double x = this->_rec_of_enemy.getLT().getX() ;
        double y = this->_rec_of_enemy.getLT().getY() ;
        this->_game.addEne1(x,y) ;
        Point a(0,0),b(0,0) ; Rectangle rec(a,b) ;
        this->setRect_of_enemy(rec) ;
    }
    //敌人放小兵



    else if(e->key() == Qt::Key_P) //如果某一关结束，按 p 进入下一关
    {
        if (this->_game.get_life_of_enemy() == 0)
        {
            int r = this->_game.get_rank() ;//根据当前关卡，生成下一关
            switch(r)
            {
                case 1 : this->_game.initWorld2() ; break ;
                default: exit(0) ;
            }
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
                if ( fabs(x-6) < 0.05 && y < 2 && this->_game.get_life_of_enemy() > 0 ) //（7,2）和（12,2）是可以攻击敌人大本营的小兵的坐标
                {
                    QTime time = QTime::currentTime() ;

                    if ( time.second()%2 == 1 ) this->_game.life_loss_of_enemy() ;
                }
                else if ( fabs(x-12) < 0.05 && y < 2 && this->_game.get_life_of_enemy() > 0 )
                {
                    QTime time = QTime::currentTime() ;

                    if ( time.second()%2 == 1 ) this->_game.life_loss_of_enemy() ;
                }
                else if ( fabs(x-6) < 0.1 && y < 2 && this->_game.get_life_of_enemy() <= 0 )
                {
                    _over = 1 ;//如果敌人大本营被干掉，这一关结束，后面 _over 有代码实现
                    break ;
                }
                else if ( fabs(x-12) < 0.05 && y < 2 && this->_game.get_life_of_enemy() <= 0 )
                {
                    _over = 1 ;
                    break ;
                }
            }

        }
    }
        it++ ;

    }

    if (_over) this->_game.delete_world() ;
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
                    if ( fabs(y-21.5) < 0.02 && x <= 6 && x > 3.5)
                        (*it)->enemy_move(4,0.01) ;
                    else if ( fabs(x-3.5) < 0.02 && y <= 21.5 && y >= 1.5)
                        (*it)->enemy_move(2,0.01) ;
                    else if ( fabs(y-1.5) < 0.02 && x >= 3.4 && x <= 6 )
                        (*it)->enemy_move(3,0.01) ;
                    else if ( fabs(y-21.5) < 0.02 && x < 14.5 && x >= 12)
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

                    if ( fabs(x-6) < 0.01 && fabs(y-21.5) < 0.1 && this->_game.get_life_of_me() >0 )
                    {
                        QTime time = QTime::currentTime() ;

                        if ( time.second()%2 == 1 )
                            this->_game.life_loss_of_me() ;
                    }
                    else if ( fabs(x-12) < 0.01 && fabs(y-21.5) < 0.1 && this->_game.get_life_of_enemy() >0 )
                    {
                        QTime time = QTime::currentTime() ;

                        if ( time.second()%2 == 1 )
                            this->_game.life_loss_of_me() ;
                    }
                    else if ( fabs(x-6) < 0.01 && fabs(y-21.5) < 0.1 ) { _over = 1 ; break ;}
                    else if ( fabs(x-12) < 0.01 && fabs(y-21.5) < 0.1 ) { _over = 1 ; break ;}

                }
                }
            }
        if (_over) this->_game.delete_world() ;

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

    if ( fabs(x-3.5) < 0.1 && y <= 10 && y >= 1.5 ) return 1 ;
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
        if ((*it)->getLife() >= 1 && fabs(x-x1) < 0.1 && fabs(y-y1) < 0.1)//判断攻击范围的同时判断敌兵还有多少血
                                                           //如果敌兵只有一滴血，直接被秒，不用 _life-- 了
        {
            QTime time = QTime::currentTime() ;//可以攻击
                                               //获取系统时间，每两秒干一滴血
                                               //每个小兵每次只能干一个敌兵一滴血，所以要 break
            if ( time.second()%2 == 1 )
            {
                (*it)->life_loss(s) ;
                show_attack(x,y,x1,y1);
                break ;
            }
        }
        else if ( fabs(x-x1) < 0.1 && fabs(y-y1) < 0.1 )
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
            if ((*it)->getLife() >= 1 && fabs(x-x1) < 0.05 && fabs(y-y1-2) < 0.1 )
            {
                QTime time = QTime::currentTime() ;

                if ( time.second()%2 == 1 )
                {
                    (*it)->life_loss(s) ;
                    show_attack(x,y,x1,y1);
                    //this->_game.delete_world() ;
                    break ;
                }
            }
            else if ( fabs(x-x1) < 0.05 && fabs(y-y1-2) < 0.1 )
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
            if ((*it)->getLife() >= 1 && fabs(x-x1) < 0.05 && fabs(y-y1+2) < 0.1 )
            {
                QTime time = QTime::currentTime() ;

                if ( time.second()%2 == 1 )
                {
                    (*it)->life_loss(e) ;
                    show_attack(x,y,x1,y1);
                    //this->_game.delete_world() ;
                    break ;
                }
            }
            else if ( fabs(x-x1) < 0.05 && fabs(y-y1+2) < 0.1 )
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
        if ((*it)->getLife() >= 1 &&fabs(x-x1) < 0.1 && fabs(y-y1) < 0.1 )
        {
            QTime time = QTime::currentTime() ;

            if ( time.second()%2 == 1 )
            {
                (*it)->life_loss(e) ;
                show_attack(x,y,x1,y1);
                break ;
            }
        }

        else if ( fabs(x-x1) < 0.1 && fabs(y-y1) < 0.1 )
        {
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

void MW1::show_attack(double x1,double y1,double x2,double y2)
{
    Point p1(x1,y1),p2(x2,y2);
    Line L(p1,p2);
    Rectangle r(p1,p2);
    QPainter painter(this);
    painter.setPen(QPen(Qt::blue,4));
    L.show(painter);
    /*  声明动画类，并将控制对象 this (this一定是继承自QObject的窗口部件)  以及属性名 "geometry" 传入构造函数  */
    //QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry");
    /*  设置动画持续时长为 2 秒钟  */
    //animation->setDuration(2000);
    /*  设置动画的起始状态 起始点 (1,2)  起始大小 (3,4)  */
    //animation->setStartValue(QLine(1, 2, 3, 4));
    /*  设置动画的结束状态 结束点 (100,200)  结束大小 (300,400)  */
    //animation->setEndValue(QLine(100, 200, 300, 400));
    /*  设置动画效果  */
    //animation->setEasingCurve(QEasingCurve::OutInExpo);
    /*  开始执行动画 QAbstractAnimation::DeleteWhenStopped 动画结束后进行自清理(效果就好像智能指针里的自动delete animation) */
    /*animation->start(QAbstractAnimation::DeleteWhenStopped);
    animation.setDuration(3000);
    animation.setStartValue(QLine(0, 0, 100, 30));
    animation.setEndValue(QLine(250, 250, 100, 30));

    animation.setEasingCurve(QEasingCurve::OutBounce);

    animation.start();*/


}
void MW1::drawline(double x1, double y1, double x2, double y2)
{
    /*QPainter *p;
    p->begin(this);
    Line l(x1,y1,x2,y2);
    l.show(*p);

    //p->drawLine(x1*32,y1*32,x2*32,y2*32);
    */
}

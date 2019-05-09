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

using namespace std;

MW1::MW1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MW1)
{
    ui->setupUi(this);
    _game.initWrold0();
    setWindowTitle("what a fuck") ;


    ui->bar_of_qi_1->hide() ;
    ui->bar_of_qi_2->hide() ;

    ui->bar_of_qi_1->setRange(0,100) ;
    ui->bar_of_qi_1->setValue(100) ;

    ui->bar_of_qi_2->setRange(0,100) ;
    ui->bar_of_qi_2->setValue(100) ;

    connect(ui->start_button,SIGNAL(on_start_button_clicked()),this,SLOT(on_start_button_clicked())) ;


    timer1 = new QTimer(this);
    connect(timer1,SIGNAL(timeout()),this,SLOT(march_of_soldiers()));
    timer1->start(50);
    timer1->setInterval(500);

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    timer2 = new QTimer(this);
    connect(timer2,SIGNAL(timeout()),this,SLOT(march_of_enemy()));
    timer2->start(50);
    timer2->setInterval(500);

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
    this->_game.show(pa);
    pa->end();
    delete pa;

    QPainter painter(this) ;
    painter.setPen(QPen(Qt::blue,4)) ;
    this->_rec_of_me.show(painter) ;
    painter.setPen(QPen(Qt::red,4)) ;
    this->_rec_of_enemy.show(painter) ;
}

void MW1::keyPressEvent(QKeyEvent *e)
{

    if(e->key() == Qt::Key_J)//左路放小兵
    {
        Point p1(7,24) ; Point p2(8,22) ;
        Rectangle rec(p1,p2) ;
        this->setRect_of_me(rec) ;
    }
    else if (e->key() == Qt::Key_L)//右路放小兵
    {
        Point p1(12,24),p2(13,22) ;
        Rectangle rec(p1,p2) ;
        this->setRect_of_me(rec) ;
    }
    else if (e->key() == Qt::Key_A) {this->_rec_of_me.move_rec(3) ; if (!this->can_put_me(_rec_of_me)) this->_rec_of_me.move_rec(4) ;}
    else if (e->key() == Qt::Key_D) {this->_rec_of_me.move_rec(4) ; if (!this->can_put_me(_rec_of_me)) this->_rec_of_me.move_rec(3) ;}
    else if (e->key() == Qt::Key_S) {this->_rec_of_me.move_rec(2) ; if (!this->can_put_me(_rec_of_me)) this->_rec_of_me.move_rec(1) ;}
    else if (e->key() == Qt::Key_W) {this->_rec_of_me.move_rec(1) ; if (!this->can_put_me(_rec_of_me)) this->_rec_of_me.move_rec(2) ;}
    else if (e->key() == Qt::Key_K) //矩形框移动到应该放小兵的位置
    {
        int x = this->_rec_of_me.getLT().getX() ;
        int y = this->_rec_of_me.getLT().getY() ;
        this->_game.addSol1(x,y) ;
        Point a(0,0),b(0,0) ; Rectangle null(a,b) ;
        this->setRect_of_me(null) ;
    }
    //自己放小兵


    else if (e->key() == Qt::Key_1)//左路放小兵
    {
        Point p1(7,4),p2(8,3) ;
        Rectangle rec(p1,p2) ;
        this->setRect_of_enemy(rec) ;
    }
    else if (e->key() == Qt::Key_3)//右路放小兵
    {
        Point p1(12,4),p2(13,3) ;
        Rectangle rec(p1,p2) ;
        this->setRect_of_enemy(rec) ;
    }
    else if (e->key() == Qt::Key_Up) {this->_rec_of_enemy.move_rec(1) ; if (!this->can_put_enemy(_rec_of_enemy)) this->_rec_of_enemy.move_rec(2) ;}
    else if (e->key() == Qt::Key_Down) {this->_rec_of_enemy.move_rec(2) ; if (!this->can_put_enemy(_rec_of_enemy)) this->_rec_of_enemy.move_rec(1) ;}
    else if (e->key() == Qt::Key_Right) {this->_rec_of_enemy.move_rec(4) ; if (!this->can_put_enemy(_rec_of_enemy)) this->_rec_of_enemy.move_rec(3) ;}
    else if (e->key() == Qt::Key_Left) {this->_rec_of_enemy.move_rec(3) ; if (!this->can_put_enemy(_rec_of_enemy)) this->_rec_of_enemy.move_rec(4) ;}
    else if (e->key() == Qt::Key_2) //矩形框移动到应该放小兵的位置
    {
        int x = this->_rec_of_enemy.getLT().getX() ;
        int y = this->_rec_of_enemy.getLT().getY() ;
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
                default: break ;
            }
        }
    }


    this->repaint();    

}


//下面是整个游戏的逻辑核心，最复杂的地方！！！
void MW1::march_of_soldiers()
{
    bool _over = 0 ;
    //判断小兵这一下能不能结束游戏

    vector <Soldier*> v = this->_game.getSol() ;
    vector <Soldier*>::iterator it ;
    //iterator 是迭代器，具体怎么回事看 note.cpp

    //对每个小兵单独进行操作
    for ( it = v.begin() ; it != v.end() ; )
    {
        int x = (*it)->getX() ; int y = (*it)->getY() ;//得到小兵的当前位置
        if ( this->_game.can_move((*it)) ) //小兵可移动，即没有遇到 Tower 和 Enemy 和敌人大本营
                {                    
                    if ( y == 22 && x <= 7 && x > 4)
                        (*it)->soldier_move(3,1) ;
                    else if ( x == 4 && y <= 22 && y >= 3)
                        (*it)->soldier_move(1,1) ;
                    else if ( y == 2 && x >= 4 && x < 7 )
                        (*it)->soldier_move(4,1) ;
                    else if ( y == 22 && x < 15 && x >= 12)
                        (*it)->soldier_move(4,1) ;
                    else if ( x == 15 && y <= 22 && y >= 3)
                        (*it)->soldier_move(1,1) ;
                    else if ( y == 2 && x <= 15 && x > 12)
                        (*it)->soldier_move(3,1) ;
                }//限定小兵的行进路线
        else
        {
            this->attack_enemy((*it)) ;
            this->attack_tower((*it)) ;


            {
                if ( x == 7 && y == 2 && this->_game.get_life_of_enemy() > 0 ) //（7,2）和（12,2）是可以攻击敌人大本营的小兵的坐标
                {
                    QTime time = QTime::currentTime() ;

                    if ( time.second()%2 == 1 ) this->_game.life_loss_of_enemy() ;
                }
                else if ( x == 12 && y == 2 && this->_game.get_life_of_enemy() > 0 )
                {
                    QTime time = QTime::currentTime() ;

                    if ( time.second()%2 == 1 ) this->_game.life_loss_of_enemy() ;
                }
                else if ( x == 7 && y == 2 && this->_game.get_life_of_enemy() <= 0 )
                {
                    _over = 1 ;//如果敌人大本营被干掉，这一关结束，后面 _over 有代码实现
                    break ;
                }
                else if ( x == 12 && y == 2 && this->_game.get_life_of_enemy() <= 0 )
                {
                    _over = 1 ;
                    break ;
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
                int x = (*it)->getPosX() ; int y = (*it)->getPosY() ;
                if (this->_game.can_move((*it)))
                {
                    if ( y == 23 && x < 7 && x >= 4)
                        (*it)->enemy_move(4,1) ;
                    else if ( x == 4 && y < 23 && y >= 3)
                        (*it)->enemy_move(2,1) ;
                    else if ( y == 3 && x > 4 && x <= 7 )
                        (*it)->enemy_move(3,1) ;
                    else if ( y == 23 && x <= 15 && x > 12)
                        (*it)->enemy_move(3,1) ;
                    else if ( x == 15 && y < 23 && y >= 3)
                        (*it)->enemy_move(2,1) ;
                    else if ( y == 3 && x < 15 && x >= 12)
                        (*it)->enemy_move(4,1) ;
                }
                else
                {
                    this->attack_soldier((*it)) ;
                    this->attack_base((*it)) ;

                    if ( x == 7 && y == 23 && this->_game.get_life_of_me() >0 )
                    {
                        QTime time = QTime::currentTime() ;

                        if ( time.second()%2 == 1 )
                            this->_game.life_loss_of_me() ;
                    }
                    else if ( x == 12 && y == 23 && this->_game.get_life_of_enemy() >0 )
                    {
                        QTime time = QTime::currentTime() ;

                        if ( time.second()%2 == 1 )
                            this->_game.life_loss_of_me() ;
                    }
                    else if ( x == 7 && y == 23 ) { _over = 1 ; break ;}
                    else if ( x == 12 && y == 23 ) { _over = 1 ; break ;}

                }
            }
        if (_over) this->_game.delete_world() ;

        this->repaint() ;
    }
}

void MW1::show_qi()
{
    int q1 = this->_game.get_life_of_me() ;
    int q2 = this->_game.get_life_of_enemy() ;
    this->ui->bar_of_qi_1->setValue(q1) ;
    this->ui->bar_of_qi_2->setValue(q2) ;
}

bool MW1::can_put_me(Rectangle rec)
{
    int x = rec.getLT().getX() ;
    int y = rec.getLT().getY() ;
    if ( x == 4 && y <= 22 && y >= 14 ) return 1 ;
    else if ( y == 22 && x >= 4 && x <= 7 ) return 1 ;
    else if ( x == 15 && y <= 22 && y >= 14) return 1 ;
    else if ( y == 22 && x >= 12 && x <= 15) return 1 ;
    return 0 ;
}

bool MW1::can_put_enemy(Rectangle rec)
{
    int x = rec.getLT().getX() ;
    int y = rec.getLT().getY() ;
    if ( x == 4 && y <=12 && y >= 3 ) return 1 ;
    else if ( y == 3 && x >= 4 && x <= 7 ) return 1 ;
    else if ( x == 15 && y <= 12 && y >= 3 ) return 1 ;
    else if ( y == 3 && x >= 12 && x <= 15 ) return 1 ;
    return 0 ;
}

void MW1::attack_enemy(Soldier *s)
{
    int x = s->getX() ;
    int y = s->getY() ;

    vector<Enemy *> v = this->_game.getEnemy() ;
    vector<Enemy *>::iterator it ;

    for ( it = v.begin() ; it != v.end() ; it++ )
    {
        int x1 = (*it)->getX() ; int y1 = (*it)->getY() ;
        if ((*it)->getLife() != 1 && x == x1 && y == y1+1)//判断攻击范围的同时判断敌兵还有多少血
                                                           //如果敌兵只有一滴血，直接被秒，不用 _life-- 了
        {
            QTime time = QTime::currentTime() ;//可以攻击
                                               //获取系统时间，每两秒干一滴血
                                               //每个小兵每次只能干一个敌兵一滴血，所以要 break
            if ( time.second()%2 == 1 )
            {
                (*it)->life_loss() ;
                break ;
            }
        }
        else if ((*it)->getLife() != 1 && x == x1 && y == y1 - 1 )
        {
            QTime time = QTime::currentTime() ;

            if ( time.second()%2 == 1 )
            {
                (*it)->life_loss() ;
                break ;
            }
        }
        else if ( x == x1 && y == y1+1 )
            this->_game.eraseObj((*it)->getX(),(*it)->getY()) ; //敌兵被干掉
        else if ( x == x1 && y == y1-1 )
            this->_game.eraseObj((*it)->getX(),(*it)->getY()) ;
    }
}

void MW1::attack_tower(Soldier *s)
{
    int x = s->getX() ;
    int y = s->getY() ;

    vector<Tower *> v = this->_game.getTow() ;
    vector<Tower *>::iterator it ;

    for ( it = v.begin() ; it != v.end() ; it++)
    {
        if ( !this->_game.tower_safe((*it)) )
        {
            int x1 = (*it)->getPosX() ; int y1 = (*it)->getPosY() ;
            if ((*it)->getLife() != 1 && x == x1 && y == y1+2 )
            {
                QTime time = QTime::currentTime() ;

                if ( time.second()%2 == 1 )
                {
                    (*it)->life_loss() ;
                    break ;
                }
            }
            else if ( x == x1 && y == y1+2 )
            {
                this->_game.eraseObj((*it)->getPosX(),(*it)->getPosY()) ;
                this->_game.addRuins((*it)->getPosX(),(*it)->getPosY()) ;
            }
        }
    }
}

void MW1::attack_base(Enemy *e)
{
    int x = e->getX() ;
    int y = e->getY() ;

    vector<Base *> v = this->_game.getBase() ;
    vector<Base *>::iterator it ;

    for ( it = v.begin() ; it != v.end() ; it++)
    {
        if ( !this->_game.base_safe((*it)) )
        {
            int x1 = (*it)->getPosX() ; int y1 = (*it)->getPosY() ;
            if ((*it)->getLife() != 1 && x == x1 && y == y1-1 )
            {
                QTime time = QTime::currentTime() ;

                if ( time.second()%2 == 1 )
                {
                    (*it)->life_loss() ;
                    break ;
                }
            }
            else if ( x == x1 && y == y1-1 )
            {
                this->_game.eraseObj((*it)->getPosX(),(*it)->getPosY()) ;
                this->_game.addRuins((*it)->getPosX(),(*it)->getPosY()) ;
            }
        }
    }
}

void MW1::attack_soldier(Enemy *e)
{
    int x = e->getX() ;
    int y = e->getY() ;

    vector<Soldier *> v = this->_game.getSol() ;
    vector<Soldier *>::iterator it ;

    for ( it = v.begin() ; it != v.end() ; it++)
    {
        int x1 = (*it)->getPosX() ; int y1 = (*it)->getPosY() ;
        if ((*it)->getLife() != 1 && x == x1 && y == y1-1)
        {
            QTime time = QTime::currentTime() ;

            if ( time.second()%2 == 1 )
            {
                (*it)->life_loss() ;
                break ;
            }
        }
        else if ((*it)->getLife() != 1 && x == x1 && y == y1+1)
        {
            QTime time = QTime::currentTime() ;

            if ( time.second()%2 == 1 )
            {
                (*it)->life_loss() ;
                break ;
            }
        }
        else if ( x == x1 && y == y1-1 )
        {
            this->_game.eraseObj((*it)->getX(),(*it)->getY()) ;
        }
        else if ( x == x1 && y == y1+1 )
        {
            this->_game.eraseObj((*it)->getX(),(*it)->getY()) ;
        }
    }
}

void MW1::on_start_button_clicked()
{
    ui->bar_of_qi_1->show() ;
    ui->bar_of_qi_2->show() ;

    ui->start_button ;

    this->_game.initWorld1() ;
    ui->start_button->deleteLater() ;
}


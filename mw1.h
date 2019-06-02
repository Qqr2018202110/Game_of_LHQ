#ifndef MW1_H
#define MW1_H

#include <QMainWindow>
#include <QImage>
#include <QPainter>
#include<QKeyEvent>
#include<QTimer>
#include <QProgressBar>

#include "rpgobj.h"
#include "world.h"
#include "soldier.h"
#include "enemy.h"
#include "base.h"
#include "rectangle.h"
#include <QPropertyAnimation>
#include "qlabel.h"

namespace Ui {
class MW1;
}

class MW1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MW1(QWidget *parent = 0);
    ~MW1();
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);

    void setRect_of_me(Rectangle rec) {this->_rec_of_me = rec ;}
    void setRect_of_enemy(Rectangle rec) {this->_rec_of_enemy = rec ;}

    bool can_put_me(Rectangle rec) ;
    bool can_put_enemy(Rectangle rec) ;

    void attack_enemy(Soldier * s) ;
    void attack_tower(Soldier * s) ;
    void attack_soldier(Enemy * e) ;
    void attack_base(Enemy * e) ;

    World getGame() { return _game ;}
    void show_attack(double x1,double,double,double);

protected slots:
    void march_of_soldiers();//己方士兵的移动
    void march_of_enemy() ;//敌兵的移动，如果两个移动函数合并的话整个函数就太复杂了，参数刚好是反的
    void add_qi()
    { this->_game.World::add_qi() ;}//气随时间增加的函数，因为在整个游戏进行过程中函数都在被调用，所以我专门声明了这个槽函数
                                    //实际上只是把 World 里面的接口放到这里来了，方便到时候用 connet

private slots:
    void show_qi() ;


    void on_start_button_clicked();

    //void on_qi_me_valueChanged(int value);

private:
    Ui::MW1 *ui;
    World _game;

    Rectangle _rec_of_me ;
    Rectangle _rec_of_enemy ;

    QTimer *timer1;
    QTimer *timer2;
    QTimer *timer3;
    QTimer *timer4;
    void drawline(double x1,double y1, double x2,double y2);

};

#endif // MW1_H

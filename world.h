#ifndef WORLD_H
#define WORLD_H
#include "tower.h"
#include "rpgobj.h"
#include <vector>
#include <string>
#include <QPainter>
#include "soldier.h"
#include "enemy.h"
#include "base.h"
#include "qmovie.h"
#include "qlabel.h"
#include <QImage>
#include<QKeyEvent>
#include<QTimer>
#include <QProgressBar>
#include <QTime>
#include <QObject>
#include <qobject.h>
#include "soldier1.h"
#include "soldier2.h"
#include "soldier3.h"
#include "enemy1.h"
#include "enemy2.h"
#include "enemy3.h"
#include "bullet.h"
#include <QPen>
#include <QFont>

class World
{
public:
    World(){}
    ~World();

    void initWrold0();//生成初始界面
    void initWorld1();//生成第一关
    void initWorld2();//通关之后生成第二关
    void initWorld3();

    void delete_world() ;//通关之后覆盖前一关的数据


    void show(QPainter * painter);

    vector<Soldier *> getSol() { return _soldier ;}
    vector<Tower *> getTow() {return _tower ;}
    vector<Enemy *> getEnemy() {return _enemy ;}
    vector<Base *> getBase() {return _base ;}
    vector<RPGObj *> getOth() {return _others ;}
    vector<Bullet *>& getBullet() {return _bullet ;}
    //返回这些 vector

    int get_qi_of_me() {return _qi_of_me ;}
    int get_qi_of_enemy() {return _qi_of_enemy ;}
    int get_life_of_me() {return _life_of_me ;}
    int get_life_of_enemy() {return _life_of_enemy ;}
    int get_rank() {return _rank ;}
    //返回这些值

    void life_loss_of_me(int x=2) {_life_of_me-=x ;}
    void life_loss_of_enemy(int x=2) {_life_of_enemy-=x ;}
    //掉血函数

    void eraseObj(double x, double y);
    //如果有东西被干掉了，就调用这个函数

    void addSol1(double x,double y) ;
    void addSol2(double x,double y) ;
    void addSol3(double x,double y) ;
    //自己的派兵函数
    void addEne1(double x,double y) ;
    void addEne2(double x,double y) ;
    void addEne3(double x,double y) ;
    //对方的派兵函数

    void addRuins(double x,double y) ;
    //某些东西被干掉之后，会有残骸。。。

    bool can_move(Soldier* s) ;
    bool can_move(Enemy *s) ;
    //自己的兵或者敌人的兵能不能动

    void add_qi()
    {
        if ( _qi_of_me <= 10)
            _qi_of_me ++ ;
        if ( _qi_of_enemy <= 10)
            _qi_of_enemy ++ ;
    }
    //重载加气函数，因为太简单，直接内联了

    bool tower_safe(Tower *tower ) ;
    bool base_safe(Base *base) ;
    int get_myscore(){return  _myscore;}
    int get_yourscore(){return  _yourscore;}
    void set_myscore(int x){_myscore=x;}
    void set_yourscore(int x){_yourscore=x;}
    void set_qi_of_me(int x){_qi_of_me=x;}
    void set_qi_of_enemy(int x){_qi_of_enemy=x;}


private:
    vector<Soldier *> _soldier ;
    vector<Tower *> _tower ;
    vector<Enemy *> _enemy ;
    vector<RPGObj *> _others ;
    vector<Base *> _base ;
    vector<Bullet *> _bullet ;
    //每个类一个 vector ，其他的放在 _others 里面

    QImage _background ;
    //背景图片
    QImage _Ali;
    QImage _Tencent;
    int _qi_of_me = 10 ;
    int _qi_of_enemy = 10 ;
    //两边的气

    int _life_of_me = 100 ;
    int _life_of_enemy = 100 ;
    //两边的生命值

    int _rank = 0 ;
    int _myscore=0;
    int _yourscore=0;
    //当前等级

};

#endif // WORLD_H

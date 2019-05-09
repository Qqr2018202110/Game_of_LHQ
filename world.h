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

class World
{
public:
    World(){}
    ~World();

    void initWrold0();//生成初始界面
    void initWorld1();//生成第一关
    void initWorld2();//通关之后生成第二关

    void delete_world() ;//通关之后覆盖前一关的数据


    void show(QPainter * painter);

    vector<Soldier *> getSol() { return _soldier ;}
    vector<Tower *> getTow() {return _tower ;}
    vector<Enemy *> getEnemy() {return _enemy ;}
    vector<Base *> getBase() {return _base ;}
    vector<RPGObj *> getOth() {return _others ;}
    //返回这些 vector

    int get_qi_of_me() {return _qi_of_me ;}
    int get_qi_of_enemy() {return _qi_of_enemy ;}
    int get_life_of_me() {return _life_of_me ;}
    int get_life_of_enemy() {return _life_of_enemy ;}
    int get_rank() {return _rank ;}
    //返回这些值

    void life_loss_of_me() {_life_of_me-- ;}
    void life_loss_of_enemy() {_life_of_enemy-- ;}
    //掉血函数

    void eraseObj(int x, int y);
    //如果有东西被干掉了，就调用这个函数

    void addSol1(int x,int y) ;
    //自己的派兵函数
    void addEne1(int x,int y) ;
    //对方的派兵函数

    void addRuins(int x,int y) ;
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


private:
    vector<Soldier *> _soldier ;
    vector<Tower *> _tower ;
    vector<Enemy *> _enemy ;
    vector<RPGObj *> _others ;
    vector<Base *> _base ;
    //每个类一个 vector ，其他的放在 _others 里面

    QImage _background ;
    //背景图片

    int _qi_of_me = 10 ;
    int _qi_of_enemy = 10 ;
    //两边的气

    int _life_of_me = 100 ;
    int _life_of_enemy = 100 ;
    //两边的生命值

    int _rank ;
    //当前等级


};

#endif // WORLD_H

#ifndef RPGOBJ_H
#define RPGOBJ_H
#include <QMediaPlayer>
#include <QImage>
#include <QPainter>
#include <string>
#include <icon.h>
#include <map>
#include "string.h"
using namespace std;
class RPGObj
{
public:
    RPGObj(){}

    void initObj(string type);
    void show(QPainter * painter);

    void setPosX(double x){this->_pos_x=x;}
    void setPosY(double y){this->_pos_y=y;}
    void set_life(int l){this->_life = l;}

    double getPosX() const{return this->_pos_x;}
    double getPosY() const{return this->_pos_y;}
    double getHeight() const{return this->_icon.getHeight();}
    double getWidth() const{return this->_icon.getWidth();}
    int getLife() const{return this->_life;}
    virtual void life_loss(RPGObj*){}
    virtual const char* getType(){}

    double getNextX(int direction);
    double getNextY(int direction);


    virtual void onErase();


    string getObjType() const{return this->_icon.getTypeName();}//返回类名

   int get_attackpower()
   {return _attackpower;}
   int get_getattackpower()
   {return _getattackpower;}
   void set_attackcount()
   {
       if(_attackcount==100)
           _attackcount=1;
       else
           _attackcount++;
   }
   int get_attackcount()
   {return _attackcount;}

protected:
    //所有坐标，单位均为游戏中的格

    QImage _pic;
    double _pos_x, _pos_y;//该物体在游戏中当前位置（左上角坐标）
    ICON _icon;//可以从ICON中获取对象的素材，尺寸等信息
    int _life = 50 ;
    int _attackpower;
    int _getattackpower;
private:
    int _attackcount=99;

};

#endif // RPGOBJ_H

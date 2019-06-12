#ifndef BASE_H
#define BASE_H

#include "rpgobj.h"

class Base : public RPGObj
{
public:
    Base() ;
    ~Base() ;
    void onErase(){}//这个可以先不理他
    void life_loss(RPGObj *r);
    void show(QPainter * painter,int x=0);

};

#endif // BASE_H

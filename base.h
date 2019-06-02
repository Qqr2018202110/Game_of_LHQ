#ifndef BASE_H
#define BASE_H

#include "rpgobj.h"

class Base : public RPGObj
{
public:
    Base() ;
    ~Base() ;
    void onErase();//这个可以先不理他
    void life_loss(RPGObj *r);
    const char* getType();

};

#endif // BASE_H

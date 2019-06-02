#ifndef TOWER_H
#define TOWER_H
#include "rpgobj.h"
#include <QMediaPlayer>

class Tower : public RPGObj
{
public:
    Tower();
    ~Tower();
    void onErase();//这个可以先不理他
    void life_loss(RPGObj *r);
    const char* getType();

};

#endif // TOWER

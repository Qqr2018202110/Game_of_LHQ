#ifndef SOLDIER1_H
#define SOLDIER1_H
#include "soldier.h"

class Soldier1 : public Soldier
{
public:
    Soldier1();
    ~Soldier1();
    const char* getType();
private:
    int _attackpower=1;
    int _getattackpower=1;
};

#endif // SOLDIER1_H

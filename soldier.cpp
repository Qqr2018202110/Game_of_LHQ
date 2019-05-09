#include "soldier.h"
#include "world.h"

//direction =1,2,3,4 for 上下左右
void Soldier::soldier_move(int direction, int step)
{
    if ( direction == 1 )
        _pos_y -= step ;
    else if ( direction == 2 )
        _pos_y += step ;
    else if ( direction == 3 )
        _pos_x -= step ;
    else if ( direction == 4 )
        _pos_x += step ;
}


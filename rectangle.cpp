#include <rectangle.h>
#include "point.h"
#include "line.h"
#include <cmath>
#include<algorithm>
#include<iostream>
#include <QPainter>
using namespace std;

Rectangle::Rectangle(Point &lb_pt, Point &rt_pt):
    _LB(lb_pt),
    _RT(rt_pt),
    _LT(_LB.getX(),_RT.getY()),
    _RB(_RT.getX(),_LB.getY()),
    _left_line(_LB,_LT),
    _right_line(_RB,_RT),
    _bottom_line(_LB,_RB),
    _top_line(_LT,_RT)
{}

Rectangle::Rectangle(const Rectangle &rec):
    _LB( rec._LB),
    _RT( rec._RT),
    _LT(_LB.getX(),_RT.getY()),
    _RB(_RT.getX(),_LB.getY()),
     _left_line(_LB,_LT),
     _right_line(_RB,_RT),
     _bottom_line(_LB,_RB),
     _top_line(_LT,_RT)
{

}
void Rectangle::show(QPainter & painter){
    this->_left_line.show(painter);
    this->_bottom_line.show(painter);
    this->_right_line.show(painter);
    this->_top_line.show(painter);
}

// direction = 1,2,3,4 意思是上下左右
void Rectangle::move_rec(int direction)
{
    switch (direction) {
    case 1:
        _LB=_LB.move_point(1);
        _LT=_LT.move_point(1);
        _RB=_RB.move_point(1);
        _RT=_RT.move_point(1);
        _left_line = _left_line.move_line(1) ;
        _right_line = _right_line.move_line(1) ;
        _top_line = _top_line.move_line(1) ;
        _bottom_line = _bottom_line.move_line(1) ;
        break ;
    case 2:
        _LB = _LB.move_point(2) ;
        _LT = _LT.move_point(2) ;
        _RB = _RB.move_point(2) ;
        _RT = _RT.move_point(2) ;
        _left_line = _left_line.move_line(2) ;
        _right_line = _right_line.move_line(2) ;
        _top_line = _top_line.move_line(2) ;
        _bottom_line = _bottom_line.move_line(2) ;
        break ;
    case 3:
        _LB = _LB.move_point(3) ;
        _LT = _LT.move_point(3) ;
        _RB = _RB.move_point(3) ;
        _RT = _RT.move_point(3) ;
        _left_line = _left_line.move_line(3) ;
        _right_line = _right_line.move_line(3) ;
        _top_line = _top_line.move_line(3) ;
        _bottom_line = _bottom_line.move_line(3) ;
        break ;
    case 4:
        _LB = _LB.move_point(4) ;
        _LT = _LT.move_point(4) ;
        _RB = _RB.move_point(4) ;
        _RT = _RT.move_point(4) ;
        _left_line = _left_line.move_line(4) ;
        _right_line = _right_line.move_line(4) ;
        _top_line = _top_line.move_line(4) ;
        _bottom_line = _bottom_line.move_line(4) ;
        break ;
    default:
        break ;

    }
}

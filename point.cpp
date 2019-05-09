#include "point.h"
#include <cmath>
#include<algorithm>
#include<iostream>
using namespace std;

Point::Point(const Point &p) {	//复制构造函数的实现
    _x = p._x;
    _y = p._y;
    //cout<< "Calling the copy constructor of Point"<<this->getX()<<","<<this->getY()<< endl;
}


int Point::getX(){
    return this->_x;
}
int Point::getY(){
    return this->_y;
}


Point Point::move_point(int direction)
{
    switch (direction) {
    case 1:
        _y -- ;
        break;
    case 2:
        _y ++ ;
        break ;
    case 3:
        _x -- ;
        break ;
    case 4:
        _x ++ ;
        break ;
    default:
        break ;
    }

    Point p(_x,_y) ;
    return p ;
}

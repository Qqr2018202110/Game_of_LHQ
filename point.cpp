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


double Point::getX(){
    return this->_x;
}
double Point::getY(){
    return this->_y;
}


Point Point::move_point(int direction)
{
    switch (direction)
    {
    case 1:
        _y -= 0.5 ;
        break;
    case 2:
        _y += 0.5 ;
        break ;
    case 3:
        _x -= 0.5 ;
        break ;
    case 4:
        _x += 0.5 ;
        break ;
    default:
        break ;
    }

    Point p(_x,_y) ;
    return p ;
}

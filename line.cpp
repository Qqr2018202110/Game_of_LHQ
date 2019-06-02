#include "line.h"
#include <QPainter>
#include <cmath>
#include<algorithm>
#include<iostream>
#include <math.h>
using namespace std;


Line::Line(Point &a, Point &b):_pa(a),_pb(b){
}

Line::Line (Line &l): _pa(l._pa), _pb(l._pb) {//组合类的复制构造函数
}

void Line::show(QPainter & painter){
    painter.save();
    int x1 = this->_pa.getX() * 32 ;
    int x2 = this->_pb.getX() * 32 ;
    int y1 = this->_pa.getY() * 32 ;
    int y2 = this->_pb.getY() * 32 ;

    painter.drawLine(x1,y1,x2,y2);
    painter.restore();
}

Line Line::move_line(int direction)
{
    switch (direction) {
    case 1:
        _pa = _pa.move_point(1) ;
        _pb = _pb.move_point(1) ;
        break ;
    case 2:
        _pa = _pa.move_point(2) ;
        _pb = _pb.move_point(2) ;
        break ;
    case 3:
        _pa = _pa.move_point(3) ;
        _pb = _pb.move_point(3) ;
        break ;
    case 4:
        _pa = _pa.move_point(4) ;
        _pb = _pb.move_point(4) ;
        break ;
    }
    Line l(_pa,_pb) ;
    return l ;
}


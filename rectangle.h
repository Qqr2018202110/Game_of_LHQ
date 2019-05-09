#ifndef RECTANGLE_H
#define RECTANGLE_H

#include<string.h>
#include "point.h"
#include "line.h"
#include <QPainter>

class Rectangle{
public:
    Rectangle(){}
    Rectangle (Point &lb_pt, Point &rt_pt);//两个输入参数分别是左下角，右上角
    Rectangle (const Rectangle &rec);
    void show(QPainter & painter);

    Point getLT() {return _LT ;}
    Point getLB() {return _LB ;}
    Point getRT() {return _RT ;}
    Point getRB() {return _RB ;}

    void move_rec(int direction) ;

private:
    Point _LB, _RT, _LT, _RB;//左下角，左上角，右下角，右上角
    Line _left_line, _right_line, _bottom_line, _top_line;
};

#endif // RECTANGLE_H

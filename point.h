#ifndef POINT_H
#define POINT_H


class Point{
public :
    Point(double xx = 0, double yy = 0) {
            _x = xx;
            _y = yy;
    }
    Point(const Point &p);
    Point move_point(int direction) ;

    double getX();
    double getY();
private:
    double _x  ;
    double _y  ;
};

#endif // POINT_H

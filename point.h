#ifndef POINT_H
#define POINT_H


class Point{
public :
    Point(int xx = 0, int yy = 0) {
            _x = xx;
            _y = yy;
    }
    Point(const Point &p);
    Point move_point(int direction) ;

    int getX();
    int getY();
private:
    int _x  ;
    int _y  ;
};

#endif // POINT_H

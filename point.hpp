/**
 * point.hpp: A point class (x,y,z) triple
 *
 * Author: Austin Hendrix
 */

#ifndef POINT_H
#define POINT_H

class Point {
   public:
      double x;
      double y;
      double z;
      Point(double xx, double yy, double zz) : x(xx), y(yy), z(zz) {}
};

#endif

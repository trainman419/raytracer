/**
 * objects.hpp: Some basic objects for a raytracer
 *
 * Author: Austin Hendrix
 */

#ifndef OBJECTS_H
#define OBJECTS_H

#include "point.hpp"
#include "object.hpp"

// sphere
class Sphere : public Object {
   public:
      Sphere(Point p, double rr) : c(p), r(rr) {}
      virtual double collide(Ray *);
      virtual Ray * reflect(Ray *);
      virtual Ray * transmit(Ray *);
      virtual Ray * absorb(Ray *);

   private:
      Point c; // center of sphere
      double r; // radius of sphere

      Point * intersect(Ray *);
      double angle(Ray *);

      virtual Point bound_min();
      virtual Point bound_max();
      virtual bool occupy(Point);
};

#endif

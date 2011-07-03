/**
 * objects.hpp: Some basic objects for a raytracer
 *
 * Author: Austin Hendrix
 */

#ifndef OBJECTS_H
#define OBJECTS_H

#include "point.hpp"
#include "object.hpp"
#include "optics.hpp"

// sphere
class Sphere : public Object {
   public:
      Sphere(Point p, double rr) : c(p), r(rr), film(NULL) {}
      virtual double collide(Ray *);
      virtual Spectrum * reflect(Spectrum *, double);
//      virtual Spectrum * transmit(Spectrum *, double);
//      virtual Spectrum * absorb(Spectrum *, double);

      virtual Ray * normal(Point);

      void setFilm(Film * f) { film = f; }

   private:
      Point c; // center of sphere
      double r; // radius of sphere
      Film * film; // surface film

      Point * intersect(Ray *);
      double angle(Ray *);

      virtual Point bound_min();
      virtual Point bound_max();
      virtual bool occupy(int x, int y, int z);
};

#endif

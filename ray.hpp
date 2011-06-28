/**
 * ray.hpp
 *
 * A class to represent rays in a raytracer
 *
 * Author: Austin Hendrix
 */

#ifndef RAY_H
#define RAY_H
#include <math.h>
#include "spectrum.hpp"
#include "point.hpp"

class Ray {
   public:
      Ray() : start(0,0,0), dir(1,1,1) { s = new WhiteSpectrum(); }
      Ray(Point d) : start(0,0,0), dir(d) { s = new WhiteSpectrum(); }
      Ray(Point a, Point d) : start(a), dir(d) { s = new WhiteSpectrum(); }
      ~Ray() { delete s; }

      Spectrum * getSpectrum() { return s; }
      Point getStart() { return start; }
      Point getDir() { return dir; }

      double length() { return sqrt((dir.x-start.x)*(dir.x-start.x) +
                                    (dir.y-start.y)*(dir.y-start.y) +
                                    (dir.z-start.z)*(dir.z-start.z)); }

   private:
      Spectrum * s;
      Point start;
      Point dir;
};

#endif

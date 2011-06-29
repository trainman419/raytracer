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

#include <stdio.h>

class Ray {
   public:
      Ray() : start(0,0,0), dir(1,1,1) { s = new WhiteSpectrum(); }
      Ray(Point d) : start(0,0,0), dir(d) { s = new WhiteSpectrum(); }
      Ray(Point a, Point d) : start(a), dir(d) { s = new WhiteSpectrum(); }
      ~Ray() { delete s; }

      Spectrum * getSpectrum() { return s; }
      Point getStart() { return start; }
      Point getDir() { return dir; }

      double length() const { return sqrt(dir.x*dir.x +
                                    dir.y*dir.y +
                                    dir.z*dir.z); }

      double dot(const Ray &o) const { return dir.x * o.dir.x + 
                                       dir.y * o.dir.y +
                                       dir.z * o.dir.z; }

      double angle(const Ray &o) const { 
         return acos(dot(o) / (length() * o.length())); }

      void print() { printf("(%lf, %lf, %lf) (%lf, %lf, %lf)\n",
            start.x, start.y, start.z, dir.x, dir.y, dir.z); }

   private:
      Spectrum * s;
      Point start;
      Point dir;
};

#endif

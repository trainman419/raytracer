/**
 * ray.hpp
 *
 * A class to represent rays in a raytracer
 *
 * Author: Austin Hendrix
 */

#ifndef RAY_H
#define RAY_H
#include "spectrum.hpp"

class Ray {
   public:
      Ray() : start(0,0,0), dir(1,1,1) { s = new WhiteSpectrum(); }
      ~Ray() { delete s; }

      Spectrum * getSpectrum() { return s; }
      Point getStart() { return start; }
      Point getDir() { return dir; }

   private:
      Spectrum * s;
      Point start;
      Point dir;
};

#endif

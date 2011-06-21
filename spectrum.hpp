/** spectrum.hpp
 *
 * A spectrum class for a raytracer
 *
 * Author: Austin Hendrix
 */

#ifndef SPECTRUM_H
#define SPECTRUM_H

#include <stdint.h>

// generic RGB triple
struct RGB {
   uint8_t r;
   uint8_t g;
   uint8_t b;

   public:
   RGB(uint8_t rr, uint8_t gg, uint8_t bb) : r(rr), g(gg), b(bb) {}
};

// base spectrum class
class Spectrum {
   public:

      virtual RGB toRGB() = 0;
};

// basic spectrum class for only white light
class WhiteSpectrum : public Spectrum {
   public:
      WhiteSpectrum() {};

      virtual RGB toRGB() { 
         return RGB((uint8_t)255, (uint8_t)255, (uint8_t)255);
      }
};

#endif

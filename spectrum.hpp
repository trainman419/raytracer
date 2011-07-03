/** spectrum.hpp
 *
 * A spectrum class for a raytracer
 *
 * Employs the 1931 CIE standard observer data sets from:
 *  http://www.cie.co.at/main/freepubs.html
 * And data from OpenFilters:
 *  http://www.polymtl.ca/larfis/English_Version/OF/OF_English.htm
 *
 * Author: Austin Hendrix
 */

#ifndef SPECTRUM_H
#define SPECTRUM_H

#include <stdint.h>

#include <map>

#include "approximation.hpp"

// generic RGB triple
struct sRGB {
   uint8_t r;
   uint8_t g;
   uint8_t b;

   public:
   sRGB(uint8_t rr, uint8_t gg, uint8_t bb) : r(rr), g(gg), b(bb) {}
};

// base spectrum class
class Spectrum {
   public:
      // convert to sRGB color space
      virtual sRGB tosRGB();

      Spectrum() { I.addPoint(300, 1.0); I.addPoint(830, 1.0); }
      Spectrum(Spectrum & s) : I(s.I) {}
      Spectrum(Spectrum * s) : I(s->I) {}
      Spectrum(Approximation & i) : I(i) {}

      virtual ~Spectrum() {}

      class const_iterator {
         private:
            double wvl;
            const_iterator(double d) : wvl(d) {}
            friend class Spectrum;

         public:
            const_iterator() : wvl(0.0) {}
            double operator*() { return wvl; }
            void operator++() { wvl += INC; }

            bool operator!=(const_iterator o) { return wvl != o.wvl; }
      };

      const_iterator begin() { return const_iterator(I.min()); }
      const_iterator end() { return const_iterator(I.max() + INC); }

   protected:
      // spectral power distribution
      //  for proper spectra, this will have many values at small increments
      //  for faster, less proper spectra, this could have a few values
      //   at wavelengths for R, G and B
      Approximation I;
      const static double INC = 1.0;
};

// basic spectrum class for only white light
class WhiteSpectrum : public Spectrum {
   public:
      WhiteSpectrum() {}
      virtual ~WhiteSpectrum() {}

      virtual sRGB tosRGB() { 
         return sRGB((uint8_t)255, (uint8_t)255, (uint8_t)255);
      }
};

// CIE 1931 standard observer at 1nm increments from 360nm to 830nm
class Observer {
   private:
      Observer();

      // singleton members and methods
      static Observer * t;

      static void init() {
         if(!t) {
            t = new Observer();
         }
      }
   public:
      struct f {
         double x;
         double y;
         double z;
      };

      static f bar2(int wvl);

   private:
      // TODO: replace the original implementation with proper Approximations
/*      Approximation x;
      Approximation y;
      Approximation z;
      */
      std::map<int, f> func;
};

#endif

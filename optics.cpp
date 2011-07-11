/**
 * optics.cpp
 *
 * Implementation of optics helper classes
 *
 * Author: Austin Hendrix
 */

#include "optics.hpp"
#include <math.h>
#include <complex>

#include <assert.h>
#include <stdio.h>

using namespace std;

//#define NM_TO_M(a) (a / 1000000000.0)
#define NM_TO_M(a) (a)

LayerMatrix LayerMatrix::operator*(const LayerMatrix o) const {
   return LayerMatrix(m11*o.m11 + m12*o.m21,
                   m11*o.m12 + m12*o.m22,
                   m21*o.m11 + m22*o.m21,
                   m21*o.m12 + m22*o.m22);
}

// wavelength in nm
LayerMatrix Layer::operator()(const double theta, const double wvl) const {
   double k = 2 * M_PI / (NM_TO_M(wvl)/(*idx)(wvl));
   // TODO: adjust thickness for angle of incidence and index?
   double L = NM_TO_M(thickness);
   double sigma = 2 * M_PI * NM_TO_M(thickness) * (*idx)(wvl) / NM_TO_M(wvl);
   assert(fabs(L*k - sigma) < 0.00000000000001);
   return LayerMatrix( cos(k*L)   , sin(k*L) / k,
                       -k*sin(k*L), cos(k*L)      );
}

// caching per-wavelength/angle transfer matrices doesn't seem to help
// optimization off: ~7.9s
// optimization on:  ~9.4s
//  caching resulting refelction value might, after we compute it

LayerMatrix Film::matrix(const double theta, const double wvl) const {
   LayerMatrix ret(1, 0, 0, 1);
   list<Layer>::const_iterator itr = layers.begin();
   ret = (*itr)(theta, wvl);
   for( itr++; itr != layers.end(); itr++ ) {
      //ret = (*itr)(wvl) * ret;
      ret = ret * (*itr)(theta, wvl);
   }
   return ret;
}

Spectrum * Film::transmit(const Spectrum * in, const double angle) const {
   Spectrum * ret = new Spectrum(in);
   Spectrum::const_iterator itr;
   for( itr = in->begin(); itr != in->end(); ++itr ) {
      LayerMatrix m = matrix(angle, *itr);
   }
   return ret;
}

Spectrum * Film::reflect(const Spectrum * in, const double angle) const {
   Approximation I;
   Spectrum::const_iterator itr;

   //fprintf(stderr, "%d layers\n", layers.size());
   for( itr = in->begin(); itr != in->end(); ++itr ) {
      // indicies of incident and subsrate materials
      double kL = 1.0;
      double kR = 1.0;
      LayerMatrix m = matrix(angle, *itr);
      complex<double> r = 
         complex<double>( m.m21 + kL*kR*m.m12, kL*m.m22 - kR*m.m11) / 
         complex<double>(-m.m21 + kL*kR*m.m12, kL*m.m22 + kR*m.m11);
      double R = r.real()*r.real() + r.imag()*r.imag();

      // TODO: fix so it doesn't ignore input spectrum
      I.addPoint(*itr, R * in->get(*itr));
      //I.addPoint(*itr, m.m11);
      // m11 varies with thickness and wavelength
      // m12 is zero
      // m21 varies with thickness and wavelength (decreasing envelope)
      // m22 varies like m11
   }
   Spectrum * ret = new Spectrum(I);
   return ret;
}

void Film::print() const {
   list<Layer>::const_iterator itr;
   for( itr = layers.begin(); itr != layers.end(); itr++ ) {
      printf("%09lf %03lf\n", itr->thickness, (*(itr->idx))(500));
   }
}

Spectrum * FakeFilm::reflect(const Spectrum * in, const double theta) const {
   Approximation I;
   Spectrum::const_iterator itr;
   for( itr = in->begin(); itr != in->end(); ++itr ) {
      double f = 0.0;

      // blue
      //if( *itr < 480 && *itr > 420 ) f = 1.0; // black/brown???

      // green
      //if( *itr < 590 && *itr > 520 ) f = 1.0; // red???

      // red
      //if( *itr < 700 && *itr > 660 ) f = 1.0; // purple???

      // on angle
      double low = 380 + 400*cos(theta);
      double high = 420 + 400*cos(theta);
      if( *itr < high && *itr > low ) f = 1.0;

      I.addPoint(*itr, f * in->get(*itr));
   }
   return new Spectrum(I);
}

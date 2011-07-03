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

using namespace std;

#define NM_TO_M(a) (a / 1000000000.0)

LayerMatrix LayerMatrix::operator*(const LayerMatrix o) const {
   return LayerMatrix(m11*o.m11 + m12*o.m21,
                   m11*o.m12 + m12*o.m22,
                   m21*o.m11 + m22*o.m21,
                   m21*o.m12 + m22*o.m22);
}

// wavelength in nm
LayerMatrix Layer::operator()(const double wvl) const {
   double k = 2 * M_PI / (NM_TO_M(wvl)/(*idx)(wvl));
   // TODO: adjust thickness for angle of incidence and index?
   double L = NM_TO_M(thickness);
   return LayerMatrix( cos(k*L)   , sin(k*L) / k,
                       -k*sin(k*L), cos(k*L)      );
}

// caching per-wavelength/angle transfer matrices doesn't seem to help
// optimization off: ~7.9s
// optimization on:  ~9.4s
//  caching resulting refelction value might, after we compute it
//#define OPTIMIZE

#ifdef OPTIMIZE
map<double, map<double, LayerMatrix> * > layerCache;
#endif

LayerMatrix Film::matrix(double theta, double wvl) {
   LayerMatrix ret(1, 0, 0, 1);
#ifdef OPTIMIZE
   map<double, LayerMatrix> * cache = layerCache[theta];
   if( cache == NULL ) {
      cache = new map<double, LayerMatrix>();
      layerCache[theta] = cache;
   }
   map<double, LayerMatrix>::const_iterator c_itr;
   if( (c_itr = cache->find(wvl)) != cache->end() ) {
      return c_itr->second;
   }
#endif
   list<Layer>::const_iterator itr = layers.begin();
   ret = (*itr)(wvl);
   for( itr++; itr != layers.end(); itr++ ) {
      ret = (*itr)(wvl) * ret;
   }
#ifdef OPTIMIZE
   cache->insert(map<double, LayerMatrix>::value_type(wvl, ret));
#endif
   return ret;
}

Spectrum * Film::transmit(Spectrum * in, double angle) {
   Spectrum * ret = new Spectrum(in);
   Spectrum::const_iterator itr;
   for( itr = in->begin(); itr != in->end(); ++itr ) {
      LayerMatrix m = matrix(angle, *itr);
   }
   return ret;
}

Spectrum * Film::reflect(Spectrum * in, double angle) {
   Approximation I;
   Spectrum::const_iterator itr;
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
      I.addPoint(*itr, R);
   }
   Spectrum * ret = new Spectrum(I);
   return ret;
}

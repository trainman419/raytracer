/**
 * optics.cpp
 *
 * Implementation of optics helper classes
 *
 * Author: Austin Hendrix
 */

#include "optics.hpp"
#include <math.h>

#define NM_TO_M(a) (a / 1000000000.0)

LayerMatrix LayerMatrix::operator*(const LayerMatrix o) const {
   return LayerMatrix(m11*o.m11 + m12*o.m21,
                   m11*o.m12 + m12*o.m22,
                   m21*o.m11 + m22*o.m21,
                   m21*o.m12 + m22*o.m22);
}

// wavelength in nm
LayerMatrix Layer::operator()(int wvl) {
   double k = 2 * M_PI / (NM_TO_M(wvl)/idx(wvl));
   // TODO: adjust thickness for angle of incidence and index?
   double L = NM_TO_M(thickness);
   return LayerMatrix( cos(k*L)   , sin(k*L) / k,
                       -k*sin(k*L), cos(k*L)      );
}

LayerMatrix Film::matrix(double theta, int wvl) {
}

Spectrum * Film::transmit(Spectrum * in, double angle) {
   Spectrum * out = new Spectrum();
}

Spectrum * Film::reflect(Spectrum * in, double angle) {
}

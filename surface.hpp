/**
 * surface.hpp: A class to represent a surface of an object
 *
 * This is where we represent thin films if we want them
 *
 * Author: Austin Hendrix
 */

#ifndef SURFACE_H
#define SUFRACE_H

#include "spectrum.hpp"
#include "optics.hpp"

// TODO: re-do this based on reflected/transmitted spectra and incidence angle
//  rather than rays

class Surface {
   public:
      virtual Spectrum * reflect(double) = 0;
      virtual Spectrum * transmit(double) = 0;
      virtual Spectrum * absorb(double) = 0;
      // TODO: diffusion
};

#endif

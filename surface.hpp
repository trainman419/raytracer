/**
 * surface.hpp: A class to represent a surface of an object
 *
 * This is where we represent thin films if we want them
 *
 * Author: Austin Hendrix
 */

#ifndef SURFACE_H
#define SUFRACE_H

class Surface {
   public:
      virtual Ray * reflect(Ray *) = 0;
      virtual Ray * transmit(Ray *) = 0;
      virtual Ray * absorb(Ray *) = 0;
      // TODO: diffusion
};

#endif

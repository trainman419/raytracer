/**
 * object.hpp: a base object class for a raytracer
 *
 * Author: Austin Hendrix
 */

#ifndef OBJECT_H
#define OBJECT_H

class World;

#include "ray.hpp"
#include "world.hpp"

class Object {
   public:
      // get the distance along the ray to the nearer collision point
      //  or return Inf/NaN for no collision
      virtual double collide(Ray *) = 0;
      virtual Spectrum * reflect(Spectrum *, double) = 0;
//      virtual Spectrum * transmit(Spectrum *, double) = 0;
//      virtual Spectrum * absorb(Spectrum *, double) = 0;

      // get normal to a point
      virtual Ray * normal(Point) = 0;
      // TODO diffuse

      // add this object to the world
      void addToWorld(World * w);

   private:
      // override this to provide minimum corner of bounding box
      virtual Point bound_min() = 0;
      // override this to provide maximum corner of bounding box
      virtual Point bound_max() = 0;
      // override this to test if the object's surface occupies a
      //  particular voxel
      virtual bool occupy(int x, int y, int z) = 0;
};

#endif

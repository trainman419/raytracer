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
      virtual bool collide(Ray *) = 0;
      virtual Ray * reflect(Ray *) = 0;
      virtual Ray * transmit(Ray *) = 0;
      virtual Ray * absorb(Ray *) = 0;
      // TODO diffuse

      // add this object to the world
      virtual void addToWorld(World * w) = 0;
};

#endif

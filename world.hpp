/**
 * world.hpp: A class to represent the world of the raytracer
 *
 * responsible for holding all of the objects and which regions they occupy
 *
 * Author: Austin Hendrix
 */

#ifndef WORLD_H
#define WORLD_H

class Object;

#include <list>
#include "object.hpp"
#include "spectrum.hpp"
#include "source.hpp"

class World {
   public:
      // get objects in ( [x, x+1), [y, y+1), [z, z+1) )
      // ( between x and the next-highest int )
      std::list<Object*> * getObjects(int x, int y, int x);

      World(int dx, int dy, int dz);
      ~World();

      // apply a light to the world
      void light(Source *);
      // minimum intensity a light must have to propagate
      double min_light;

      // trace a ray through the world
      sRGB trace(Ray *);
      // minimum percentage a ray must have to propagate
      double min_ray;
   private:
      std::list<Object*> **** w;
      int x;
      int y;
      int z;

      std::list<Source*> lights; // light sources
};

#endif

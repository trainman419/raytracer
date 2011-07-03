/**
 * world.cpp: Implementation of the world
 *
 * Author: Austin Hendrix
 */

#include <math.h>
#include <assert.h>

#include "world.hpp"

#include <stdio.h>

using namespace std;

World::World(int dx, int dy, int dz) {
   w = new list<Object*>***[dx];
   for( int i=0; i<dx; i++ ) {
      w[i] = new list<Object*>**[dy];
      for( int j=0; j<dy; j++ ) {
         w[i][j] = new list<Object*>*[dz];
         for( int k=0; k<dz; k++ ) {
            w[i][j][k] = new list<Object*>();
         }
      }
   }
   x = dx;
   y = dy;
   z = dz;

   min_light = 1.0;  // arbitrary
   min_ray = 0.1;    // 10%
}

World::~World() {
   for( int i=0; i<x; i++ ) {
      for( int j=0; j<y; j++ ) {
         for( int k=0; k<z; k++ ) {
            delete w[i][j][k];
         }
         delete w[i][j];
      }
      delete w[i];
   }
   delete w;
}

list<Object*> * World::getObjects(int x, int y, int z) {
   return w[x][y][z];
}

void World::light(Source * s) {
   lights.push_back(s);
}

sRGB World::trace(Ray * r) {
   // trace a ray through the world
   int sx, sy, sz;
   Point start = r->getStart();
   // ray direction
   Point u = r->getDir();
   {
      double l = r->length();
      u.x /= l;
      u.y /= l;
      u.z /= l;
   }
   int dx = u.x>0 ? 1 : u.x<0 ? -1 : 0;
   int dy = u.y>0 ? 1 : u.y<0 ? -1 : 0;
   int dz = u.z>0 ? 1 : u.z<0 ? -1 : 0;

   // truncate down
   sx = start.x;
   sy = start.y;
   sz = start.z;
   list<Object*> * objects;
   list<Object*>::iterator itr;
   Object * near = NULL;
   double dist;
   while( sz < x && sx >= 0 &&
          sy < y && sy >= 0 &&
          sz < z && sz >= 0 &&
          near == NULL ) {
      objects = w[sx][sy][sz];
      dist = INFINITY;
      for( itr = objects->begin(); itr != objects->end(); itr++ ) {
         double d = (*itr)->collide(r);
         if( !isinf(d) && d < dist ) {
            dist = d;
            near = *itr;
         }
      }
      // if we didn't hit anything, propagate to next voxel
      if( near == NULL ) {
         // solve for where our ray intersects the next voxel-boundary plane
         //  and pick the nearest point
         //  (add a little so that we are guaranteed to round down properly)
         double ts[3];
         ts[0] = ((sx+dx) - start.x)/u.x;
         ts[1] = ((sy+dy) - start.y)/u.y;
         ts[2] = ((sz+dz) - start.z)/u.z;
         double t = INFINITY;
         // gcc ought to unroll this
         for( int i=0; i<3; i++ ) {
            // check that result is a number, for degenerate cases
            if( isnormal(ts[i]) && ts[i] < t ) {
               t = ts[i];
            }
         }
         t += 0.0001;

         // increment our counters
         sx = (start.x + u.x*t);
         sy = (start.y + u.y*t);
         sz = (start.z + u.z*t);
      }
   }
   sRGB ret(0, 0, 0);
   if( near != NULL ) {
      Point intersect(start.x + u.x*dist, 
                      start.y + u.y*dist, 
                      start.z + u.z*dist);
      Ray * normal = near->normal(intersect);
      double theta = normal->angle(*r);
      // reverse angle since rays are pointing in opposite directions
      theta = M_PI - theta;
      delete normal;
      /* // sanity check
      if( fabs(theta) > (M_PI/2) ) {
         printf("Theta > pi: %lf\n", fabs(theta/(M_PI/2)));
      } */
      // TODO: fix mad hax
      char c = 255 * (1.0 - fabs(theta/(M_PI/2)));
      ret.r = c;
      ret.g = c;
      ret.b = c;
      assert(lights.front());
      Spectrum * s = near->reflect(lights.front(), theta);
      assert(s != NULL);
      ret = s->tosRGB();
      delete s;
   }
   return ret;
}

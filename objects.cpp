/**
 * obejcts.cpp: implementation of basic object classes
 *
 * Author: Austin Hendrix
 */

#include <math.h>
#include <assert.h>

#include "objects.hpp"

using namespace std;

// sphere

// get the first intersection point of a ray with this sphere
Point * Sphere::intersect(Ray * in) {
   Point p1 = in->getStart(); // P1
   Point d = in->getDir();    // P2 - P1
   // c                       // P3
   // From: http://paulbourke.net/geometry/sphereline/
   // u*d + p1 = closest point to c
   /*double u = ( (c.x - p1.x)*d.x + (c.y - p1.y)*d.y + (c.z - p1.z)*d.z ) /
      ( d.x*dx + d.y*d.y + d.z*d.z );
   // u > 0 implies point is on forward part of ray
   if( u > 0 ) {
      Point p;
      p.x = u*d.x + p1.x;
      p.y = u*d.y + p1.y;
      p.z = u*d.z + p1.z;
      // distance from point to center of sphere
      double dist = p.x*p.x + p.y*p.y + p.z*p.z;
      // if distance is within the sphere we actually have intersection
      if( dist <= r ) {
         // re-solve for values of u that are on surface of sphere
      }
   }*/
   double a = d.x*d.x + d.y*d.y + d.z*d.z;
   double b = 2 * (d.x*(p1.x-c.x) + d.y*(p1.y-c.y) + d.z*(p1.z-c.z) );
   double cc = c.x*c.x + c.y*c.y + c.z*c.z + p1.x*p1.x + p1.y*p1.y + 
      p1.z*p1.z - 2*(c.x*p1.x + c.y*p1.y + c.z*p1.z) - r*r;
   double root = b*b - 4*a*cc;
   // if root < 0; no intersection
   if( root < 0 ) {
      return NULL;
   } else if( root == 0.0 ) {
      // one root; one intersection
      return new Point(0,0,0);
   } else {
      // two roots; two intersections. pick the closer one
      return new Point(0,0,0);
   }
   return NULL;
}

double Sphere::collide(Ray * in) {
   Point p1 = in->getStart(); // P1
   Point d = in->getDir();    // P2 - P1
   // c                       // P3
   // From: http://paulbourke.net/geometry/sphereline/
   // u*d + p1 = closest point to c
   double a = d.x*d.x + d.y*d.y + d.z*d.z;
   double b = 2 * (d.x*(p1.x-c.x) + d.y*(p1.y-c.y) + d.z*(p1.z-c.z) );
   double cc = c.x*c.x + c.y*c.y + c.z*c.z + p1.x*p1.x + p1.y*p1.y + 
      p1.z*p1.z - 2*(c.x*p1.x + c.y*p1.y + c.z*p1.z) - r*r;
   double root = b*b - 4*a*cc;

   // length of input ray
   double dist = sqrt(d.x*d.x + d.y*d.y + d.z*d.z);
   // if root < 0; no intersection
   if( root < 0 ) {
      return INFINITY;
   } else if( root == 0.0 ) {
      // one root; one intersection
      root = -b / (2*a);
      if( root < 0 ) {
         return INFINITY;
      } else {
         return root*dist;
      }
   } else {
      // two roots; two intersections. pick the closer one
      double r1 = (-b + sqrt(root)) / (2*a);
      double r2 = (-b - sqrt(root)) / (2*a);
      if( r1 < 0 && r2 < 0 ) {
         return INFINITY;
      } else if( r1 < 0 ) {
         return r2*dist;
      } else if( r2 < 0 ) {
         return r1*dist;
      } else {
         return min(r1, r2)*dist;
      }
   }
}

// get the angle of intersection with the surface
double angle(Ray *) {
}

// get the reflected ray off of this sphere
Spectrum * Sphere::reflect(Spectrum * in, double theta) {
   if( film ) {
//      printf("reflecting ray off film at angle %lf\n", theta);
      return film->reflect(in, theta);
   } else {
      return new Spectrum(in);
   }
}

/*
Spectrum * Sphere::transmit(Spectrum * in, double theta) {
   assert(false);
   if( film )
      return film->transmit(in, theta);
   else
      return in;
}

Spectrum * Sphere::absorb(Spectrum * in, double theta) {
   assert(false);
   return new Spectrum(in);
}
*/

Point Sphere::bound_min() {
   return Point(c.x-r, c.y-r, c.z-r);
}

Point Sphere::bound_max() {
   return Point(c.x+r, c.y+r, c.z+r);
}

bool Sphere::occupy(int x, int y, int z) {
   int inside = 0;
   // TODO: fix this to work properly
   for( int i=x; i<x+2; i++ ) {
      for( int j=y; j<y+2; j++ ) {
         for( int k=z; k<z+2; k++ ) {
            double d = sqrt((i-c.x)*(i-c.x) +(j-c.y)*(j-c.y) +(k-c.z)*(k-c.z));
            if( d < r ) {
               inside++;
            }
         }
      }
   }
   // if all points are not inside or outside our sphere, the surface passes
   //  through this voxel
   return !(inside == 0 || inside == 8 );
}

Ray * Sphere::normal(Point p) {
   return new Ray(c, Point(p.x-c.x, p.y-c.y, p.z-c.z));
}

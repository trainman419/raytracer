/**
 * approximation.hpp
 *
 * An approximation of an arbitrary function by a series of data points,
 * usually read from a file.
 *
 * Author: Austin Hendrix
 */

#ifndef APPROXIMATION_H
#define APPROXIMATION_H

#include <map>

class Approximation {
   public:
      double operator()(const double) const;
      double min() const { return f.begin()->first; }
      double max() const { return f.rbegin()->first; }
      void addPoint(double x, double y) { f[x] = y; }
      Approximation() {};
      Approximation(Approximation & a) : f(a.f) {}
      Approximation(Approximation * a) : f(a->f) {}
   private:
      std::map<double, double> f; // data points in this approximation
};

#endif

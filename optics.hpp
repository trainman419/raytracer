/** optics.hpp
 *
 * Various optical helper calsses and formulae
 *
 * Author: Austin Hendrix
 */

#ifndef OPTICS_H
#define OPTICS_H

#include <list>
#include "spectrum.hpp"

class Index {
   public:
      virtual double operator()(double wvl) = 0;
};

class FixedIndex : public Index {
   public:
      virtual double operator()(double wvl) { return idx; }
      FixedIndex(double i) : idx(i) {}
   private:
      double idx;
};

class LayerMatrix {
   public:
      double m11;
      double m12;
      double m21;
      double m22;
      LayerMatrix(double a, double b, double c, double d) : m11(a), m12(b), m21(c), m22(d) {}
      LayerMatrix operator*(const LayerMatrix o) const;
};

class Layer {
   public:
      double thickness; // in nm
      Index * idx;

      Layer(double t, Index * i) : thickness(t), idx(i) {}
      LayerMatrix operator()(const double theta, const double wvl) const;
};

class Film {
   public:
      virtual Spectrum *transmit(const Spectrum *in, const double angle) const;
      virtual Spectrum *reflect(const Spectrum *in, const double angle) const;

      void addLayer(Layer l) {layers.push_back(l); }

      void print() const;
   private:
      std::list<Layer> layers;
      // TODO: cache calculation results?
      LayerMatrix matrix(const double theta, const double wvl) const;
};

class FakeFilm : public Film {
   public:
      virtual Spectrum *reflect(const Spectrum *in, const double angle) const;
};

#endif

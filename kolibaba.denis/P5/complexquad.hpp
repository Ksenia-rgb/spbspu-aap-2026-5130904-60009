#ifndef KOLIBABA_COMPLEXQUAD_HPP
#define KOLIBABA_COMPLEXQUAD_HPP

#include "shape.hpp"
#include <cstddef>

namespace kolibaba
{
  class Complexquad final: public Shape
  {
  public:
    Complexquad(const point_t& a, const point_t& b, const point_t& c, const point_t& d);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& pos) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;

  private:
    point_t vertices_[4];
    point_t center_;
    std::size_t crossing_;
  };
}

#endif

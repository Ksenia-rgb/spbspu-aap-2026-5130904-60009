#ifndef KOLIBABA_RECTANGLE_HPP
#define KOLIBABA_RECTANGLE_HPP

#include "shape.hpp"

namespace kolibaba
{
  class Rectangle final: public Shape
  {
  public:
    Rectangle(double width, double height, const point_t& center);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& pos) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;

  private:
    rectangle_t frame_;
  };
}

#endif

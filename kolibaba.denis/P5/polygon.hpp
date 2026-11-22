#ifndef KOLIBABA_POLYGON_HPP
#define KOLIBABA_POLYGON_HPP

#include "shape.hpp"
#include <cstddef>
#include <memory>

namespace kolibaba
{
  class Polygon final: public Shape
  {
  public:
    Polygon(const point_t* vertices, std::size_t count);
    Polygon(const Polygon& other);
    Polygon& operator=(const Polygon& other);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& pos) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;

  private:
    double signedDoubleArea() const;
    point_t getCenter() const;

    std::unique_ptr<point_t[]> vertices_;
    std::size_t count_;
  };
}

#endif

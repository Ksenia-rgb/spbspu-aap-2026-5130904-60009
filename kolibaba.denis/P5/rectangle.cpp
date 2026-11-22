#include "rectangle.hpp"
#include <cmath>
#include <stdexcept>

namespace kolibaba
{
  Rectangle::Rectangle(double width, double height, const point_t& center):
    frame_{width, height, center}
  {
    if (!std::isfinite(width) || !std::isfinite(height) || width <= 0.0 || height <= 0.0 ||
        !std::isfinite(center.x) || !std::isfinite(center.y))
    {
      throw std::invalid_argument("Invalid rectangle");
    }
  }

  double Rectangle::getArea() const
  {
    return frame_.width * frame_.height;
  }

  rectangle_t Rectangle::getFrameRect() const
  {
    return frame_;
  }

  void Rectangle::move(const point_t& pos)
  {
    frame_.pos = pos;
  }

  void Rectangle::move(double dx, double dy)
  {
    frame_.pos.x += dx;
    frame_.pos.y += dy;
  }

  void Rectangle::scale(double factor)
  {
    if (!std::isfinite(factor) || factor <= 0.0)
    {
      throw std::invalid_argument("Invalid scale factor");
    }
    frame_.width *= factor;
    frame_.height *= factor;
  }
}

#include "polygon.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <utility>

namespace kolibaba
{
  Polygon::Polygon(const point_t* vertices, std::size_t count):
    vertices_(new point_t[count]),
    count_(count)
  {
    if (vertices == nullptr || count < 3)
    {
      throw std::invalid_argument("Invalid polygon vertices");
    }
    for (std::size_t i = 0; i < count_; ++i)
    {
      if (!std::isfinite(vertices[i].x) || !std::isfinite(vertices[i].y))
      {
        throw std::invalid_argument("Invalid polygon vertex");
      }
      vertices_[i] = vertices[i];
    }
    if (signedDoubleArea() == 0.0)
    {
      throw std::invalid_argument("Polygon area must be positive");
    }
  }

  Polygon::Polygon(const Polygon& other):
    vertices_(new point_t[other.count_]),
    count_(other.count_)
  {
    for (std::size_t i = 0; i < count_; ++i)
    {
      vertices_[i] = other.vertices_[i];
    }
  }

  Polygon& Polygon::operator=(const Polygon& other)
  {
    if (this != &other)
    {
      Polygon copy(other);
      vertices_.swap(copy.vertices_);
      std::swap(count_, copy.count_);
    }
    return *this;
  }

  double Polygon::signedDoubleArea() const
  {
    double result = 0.0;
    for (std::size_t i = 0; i < count_; ++i)
    {
      const std::size_t j = (i + 1) % count_;
      result += vertices_[i].x * vertices_[j].y - vertices_[j].x * vertices_[i].y;
    }
    return result;
  }

  double Polygon::getArea() const
  {
    return std::abs(signedDoubleArea()) / 2.0;
  }

  point_t Polygon::getCenter() const
  {
    double x = 0.0;
    double y = 0.0;
    for (std::size_t i = 0; i < count_; ++i)
    {
      const std::size_t j = (i + 1) % count_;
      const double cross = vertices_[i].x * vertices_[j].y - vertices_[j].x * vertices_[i].y;
      x += (vertices_[i].x + vertices_[j].x) * cross;
      y += (vertices_[i].y + vertices_[j].y) * cross;
    }
    const double denominator = 3.0 * signedDoubleArea();
    return {x / denominator, y / denominator};
  }

  rectangle_t Polygon::getFrameRect() const
  {
    double minX = vertices_[0].x;
    double maxX = vertices_[0].x;
    double minY = vertices_[0].y;
    double maxY = vertices_[0].y;
    for (std::size_t i = 1; i < count_; ++i)
    {
      minX = std::min(minX, vertices_[i].x);
      maxX = std::max(maxX, vertices_[i].x);
      minY = std::min(minY, vertices_[i].y);
      maxY = std::max(maxY, vertices_[i].y);
    }
    return {maxX - minX, maxY - minY, {(minX + maxX) / 2.0, (minY + maxY) / 2.0}};
  }

  void Polygon::move(const point_t& pos)
  {
    const point_t center = getCenter();
    move(pos.x - center.x, pos.y - center.y);
  }

  void Polygon::move(double dx, double dy)
  {
    for (std::size_t i = 0; i < count_; ++i)
    {
      vertices_[i].x += dx;
      vertices_[i].y += dy;
    }
  }

  void Polygon::scale(double factor)
  {
    if (!std::isfinite(factor) || factor <= 0.0)
    {
      throw std::invalid_argument("Invalid scale factor");
    }
    const point_t center = getCenter();
    for (std::size_t i = 0; i < count_; ++i)
    {
      vertices_[i].x = center.x + (vertices_[i].x - center.x) * factor;
      vertices_[i].y = center.y + (vertices_[i].y - center.y) * factor;
    }
  }
}

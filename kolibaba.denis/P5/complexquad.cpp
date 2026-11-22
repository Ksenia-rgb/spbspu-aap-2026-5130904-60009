#include "complexquad.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace kolibaba
{
  namespace
  {
    bool findIntersection(const point_t& a, const point_t& b, const point_t& c,
        const point_t& d, point_t& result)
    {
      const double abx = b.x - a.x;
      const double aby = b.y - a.y;
      const double cdx = d.x - c.x;
      const double cdy = d.y - c.y;
      const double denominator = abx * cdy - aby * cdx;
      if (denominator == 0.0)
      {
        return false;
      }
      const double acx = c.x - a.x;
      const double acy = c.y - a.y;
      const double t = (acx * cdy - acy * cdx) / denominator;
      const double u = (acx * aby - acy * abx) / denominator;
      if (t <= 0.0 || t >= 1.0 || u <= 0.0 || u >= 1.0)
      {
        return false;
      }
      result = {a.x + t * abx, a.y + t * aby};
      return true;
    }

    double triangleArea(const point_t& a, const point_t& b, const point_t& c)
    {
      return std::abs((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x)) / 2.0;
    }
  }

  Complexquad::Complexquad(const point_t& a, const point_t& b, const point_t& c,
      const point_t& d):
    vertices_{a, b, c, d},
    center_{0.0, 0.0},
    crossing_(0)
  {
    for (const point_t& vertex: vertices_)
    {
      if (!std::isfinite(vertex.x) || !std::isfinite(vertex.y))
      {
        throw std::invalid_argument("Invalid quadrilateral vertex");
      }
    }
    if (findIntersection(vertices_[0], vertices_[1], vertices_[2], vertices_[3], center_))
    {
      crossing_ = 0;
    }
    else if (findIntersection(vertices_[1], vertices_[2], vertices_[3], vertices_[0], center_))
    {
      crossing_ = 1;
    }
    else
    {
      throw std::invalid_argument("Quadrilateral must have a self-intersection");
    }
  }

  double Complexquad::getArea() const
  {
    const std::size_t a = crossing_;
    return triangleArea(center_, vertices_[(a + 1) % 4], vertices_[(a + 2) % 4]) +
        triangleArea(center_, vertices_[(a + 3) % 4], vertices_[a]);
  }

  rectangle_t Complexquad::getFrameRect() const
  {
    double minX = vertices_[0].x;
    double maxX = vertices_[0].x;
    double minY = vertices_[0].y;
    double maxY = vertices_[0].y;
    for (const point_t& vertex: vertices_)
    {
      minX = std::min(minX, vertex.x);
      maxX = std::max(maxX, vertex.x);
      minY = std::min(minY, vertex.y);
      maxY = std::max(maxY, vertex.y);
    }
    return {maxX - minX, maxY - minY, {(minX + maxX) / 2.0, (minY + maxY) / 2.0}};
  }

  void Complexquad::move(const point_t& pos)
  {
    move(pos.x - center_.x, pos.y - center_.y);
  }

  void Complexquad::move(double dx, double dy)
  {
    for (point_t& vertex: vertices_)
    {
      vertex.x += dx;
      vertex.y += dy;
    }
    center_.x += dx;
    center_.y += dy;
  }

  void Complexquad::scale(double factor)
  {
    if (!std::isfinite(factor) || factor <= 0.0)
    {
      throw std::invalid_argument("Invalid scale factor");
    }
    for (point_t& vertex: vertices_)
    {
      vertex.x = center_.x + (vertex.x - center_.x) * factor;
      vertex.y = center_.y + (vertex.y - center_.y) * factor;
    }
  }
}

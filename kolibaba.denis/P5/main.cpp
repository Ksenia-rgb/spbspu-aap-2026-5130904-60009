#include "rectangle.hpp"
#include "complexquad.hpp"
#include "polygon.hpp"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <exception>
#include <iomanip>
#include <iostream>

namespace kolibaba
{
  void printRectangle(const rectangle_t& frame)
  {
    std::cout << "width=" << frame.width << ", height=" << frame.height
        << ", center=(" << frame.pos.x << ", " << frame.pos.y << ")\n";
  }

  void printFigures(Shape* const* figures, std::size_t count)
  {
    double totalArea = 0.0;
    rectangle_t firstFrame = figures[0]->getFrameRect();
    double minX = firstFrame.pos.x - firstFrame.width / 2.0;
    double maxX = firstFrame.pos.x + firstFrame.width / 2.0;
    double minY = firstFrame.pos.y - firstFrame.height / 2.0;
    double maxY = firstFrame.pos.y + firstFrame.height / 2.0;

    for (std::size_t i = 0; i < count; ++i)
    {
      const rectangle_t frame = figures[i]->getFrameRect();
      totalArea += figures[i]->getArea();
      const double left = frame.pos.x - frame.width / 2.0;
      const double right = frame.pos.x + frame.width / 2.0;
      const double bottom = frame.pos.y - frame.height / 2.0;
      const double top = frame.pos.y + frame.height / 2.0;
      minX = std::min(minX, left);
      maxX = std::max(maxX, right);
      minY = std::min(minY, bottom);
      maxY = std::max(maxY, top);
      std::cout << "Figure " << i + 1 << ": area=" << figures[i]->getArea() << ", frame: ";
      printRectangle(frame);
    }
    std::cout << "Total area: " << totalArea << "\nOverall frame: ";
    printRectangle({maxX - minX, maxY - minY, {(minX + maxX) / 2.0, (minY + maxY) / 2.0}});
  }

  void scaleFigures(Shape* const* figures, std::size_t count, const point_t& pivot, double factor)
  {
    for (std::size_t i = 0; i < count; ++i)
    {
      const rectangle_t before = figures[i]->getFrameRect();
      figures[i]->scale(factor);
      const rectangle_t after = figures[i]->getFrameRect();
      const double targetX = pivot.x + (before.pos.x - pivot.x) * factor;
      const double targetY = pivot.y + (before.pos.y - pivot.y) * factor;
      figures[i]->move(targetX - after.pos.x, targetY - after.pos.y);
    }
  }
}

int main()
{
  try
  {
    kolibaba::Rectangle rectangle(4.0, 2.0, {0.0, 0.0});
    kolibaba::Complexquad quadrilateral({-4.0, -1.0}, {0.0, 3.0}, {-4.0, 3.0}, {0.0, -1.0});
    const kolibaba::point_t vertices[] = {
      {1.0, 1.0}, {5.0, 1.0}, {5.0, 4.0}, {3.0, 2.0}, {1.0, 4.0}
    };
    kolibaba::Polygon polygon(vertices, sizeof(vertices) / sizeof(vertices[0]));
    kolibaba::Polygon secondPolygon(polygon);
    secondPolygon.move({7.0, -3.0});
    kolibaba::Shape* figures[] = {&rectangle, &quadrilateral, &polygon, &secondPolygon};
    const std::size_t count = sizeof(figures) / sizeof(figures[0]);

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Before scaling:\n";
    kolibaba::printFigures(figures, count);

    kolibaba::point_t pivot{};
    double factor = 0.0;
    std::cout << "Enter pivot x y and scale factor: ";
    if (!(std::cin >> pivot.x >> pivot.y >> factor) || !std::isfinite(pivot.x) ||
        !std::isfinite(pivot.y) || !std::isfinite(factor) || factor <= 0.0)
    {
      std::cerr << "Error: invalid scaling parameters\n";
      return 1;
    }

    kolibaba::scaleFigures(figures, count, pivot, factor);
    std::cout << "After scaling:\n";
    kolibaba::printFigures(figures, count);
  }
  catch (const std::exception& error)
  {
    std::cerr << "Error: " << error.what() << '\n';
    return 1;
  }
  return 0;
}

#ifndef KOLIBABA_BASE_TYPES_HPP
#define KOLIBABA_BASE_TYPES_HPP

namespace kolibaba
{
  struct point_t
  {
    double x;
    double y;
  };

  struct rectangle_t
  {
    double width;
    double height;
    point_t pos;
  };
}

#endif

#include <iostream>
#include <limits>

namespace shulzhenko
{
  constexpr int success = 0;
  constexpr int invalid_input = 1;
  constexpr int impossible_calculate = 2;
  constexpr int max_count = std::numeric_limits< int >::max();

  int laba()
  {
    int last = 0, cur = 0, next = 0;
    int inq_seq = 0;
    int grt_lss = 0;
    bool inq_overflow = false;
    bool grt_overflow = false;
    bool zero_reached = false;

    while (std::cin >> next)
    {
      if (next == 0)
      {
        zero_reached = true;
        break;
      }

      if (cur != 0)
      {
        if (last != 0 && cur < last && cur > next)
        {
          if (grt_lss == max_count)
          {
            grt_overflow = true;
          }
          grt_lss += 1;
        }
      }

      last = cur;
      cur = next;

      if (last != 0 && cur > last)
      {
        if (inq_seq == max_count)
        {
          inq_overflow = true;
        }
        inq_seq += 1;
      }
    }

    if (next != 0 || std::cin.fail())
    {
      std::cerr << "Error: invalid input\n";
      return invalid_input;
    }

    if (!zero_reached)
    {
      std::cerr << "Error: invalid input\n";
      return invalid_input;
    }

    if (inq_overflow)
    {
      std::cerr << "Error: overflow\n";
      return impossible_calculate;
    }
    else
    {
      std::cout << inq_seq << '\n';
    }

    if (grt_overflow)
    {
      std::cerr << "Error: overflow\n";
      return impossible_calculate;
    }
    else
    {
      std::cout << grt_lss << '\n';
    }

    return success;
  }

}

int main()
{
  return shulzhenko::laba();
}

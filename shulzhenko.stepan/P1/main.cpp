#include <iostream>
#include <limits>

namespace shulzhenko
{
  constexpr int success = 0;
  constexpr int invalid_input = 1;
  constexpr int impossible_calculate = 2;
  constexpr int max_count = std::numeric_limits<int>::max();

  int laba()
  {
    int last = 0, cur = 0, next = 0;
    int inq_seq = 0;
    int grt_lss = 0;

    while (std::cin >> next)
    {
      if (next == 0)
      {
        break;
      }

      if (cur != 0)
      {
        if (last != 0 && cur < last && cur > next)
        {
          if (grt_lss == max_count)
          {
            std::cerr << "Error: overflow\n";
            return impossible_calculate;
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
          std::cerr << "Error: overflow\n";
          return impossible_calculate;
        }
        inq_seq += 1;
      }
    }

    if (next != 0 || std::cin.fail())
    {
      std::cerr << "Error: invalid input\n";
      return invalid_input;
    }

    std::cout << inq_seq << std::endl;
    std::cout << grt_lss << std::endl;
    return success;
  }

}

int main()
{
  return shulzhenko::laba();
}

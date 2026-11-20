#include <iostream>
#include <limits>

namespace drugov
{
  const int ERROR_INVALID_INPUT = 1;
  const int ERROR_CALCULATION = 2;

  int process()
  {
    int n = 0;
    int old_n = 0;

    if (not(std::cin >> n))
    {
      std::cerr << "invalid input\n";
      return ERROR_INVALID_INPUT;
    }

    if (n == 0)
    {
      std::cout << 0 << "\n" << 0 << "\n";
      return 0;
    }

    int max_four = 1;
    int cur_four = 1;
    int max_six = 1;
    int cur_six = 1;

    old_n = n;
    std::cin >> n;

    while (n != 0)
    {
      if (!std::cin)
      {
        std::cerr << "invalid input\n";
        return ERROR_INVALID_INPUT;
      }

      if (n == old_n)
      {
        if (cur_four == std::numeric_limits< decltype(cur_four) >::max())
        {
          std::cerr << "overflow error\n";
          return ERROR_CALCULATION;
        }
        cur_four++;
      }
      else
      {
        cur_four = 1;
      }

      if (cur_four > max_four)
      {
        max_four = cur_four;
      }

      if (n >= old_n)
      {
        if (cur_six == std::numeric_limits< decltype(cur_six) >::max())
        {
          std::cerr << "overflow error\n";
          return ERROR_CALCULATION;
        }
        cur_six++;
      }
      else
      {
        cur_six = 1;
      }

      if (cur_six > max_six)
      {
        max_six = cur_six;
      }

      old_n = n;
      std::cin >> n;
    }

    std::cout << max_four << "\n" << max_six << "\n";
    return 0;
  }
}

int main()
{
  return drugov::process();
}

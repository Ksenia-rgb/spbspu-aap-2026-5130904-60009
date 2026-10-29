#include <iostream>

namespace drugov
{
  int process()
  {
    int n = 0;
    int old_n = 0;
    std::cin >> n;

    if (!std::cin)
    {
      std::cerr << "invalid input\n";
      return 1;
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
        return 1;
      }

      if (n == old_n)
      {
        cur_four = cur_four + 1;
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
        cur_six = cur_six + 1;
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


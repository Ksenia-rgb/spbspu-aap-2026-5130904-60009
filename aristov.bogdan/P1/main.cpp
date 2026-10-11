#include <iostream>

namespace aristov
{
  int run()
  {
    int x = 0;
    if (!(std::cin >> x))
    {
      std::cerr << "Invalid input\n";
      return 1;
    }

    int max = 0;
    int second = 0;
    int prev = 0;
    int sign_changes = 0;
    bool has_value = false;
    bool has_second = false;

    while (x != 0)
    {
      if (!has_value)
      {
        max = x;
        prev = x;
        has_value = true;
      }
      else
      {
        if ((prev > 0 && x < 0) || (prev < 0 && x > 0))
        {
          ++sign_changes;
        }

        if (x > max)
        {
          second = max;
          max = x;
          has_second = true;
        }
        else if (!has_second || x > second)
        {
          second = x;
          has_second = true;
        }

        prev = x;
      }

      if (!(std::cin >> x))
      {
        std::cerr << "Invalid input\n";
        return 1;
      }
    }

    if (!has_second)
    {
      std::cerr << "Cannot calculate SUB-MAX\n";
    }
    else
    {
      std::cout << second << '\n';
    }

    std::cout << sign_changes << '\n';

    if (!has_second)
    {
      return 2;
    }
    return 0;
  }
}

int main()
{
  return aristov::run();
}

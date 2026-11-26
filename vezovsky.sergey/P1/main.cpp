#include <iostream>

namespace vezovsky {

  constexpr int success = 0;
  constexpr int error = 1;
  constexpr int few = 2;

  int count()
  {
    int current = 0;
    int prev = 0;
    int prevprev = 0;

    int count = 0;
    int sum = 0;
    int increase = 0;

    while (std::cin >> current && current != 0) {
      ++count;

      if (count >= 3 && prevprev + prev == current) {
        ++sum;
      }

      if (count >= 2 && current > prev) {
        ++increase;
      }

      prevprev = prev;
      prev = current;
    }

    if (std::cin.fail()) {
      std::cerr << "Input error." << '\n';
      return error;
    }

    if (count < 3) {
      std::cerr << "Not enough data." << '\n';
      return few;
    }

    std::cout << sum << '\n';
    std::cout << increase << '\n';

    return success;
  }
}

int main()
{
  return vezovsky::count();
}

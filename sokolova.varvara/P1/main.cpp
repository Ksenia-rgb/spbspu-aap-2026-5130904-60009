#include <iostream>

namespace sokolova {
  int maxDecreasingLength()
  {
    int n = 0;
    std::cin >> n;

    if (n == 0) {
      return 0;
    }

    int prev = n;
    int len = 1;
    int max_len = 1;

    while (std::cin >> n && n != 0) {
      if (n <= prev) {
        len++;
      } else {
        len = 1;
      }

      if (len > max_len) {
        max_len = len;
      }

      prev = n;
    }

    std::cout << max_len << std::endl;
    return 0;
  }

  int number4()
  {
    int x = 0;
    std::cin >> x;

    if (x == 0) {
      std::cout << 0;
      return 0;
    }

    int prev = x;
    int len = 1;
    int max_len = 1;

    while (std::cin >> x && x != 0) {
      if (x == prev) {
        len++;
      } else {
        len = 1;
      }

      if (len > max_len) {
        max_len = len;
      }

      prev = x;
    }

    std::cout << max_len << std::endl;
    return 0;
  }
}

int main()
{
  return sokolova::maxDecreasingLength();
  return sokolova::number4();
  return 0;
}

#include <iostream>

namespace sokolova {
  int maxDecreasingLength()
  {
    int n;
    std::cin >> n;

    if (n == 0) {
      return 0;
    }

    int prev = n;
    int len = 1;
    int maxLen = 1;

    while (std::cin >> n && n != 0) {
      if (n <= prev) {
        len++;
      } else {
        len = 1;
      }

      if (len > maxLen) {
        maxLen = len;
      }

      prev = n;
    }

    std::cout << maxLen << std::endl;
    return 0;
  }

  int number4()
  {
    int x;
    std::cin >> x;

    if (x == 0) {
      std::cout << 0;
      return 0;
    }

    int prev = x;
    int len = 1;
    int maxLen = 1;

    while (std::cin >> x && x != 0) {
      if (x == prev) {
        len++;
      } else {
        len = 1;
      }

      if (len > maxLen) {
        maxLen = len;
      }

      prev = x;
    }

    std::cout << maxLen << std::endl;
    return 0;
  }
}

int main()
{
  return sokolova::maxDecreasingLength();
  return sokolova::number4();
  return 0;
}

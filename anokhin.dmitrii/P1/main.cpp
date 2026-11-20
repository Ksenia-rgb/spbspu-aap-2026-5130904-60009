#include <iostream>
int main()
{
  int a = 0;
  int max_val = 0;
  int count_max = 0;
  int prev = 0;
  int len = 0;
  int max_len = 0;

  while (std::cin >> a && a != 0) {
    if (len == 0) {
      max_val = a;
      count_max = 1;
      prev = a;
      len = 1;
      max_len = 1;
    } else {
      if (a > max_val) {
        max_val = a;
        count_max = 1;
      } else if (a == max_val) {
        count_max++;
      }

      if (a == prev) {
        len++;
      } else {
        len = 1;
      }

      if (len > max_len) {
        max_len = len;
      }

      prev = a;
    }
  }

  if (!std::cin.eof() && std::cin.fail()) {
    std::cerr << "Input error\n";
    return 1;
  }

  if (len == 0) {
    std::cerr << "Cannot calculate CNT-MAX\n";
    std::cout << 0 << '\n';
    return 2;
  }

  std::cout << count_max << '\n';
  std::cout << max_len << '\n';

  return 0;
}

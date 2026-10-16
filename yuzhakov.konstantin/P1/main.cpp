#include <iostream>
namespace yuzhakov {
  using ull = unsigned long long;
  constexpr int calculate_error = 2;
  constexpr int invalid_input = 1;
  constexpr int success = 0;

  int p1()
  {
    int s1 = 0;
    if (!(std::cin >> s1)) {
      std::cerr << "invalid input" << "\n";
      return invalid_input;
    }
    if (s1 == 0) {
      std::cout << "0" << "\n";
      std::cerr << "calculate error" << "\n";
      return calculate_error;
    }

    int s2 = 0;
    if (!(std::cin >> s2)) {
      std::cerr << "invalid input" << "\n";
      return invalid_input;
    }
    if (s2 == 0) {
      std::cout << "0" << "\n";
      std::cout << "0" << "\n";
      return success;
    }

    ull c7 = 0, c13 = 0;
    int s3 = 0;

    while (std::cin >> s3) {
      if (s3 == 0) {
        break;
      }
      if (s1 < s2 && s2 > s3) {
        c7++;
      }
      long long const a = s1;
      long long const b = s2;
      long long const c = s3;
      if ((c * c - b * b) == a * a) {
        c13++;
      }
      s1 = s2;
      s2 = s3;
    }

    if (!(std::cin)) {
      std::cerr << "invalid input" << "\n";
      return invalid_input;
    }

    std::cout << c7 << "\n";
    std::cout << c13 << "\n";
    return success;
  }
}
int main()
{
  return yuzhakov::p1();
}

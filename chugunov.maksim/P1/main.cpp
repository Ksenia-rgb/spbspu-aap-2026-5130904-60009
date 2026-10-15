#include <iostream>

namespace chugunov {

  bool readNum(int &x)
  {
    if (std::cin >> x) {
      return true;
    }
    return false;
  }

}

int main()
{
  int x = 0;
  int prev = 0;
  int count = 0;
  int max1 = 0, max2 = 0;
  bool have_max1 = false;
  bool have_max2 = false;
  int div_count = 0;

  while (true) {
    if (!chugunov::readNum(x)) {
      std::cerr << "not a seq" << std::endl;
      return 1;
    }

    if (x == 0) {
      break;
    }

    if (!have_max1) {
      max1 = x;
      have_max1 = true;
    } else if (x > max1) {
      max2 = max1;
      have_max2 = true;
      max1 = x;
    } else if (x == max1) {
      max2 = x;
      have_max2 = true;
    } else {
      if (!have_max2 || x > max2) {
        max2 = x;
        have_max2 = true;
      }
    }

    if (count > 0) {
      if (x % prev == 0) {
        div_count = div_count + 1;
      }
    }

    prev = x;
    count = count + 1;
  }

  char c = 0;
  while (std::cin.get(c)) {
    if (c != ' ' && c != '\n' && c != '\t' && c != '\r') {
      std::cerr << "not a seq" << std::endl;
      return 1;
    }
  }

  int code = 0;
  if (count >= 2 && have_max2) {
    std::cout << max2 << std::endl;
  } else {
    std::cerr << "cant find second max" << std::endl;
    code = 2;
  }

  if (count >= 2) {
    std::cout << div_count << std::endl;
  } else {
    std::cerr << "cant count divs" << std::endl;
    code = 2;
  }

  return code;
}

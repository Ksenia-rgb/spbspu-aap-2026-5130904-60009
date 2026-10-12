#include <iostream>

int podschet()
{
  int a = 1, b = 0, chet = 0, c1 = 0, c2 = 0, chet2 = 0;
  while (true) {
    std::cin >> a;
    if (std::cin.fail()) {
      return 1;
    }
    if (a == 0) {
      break;
    }
    b++;
    if ((long long)c1 + c2 == a && b >= 3) {
      chet++;
    }
    if (b >= 2 && a > c2) {
      chet2++;
    }

    c1 = c2;
    c2 = a;
  }
  int res = 0;
  if (b >= 3) {
    std::cout << chet << "\n";
  } else {
    res = 2;
  }
  std::cout << chet2 << "\n";
  return res;
}

int main()
{
  return podschet();
}

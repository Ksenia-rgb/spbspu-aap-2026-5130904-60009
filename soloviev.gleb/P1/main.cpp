#include <iostream>

void variant1(int a, int b[3], int *c) {
  if (b[0] != 0) {
    if (a > b[0]) {
      (*c)++;
    }
  }
  b[0] = a;
}
void variant3(int a, int b[3], int *c) {
  if ((*c) < 0) {
    b[1] = a;
    (*c) = 1;
  } else if (a > b[1]) {
    b[1] = a;
    (*c) = 1;
  } else if (a == b[1]) {
    (*c)++;
  }
}
int main() {
  void (*const fn[2])(int, int *, int *) = {variant1, variant3};
  const char *const varnames[2] = {"Variant 1", "Variant 3"};
  int rs[2] = {0, -1};
  int cyclst[3] = {0};
  while (true) {
    int a = 0;
    std::cin >> a;
    if (std::cin.fail() || std::cin.eof()) {
      std::cerr << "input error";
      return 1;
    }
    if (a == 0) {
      break;
    }
    for (int i = 0; i < 2; i++) {
      fn[i](a, cyclst, rs + i);
    }
  }
  bool err = false;
  for (int i = 0; i < 2; i++) {
    if (rs[i] < 0) {
      std::cerr << varnames[i] << ": cannot compute" << std::endl;
      err = true;
    } else {
      std::cout << rs[i] << std::endl;
    }
  }
  return err ? 2 : 0;
}

#include <iostream>
#include <stdexcept>

namespace stamboliyski {
int *EnterNums() {
  int num = 0;
  size_t count = 0;
  int *p = nullptr;
  if (!(std::cin >> num)) {
    throw std::invalid_argument("Invalid argument");
  }
  if (num == 0) {
    p = new int[1];
  }
  while (num != 0) {
    if (p == nullptr) {
      p = new int[1];
      p[0] = num;
    }
    count += 1;
    int *temp = new int[count];
    for (size_t i = 0; i < count; i++) {
      temp[i] = p[i];
    }
    temp[count - 1] = num;
    delete[] p;
    p = new int[count + 1];
    for (size_t i = 0; i < count; i++) {
      p[i] = temp[i];
    }
    delete[] temp;
    if (!(std::cin >> num)) {
      throw std::invalid_argument("ERROR");
    }
  }
  p[count] = 0;
  return p;
}

int Zad6(int *p) {
  if (p[0] == 0) {
    return 0;
  }
  int count = 0;
  int countnums = 0;
  int highnum = 0;
  int temp = p[0];
  while (p[count] != 0) {
    if (p[count] >= temp) {
      countnums++;
    } else {
      countnums = 1;
    }
    temp = p[count];
    count++;
    if (countnums > highnum) {
      highnum = countnums;
    }
  }
  return highnum;
}

int Zad16(int *p) {
  if (p[0] == 0) {
    return 0;
  }
  int count = 0;
  int smallestnum = p[0];
  int smallestnumcounter = 0;
  while (p[count] != 0) {
    if (p[count] < smallestnum) {
      smallestnum = p[count];
    }
    count++;
  }
  count = 0;
  while (p[count] != 0) {
    if (p[count] == smallestnum) {
      smallestnumcounter++;
    }
    count++;
  }
  return smallestnumcounter;
}
} // namespace stamboliyski
int main() {
  int *nums = nullptr;
  try {
    nums = stamboliyski::EnterNums();
  } catch (const std::invalid_argument &a) {
    std::cerr << "Program terminated with error code: 1\n";
    return 1;
  }
  std::cout << "Output from 6.  : " << stamboliyski::Zad6(nums) << "\n";
  std::cout << "Output from 16. : " << stamboliyski::Zad16(nums) << "\n";
  return 0;
}

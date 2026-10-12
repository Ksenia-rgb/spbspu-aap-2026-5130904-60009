#include <iostream>
#include <stdexcept>
#include <limits>

bool inputNumber(int& value)
{
  return static_cast< bool >(std::cin >> value);
}

bool isSignChanged(int& prev, int& current)
{
  return (prev > 0) != (current > 0);
}

bool isSecondMaxDefined(unsigned long long n)
{
  return n >= 2;
}

void sub_max(int& value, int& prevMax, int& currentMax)
{
  if (value > currentMax) {
    prevMax = currentMax;
    currentMax = value;
  } else if (value > prevMax) {
    prevMax = value;
  }
}

void sgn_chg(int& prev, int& current, unsigned long long& count)
{
  if (isSignChanged(prev, current)) {
    ++count;
  }
}

int main()
{
  int prev = 0, current = 0;
  const int minInt = std::numeric_limits< int >::min();
  int prevMax = minInt, currentMax = minInt;
  unsigned long long count = 0;
  unsigned long long n = 0;
  while (true) {
    prev = current;
    if (!inputNumber(current)) {
      std::cerr << "Error: input is not a valid sequence\n";
      return 1;
    }
    if (current == 0) {
      int exitcode = 0;
      if (isSecondMaxDefined(n)) {
        std::cout << prevMax << '\n';
      } else {
        std::cerr << "Error: cannot calculate second maximum\n";
        exitcode = 2;
      }
      std::cout << count << '\n';
      return exitcode;
    }
    sub_max(current, prevMax, currentMax);
    if (n > 0) {
      sgn_chg(prev, current, count);
    }
    ++n;
  }
}


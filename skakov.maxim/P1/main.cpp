#include <iostream>
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

void subMax(int& value, int& prev_max, int& current_max)
{
  if (value > current_max) {
    prev_max = current_max;
    current_max = value;
  } else if (value > prev_max) {
    prev_max = value;
  }
}

void sgnChg(int& prev, int& current, unsigned long long& count)
{
  if (isSignChanged(prev, current)) {
    ++count;
  }
}

int main()
{
  int prev = 0, current = 0;
  const int min_int = std::numeric_limits< int >::min();
  int prev_max = min_int, current_max = min_int;
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
        std::cout << prev_max << '\n';
      } else {
        std::cerr << "Error: cannot calculate second maximum\n";
        exitcode = 2;
      }
      std::cout << count << '\n';
      return exitcode;
    }
    subMax(current, prev_max, current_max);
    if (n > 0) {
      sgnChg(prev, current, count);
    }
    ++n;
  }
}


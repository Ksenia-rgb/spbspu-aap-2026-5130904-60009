#include <iostream>
#include <limits>

int main()
{
  long long x;
  long long maxValue;
  unsigned long long after = 0;
  bool hasElements = false;
  bool terminated = false;
  bool overflow = false;

  const unsigned long long kMaxCount = std::numeric_limits<unsigned long long>::max();

  while (std::cin >> x)
  {
    if (x == 0)
    {
      terminated = true;
      break;
    }
    if (!hasElements || x > maxValue)
    {
      maxValue = x;
      after = 0;
      hasElements = true;
    }
    else
    {
      if (after == kMaxCount)
      {
        overflow = true;
      }
      else
      {
        ++after;
      }
    }
  }

  if (!terminated)
  {
    std::cerr << "Error: input is not a valid sequence\n";
    return 1;
  }

  if (!hasElements || overflow)
  {
    std::cerr << "Error: cannot calculate AFT-MAX\n";
    return 2;
  }

  std::cout << after << '\n';
  return 0;
}

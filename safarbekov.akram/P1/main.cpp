#include <iostream>
#include <limits>

int main()
{
  long long x = 0;
  long long max_value = 0;
  unsigned long long after = 0;
  bool has_elements = false;
  bool terminated = false;
  bool overflow = false;

  const unsigned long long k_max_count = std::numeric_limits< unsigned long long >::max();

  while (std::cin >> x)
  {
    if (x == 0)
    {
      terminated = true;
      break;
    }
    if (!has_elements || x > max_value)
    {
      max_value = x;
      after = 0;
      has_elements = true;
    }
    else
    {
      if (after == k_max_count)
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

  if (!has_elements || overflow)
  {
    std::cerr << "Error: cannot calculate AFT-MAX\n";
    return 2;
  }

  std::cout << after << '\n';
  return 0;
}

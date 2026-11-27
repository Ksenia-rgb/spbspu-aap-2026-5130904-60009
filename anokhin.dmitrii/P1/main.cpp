#include <cstddef>
#include <iostream>
#include <limits>

int main()
{
  const int inputError = 1;
  const int calcError = 2;
  const std::size_t maxSize = std::numeric_limits< std::size_t >::max();

  int a = 0;
  int max_val = 0;
  std::size_t count_max = 0;
  int prev = 0;
  std::size_t len = 0;
  std::size_t max_len = 0;

  bool count_max_overflow = false;
  bool max_len_overflow = false;

  while (std::cin >> a && a != 0)
  {
    if (len == 0)
    {
      max_val = a;
      count_max = 1;
      prev = a;
      len = 1;
      max_len = 1;
    }
    else
    {
      if (a > max_val)
      {
        max_val = a;
        count_max = 1;
      }
      else if (a == max_val)
      {
        if (count_max == maxSize)
        {
          count_max_overflow = true;
        }
        else
        {
          ++count_max;
        }
      }

      if (a == prev)
      {
        if (len == maxSize)
        {
          max_len_overflow = true;
        }
        else
        {
          ++len;
        }
      }
      else
      {
        len = 1;
      }

      if (len > max_len)
      {
        max_len = len;
      }

      prev = a;
    }
  }

  if (std::cin.fail() && !std::cin.eof())
  {
    std::cerr << "Input error\n";
    return inputError;
  }

  if (len == 0)
  {
    std::cerr << "Cannot calculate CNT-MAX\n";
    std::cout << max_len << '\n';
    return calcError;
  }

  if (count_max_overflow)
  {
    std::cerr << "Counter overflow\n";
    return calcError;
  }
  else
  {
    std::cout << count_max << '\n';
  }

  if (max_len_overflow)
  {
    std::cerr << "Max length overflow\n";
    return calcError;
  }
  else
  {
    std::cout << max_len << '\n';
  }

  return 0;
}

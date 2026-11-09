#include <iostream>
#include <stdexcept>

bool isPythagorian(int a, int b, int c)
{
  if (a <= 0 || b <= 0 || c <= 0)
  {
    return 0;
  }
  const int lhs = a * a + b * b;
  const int rhs = c * c;
  return lhs == rhs;
}
int main()
{
  try
  {
    int triples = 0;
    int range = 0;
    int b_num = 0;
    int num = 0;
    int bb_num = 0;
    while (std::cin >> num)
    {
      if (num == 0)
      {
        break;
      }
      if ((num > 0 && b_num < 0) || (num < 0 && b_num > 0))
      {
        range = range + 1;
      }
      if (isPythagorian(bb_num, b_num, num))
      {
        triples++;
      }
      bb_num = b_num;
      b_num = num;
    }
    if (std::cin.bad() || (std::cin.fail() && !std::cin.eof()))
    {
      throw std::invalid_argument("invalid input");
    }
    std::cout << range << " " << triples << std::endl;
    return 0;
  }
  catch (const std::invalid_argument &)
  {
    return 1;
  }
  catch (...)
  {
    return 1;
  }
}


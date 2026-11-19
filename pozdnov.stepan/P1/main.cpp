#include <cstddef>
#include <iostream>

namespace pozdnov
{
bool isPythagoreanTriple(int a, int b, int c)
{
  if (a <= 0 || b <= 0 || c <= 0)
  {
    return false;
  }
  unsigned long long x = a;
  unsigned long long y = b;
  unsigned long long z = c;
  return x * x + y * y == z * z;
}

bool isSignChange(int prev, int cur)
{
  return (prev < 0) != (cur < 0);
}
}

int main()
{
  int first = 0;
  int second = 0;
  int current = 0;
  std::size_t count = 0;
  unsigned long long triples = 0;
  unsigned long long changes = 0;

  while (std::cin >> current && current != 0)
  {
    if (count >= 2 && pozdnov::isPythagoreanTriple(first, second, current))
    {
      ++triples;
    }
    if (count >= 1 && pozdnov::isSignChange(second, current))
    {
      ++changes;
    }
    first = second;
    second = current;
    ++count;
  }

  if (!std::cin)
  {
    std::cerr << "Error: input is not a sequence of integers ending with 0\n";
    return 1;
  }

  std::cout << triples << '\n';
  std::cout << changes << '\n';
  return 0;
}

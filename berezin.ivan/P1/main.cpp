#include <cstddef>
#include <iostream>

namespace berezin
{

int GRT_LSS_DIV_REM()
{
  int first = 0;
  if (!(std::cin >> first))
  {
    std::cerr << "Error: invalid input\n";
    return 1;
  }
  if (first == 0)
  {
    std::cout << "0\n";
    std::cerr << "Error: not enough input values for DIV-REM\n";
    return 2;
  }

  int second = 0;
  if (!(std::cin >> second))
  {
    std::cerr << "Error: invalid input\n";
    return 1;
  }
  if (second == 0)
  {
    std::cout << "0\n";
    std::cerr << "Error: not enough input values for DIV-REM\n";
    return 2;
  }

  std::size_t grt_lss_count = 0;
  std::size_t div_rem_count = (second % first) == 0;

  int prev = first;
  int curr = second;
  int next = 0;

  while (std::cin >> next)
  {
    if (next == 0)
    {
      break;
    }
    grt_lss_count += (curr < prev) && (curr > next);
    div_rem_count += (next % curr) == 0;
    prev = curr;
    curr = next;
  }

  if (!std::cin)
  {
    std::cerr << "Error: invalid input\n";
    return 1;
  }

  char extra = 0;
  if (std::cin >> extra)
  {
    std::cerr << "Error: extra data after \"0\"\n";
    return 1;
  }

  std::cout << grt_lss_count << '\n';
  std::cout << div_rem_count << '\n';

  return 0;
}

} // namespace berezin

int main()
{
  return berezin::GRT_LSS_DIV_REM();
}

#include <iostream>

constexpr int success = 0;
constexpr int invalid_input_error = 1;
constexpr int inposible_calculations_error = 2;

namespace berezin
{

  int grtLssDivRem()
  {
    int first = 0;
    if (!(std::cin >> first))
    {
      std::cerr << "Error: invalid input\n";
      return invalid_input_error;
    }
    if (first == 0)
    {
      std::cout << "0\n";
      std::cerr << "Error: not enough input values for DIV-REM\n";
      return inposible_calculations_error;
    }

    int second = 0;
    if (!(std::cin >> second))
    {
      std::cerr << "Error: invalid input\n";
      return invalid_input_error;
    }
    if (second == 0)
    {
      std::cout << "0\n";
      std::cerr << "Error: not enough input values for DIV-REM\n";
      return inposible_calculations_error;
    }

    unsigned int grt_lss_count = 0;
    unsigned int div_rem_count = (second % first) == 0;

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
      return invalid_input_error;
    }

    int extra = 0;
    if (std::cin >> extra)
    {
      std::cerr << "Error: extra data after \"0\"\n";
      return invalid_input_error;
    }

    std::cout << grt_lss_count << '\n';
    std::cout << div_rem_count << '\n';

    return success;
  }

}

int main()
{
  return berezin::grtLssDivRem();
}

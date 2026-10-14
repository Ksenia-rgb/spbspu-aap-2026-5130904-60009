#include <iostream>

int main()
{
  int input = 0;
  int prev_input = 0;
  int sequence_len = 0;

  int div_rem_count = 0;
  int sgn_chg_count = 0;

  while (true)
  {
    if (!(std::cin >> input))
    {
      std::cerr << "Error: invalid input\n";
      return 1;
    }

    if (input == 0)
    {
      break;
    }

    sequence_len++;

    if (sequence_len > 1)
    {
      if (input % prev_input == 0)
      {
        div_rem_count++;
      }

      if ((prev_input < 0) != (input < 0))
      {
        sgn_chg_count++;
      }
    }

    prev_input = input;
  }

  if (sequence_len < 2)
  {
    std::cerr << "Error: cannot calculate chiferki; "
              << "sequence_length < 2\n";
    return 2;
  }

  std::cout << "div_rem_count: " << div_rem_count << '\n';
  std::cout << "sgn_chg_count: " << sgn_chg_count << '\n';

  return 0;
}

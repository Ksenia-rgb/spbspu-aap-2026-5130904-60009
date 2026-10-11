#include <iostream>

int laba()
{
  int last = 0, cur = 0, next = 0;
  int INC_SEQ = 0;
  int GRT_LSS = 0;

  while (true)
  {
    if (!(std::cin >> next))
    {
      return 1;
    }

    if (next == 0)
    {
      break;
    }

    if (cur != 0)
    {
      if (last != 0 && cur < last && cur > next)
      {
        GRT_LSS += 1;
      }
    }

    last = cur;
    cur = next;

    if (last != 0 && cur > last)
    {
      INC_SEQ += 1;
    }
  }

  std::cout << INC_SEQ << std::endl;
  std::cout << GRT_LSS << std::endl;
  return 0;
}

int main()
{
  laba();
}

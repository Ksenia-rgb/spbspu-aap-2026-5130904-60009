#include <iostream>

namespace shulzhenko
{
  int laba()
  {
    int last = 0, cur = 0, next = 0;
    int inq_seq = 0;
    int grt_lss = 0;

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
          grt_lss += 1;
        }
      }

      last = cur;
      cur = next;

      if (last != 0 && cur > last)
      {
        inq_seq += 1;
      }
    }

    std::cout << inq_seq << std::endl;
    std::cout << grt_lss << std::endl;
    return 0;
  }

}

int main()
{
  return shulzhenko::laba();
}

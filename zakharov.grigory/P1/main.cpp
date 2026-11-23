#include <iostream>

namespace zakharov {
  struct SeqStats
  {
    size_t count = 0;       
    size_t maxIncLen = 0;   
    size_t locMax = 0;      
  };

  bool readAndProcess(std::istream & in, SeqStats & s)
  {
    int prevPrev = 0, prev = 0, cur = 0;
    size_t curInc = 0;
    while (true)
    {
      if (!(in >> cur))
      {
        return false;
      }
      if (cur == 0)
      {
        return true;
      }
      ++s.count;

      // MON-INC
      if (s.count > 1 && cur >= prev)
      {
        ++curInc;
      }
      else
      {
        curInc = 1;
      }
      if (curInc > s.maxIncLen)
      {
        s.maxIncLen = curInc;
      }
      if (s.count > 2 && prev > prevPrev && prev > cur)
      {
        ++s.locMax;
      }

      prevPrev = prev;
      prev = cur;
    }
  }
}

int main()
{
  zakharov::SeqStats s;
  if (!zakharov::readAndProcess(std::cin, s))
  {
    std::cerr << "Error: input is not a sequence of integers\n";
    return 1;
  }

  int code = 0;

  std::cout << s.maxIncLen << '\n';

  if (s.count == 0)
  {
    std::cerr << "Error: LOC-MAX cannot be calculated for an empty sequence\n";
    code = 2;
  }
  else
  {
    std::cout << s.locMax << '\n';
  }

  return code;
}

#include <iostream>
#include <stdexcept>
#include <cstddef>

#define size 1000

namespace stamboliyski
{
  void enterNums(int p[size])
  {
    int num = 0;
    std::size_t count = 0;

    if (!(std::cin >> num))
    {
      throw std::invalid_argument("Invalid argument");
    }

    while (num != 0 && count < size)
    {
      p[count] = num;
      count++;
      if (!(std::cin >> num))
      {
        throw std::invalid_argument("ERROR");
      }
    }
  }

  int zOne(const int p[size])
  {
    if (p[0] == 0)
    {
      return 0;
    }

    int count = 0;
    int countnums = 0;
    int highnum = 0;
    int temp = p[0];

    while (p[count] != 0)
    {
      if (p[count] >= temp)
      {
        countnums++;
      }
      else
      {
        countnums = 1;
      }

      temp = p[count];
      count++;

      if (countnums > highnum)
      {
        highnum = countnums;
      }
    }
    return highnum;
  }

  int zTwo(const int p[size])
  {
    if (p[0] == 0)
    {
      return 0;
    }

    int count = 0;
    int smallestnum = p[0];
    int smallestnumcounter = 0;

    while (p[count] != 0)
    {
      if (p[count] < smallestnum)
      {
        smallestnum = p[count];
      }

      count++;
    }

    count = 0;

    while (p[count] != 0)
    {
      if (p[count] == smallestnum)
      {
        smallestnumcounter++;
      }

      count++;
    }

    return smallestnumcounter;
  }
}

int main()
{
  int nums[size] = {0};

  try
  {
    stamboliyski::enterNums(nums);
  }
  catch (const std::invalid_argument &)
  {
    std::cerr << "Program terminated with error code: 1\n";
    return 1;
  }
  std::cout << stamboliyski::zOne(nums) << "\n";
  std::cout << stamboliyski::zTwo(nums) << "\n";
  return 0;
}

#include <iostream>

namespace aristov
{
    int run()
    {
        int x;
        if (!(std::cin >> x))
        {
            std::cerr << "Invalid input\n";
            return 1;
        }

        int max = 0;
        int second = 0;
        int prev = 0;
        int signChanges = 0;
        bool hasValue = false;
        bool hasSecond = false;

        while (x != 0)
        {
            if (!hasValue)
            {
                max = x;
                prev = x;
                hasValue = true;
            }
            else
            {
                if ((prev > 0 && x < 0) || (prev < 0 && x > 0))
                {
                    ++signChanges;
                }

                if (x > max)
                {
                    second = max;
                    max = x;
                    hasSecond = true;
                }
                else if (!hasSecond || x > second)
                {
                    second = x;
                    hasSecond = true;
                }

                prev = x;
            }

            if (!(std::cin >> x))
            {
                std::cerr << "Invalid input\n";
                return 1;
            }
        }

        if (!hasSecond)
        {
            std::cerr << "Cannot calculate SUB-MAX\n";
        }
        else
        {
            std::cout << second << '\n';
        }

        std::cout << signChanges << '\n';

        if (!hasSecond)
        {
            return 2;
        }
        return 0;
    }
}

int main()
{
    return aristov::run();
}
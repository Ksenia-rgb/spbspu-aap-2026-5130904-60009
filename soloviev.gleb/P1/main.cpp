#include <iostream>
#include <limits>

void Variant12(int a, int b[3], int* c)
{
	if (a > b[0])
	{
		b[0] = a;
		(*c) = 0;
	}
	else
	{
		(*c)++;
	}
}
void Variant2(int a, int b[3], int* c)
{
	if (a > b[2])
	{
		b[1] = b[2];
		b[2] = a;
	}
	if (a<b[2] && a>b[1])
	{
		b[1] = a;
	}
	(*c) = b[1];
}
int main()
{
	void (*fn[2]) (int,int*,int*) = {Variant12,Variant2};
	const char* varnames[2] = {"Variant 12","Variant 2"};
	int rs[2] = { 0 };
	int cyclst[3] = {std::numeric_limits<int>::min()};
	for (int i = 0; i < 2; i++)
	{
		std::cout << varnames[i]<<std::endl;
		while (true)
		{
			int a = 0;
			std::cin >> a;
			if (std::cin.fail() || std::cin.eof())
			{
				std::cerr << "input error";
				return 1;
			}
			if (a == 0)
			{
				break;
			}

			fn[i](a, cyclst, rs+i);
		}
		std::cout << rs[i] << std::endl;
		
	}
}

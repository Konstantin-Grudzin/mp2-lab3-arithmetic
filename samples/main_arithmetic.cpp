#include "arithmetic.h"

int main()
{
	std::string s;
	std::pair<double, int> x;
	do
	{
		std::cin >> s;
		Arifm a(s);
		 x= a.Execution();
	} while (x.second == -1);
	std::cout << x.first;
}

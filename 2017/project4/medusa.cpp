#include"medusa.hpp"
#include<cstdlib>
#include<iostream>
int Medusa::attack()
{
	int total = 0;
	total += rand() % 6 + 1;
	total += rand() % 6 + 1;
	if (total == 12)
	{
		std::cout << "Medusa used glare and turned the other player into stone.\n";
		total = 100;
		return total;
	}
	else
	{
		return total;
	}
	
}
int Medusa::defense()
	{
		int total = 0;
		total = rand() % 6 + 1;
		return total;
	}

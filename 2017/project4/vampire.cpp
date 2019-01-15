#include"vampire.hpp"
#include<cstdlib>
#include <iostream>
int Vampire::attack()
{
	int total = 0;
	total += rand() % 12 + 1;
	return total;
}
int Vampire::charm()
{
	int c;
	c = rand() % 2 + 1;
	return c;
}
int Vampire::defense()
{
	int total = 0;
	if (charm() == 1)
	{
		total = 101;
		std::cout << "Charm was used. Attack dodged\n";
		return total;
	}
	else
	{
		total += rand() % 6 + 1;
		return total;
	}
	
}

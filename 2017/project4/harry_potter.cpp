#include"harry_potter.hpp"
#include<cstdlib>
#include<iostream>
int Harry_Potter::attack()
{
	int total = 0;
	total += rand() % 6 + 1;
	total += rand() % 6 + 1;
	return total;
}
void Harry_Potter::special()
{
	if (strengthPoint <= 0 && secondLife == 0)
	{
		strengthPoint = 20;
		std::cout << "Harry used Hogwarts and revived.\n";
		secondLife++;
	}
}
int Harry_Potter::defense()
{
	int total = 0;
	total += rand() % 6 + 1;
	total += rand() % 6 + 1;
	return total;
}

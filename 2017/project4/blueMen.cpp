#include"blueMen.hpp"
#include<cstdlib>
#include<iostream>
int blueMen::attack()
{
	int total = 0;
	total += rand() % 10 + 1;
	total += rand() % 10 + 1;
	return total;
}
int blueMen::defense()
{
	int d=0;
	if (strengthPoint > 8)
	{
		d += rand() % 6 + 1;
		d += rand() % 6 + 1;
		d += rand() % 6 + 1;
	}
	else if (strengthPoint > 4 && strengthPoint <= 8)
	{
		d += rand() % 6 + 1;
		d += rand() % 6 + 1;
	}
	else if (strengthPoint <= 4)
	{
		d += rand() % 6 + 1;
	}
	return d;
}


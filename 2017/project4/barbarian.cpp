#include"barbarian.hpp"
#include<cstdlib>
#include<iostream>
int Barbarian::attack()
{
	int total=0;
	total += rand() % 6 + 1;
	total += rand() % 6 + 1;
	return total;
}
int Barbarian::defense()
{
	int total=0;
	total += rand() % 6 + 1;
	total += rand() % 6 + 1;
	return total;
}

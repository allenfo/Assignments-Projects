#include"monster.hpp"
#include<iostream>
#include<cstdlib>

int Monster::fight()
{
	int d = std::rand() % attack + 1;
	return d;
}
int Monster::search()
{
	if (defeat == 0)
	{
		std::cout << "The area was searched and a monster was found. It spots you and you start to fight\n";
		int damage = rand()&attack + 1;
		defeat++;
		return damage;
	}
	else
	{
		std::cout << "The area was searched and you found a dead monster\n";
		return 21;
	}
	
}

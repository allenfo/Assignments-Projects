#include"item.hpp"
#ifndef HEALTHPO_HPP
#define HEALTHPO_HPP

class Healthpo :public Item
{
public:
	int count;
	int health;
	Healthpo()
	{
		count = 0;
		health = 50;
	}
	bool isEmpty();
	int get();
	int search();
};

#endif

#include"space.hpp"
#ifndef MONSTER_HPP
#define MONSTER_HPP

class Monster :public Space
{
public:
	int attack;
	int defeat;
	Monster()
	{
		defeat = 0;
		attack = 0;
	}
	int get()
	{
		return 0;
	}
	int fight();
	int search();
};

#endif

#include"monster.hpp"
#ifndef BOSS_HPP
#define BOSS_HPP

class Boss :public Monster
{
public:
	int health;
	Boss()
	{
		attack = 30;
		health = 30;
	}
	int search();
};

#endif

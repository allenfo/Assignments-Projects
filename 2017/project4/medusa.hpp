#include"character.hpp"
#ifndef MEDUSA_HPP
#define MEDUSA_HPP

class Medusa :public Character
{
public:
	Medusa()
	{
		armor = 3;
		strengthPoint = 8;
		type = "Medusa";
	}
	int attack();
	int defense();
	void special()
	{
		return;
	}
};

#endif

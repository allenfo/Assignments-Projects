#include"character.hpp"
#ifndef BLUEMEN_HPP
#define BLUEMEN_HPP

class blueMen :public Character
{
public:
	blueMen()
	{
		armor = 3;
		strengthPoint = 12;
		type = "Blue Men";
	}
	int attack();
	int defense();
	void special()
	{
		return;
	}

};

#endif


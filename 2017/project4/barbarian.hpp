#include"character.hpp"
#ifndef BARBARIAN_HPP
#define BARBARIAN_HPP
class Barbarian :public Character
{
public:
	Barbarian()
	{
		armor = 0;
		strengthPoint = 12;
		type = "Barbarian";
	}
	int attack();
	int defense();
	void special()
	{
		return;
	}

};
#endif


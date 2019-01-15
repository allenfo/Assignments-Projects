#include"character.hpp"
#ifndef VAMPIRE_HPP
#define VAMPIRE_HPP
class Vampire :public Character
{
public:
	Vampire()
	{
		armor = 1;
		strengthPoint = 18;
		type = "Vampire";
	}
	int attack();
	int defense();
	int charm();
	void special()
	{
		return;
	}
};
#endif 

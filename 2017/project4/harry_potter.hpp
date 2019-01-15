#include"character.hpp"
#include<iostream>
#ifndef HARRYPOTTER_HPP
#define HARRYPOTTER_HPP

class Harry_Potter :public Character
{
private:
	int secondLife;
public:
	Harry_Potter()
	{
		armor = 0;
		strengthPoint = 10;
		type = "Harry Potter";
		secondLife = 0;
	}
	int attack();
	int defense();
	void special();
};

#endif

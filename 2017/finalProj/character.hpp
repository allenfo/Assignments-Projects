#include"monster.hpp"
#include<stack>
#include"item.hpp"
#ifndef CHARACTER_HPP
#define CHARACTER_HPP

class Character :public Monster
{
public:
	std::stack<int> bag;
	int keys;
	int limit;
	int health;
	Character()
	{
		attack = 20;
		health = 50;
	}
	int getHealth();
	void add(int);
	void key();
	int getKey();
	void use();
};

#endif

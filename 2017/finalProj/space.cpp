#include"space.hpp"
#include"character.hpp"
#include<iostream>
Space::~Space()
{
	delete top;
	delete bottom;
	delete left;
	delete right;
	delete val;
}
void Space::print()
{
	if (val == NULL)
	{
		std::cout << "[ ]";
	}
	else
	{
		std::cout << "[o]";
	}
	
}
void Space::setPlayer(Space *v)
{
	val = v;
}
void Space::remove()
{
	val = NULL;
}

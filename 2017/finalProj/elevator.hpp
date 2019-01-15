#include"space.hpp"
#ifndef ELEVATOR_HPP
#define ELEVATOR_HPP

class Elevator:public Space
{
public:
	Elevator *ladder;
	Elevator()
	{
		top = NULL;
		bottom = NULL;
		left = NULL;
		right = NULL;
		ladder = NULL;
		val = NULL;
	}
	int get()
	{
		return 0;
	}
	int search();
	int fight()
	{
		return 0;
	}
};

#endif


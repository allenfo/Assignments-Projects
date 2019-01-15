#include"item.hpp"
#ifndef ATTACKUP_HPP
#define ATTACKUP_HPP

class Attackup :public Item
{
public:
	int count;
	int boost;
	Attackup()
	{
		count = 0;
		boost = 30;
	}
	bool isEmpty();
	int get();
	int search();
};

#endif

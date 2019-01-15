#include"space.hpp"
#ifndef ITEM_HPP
#define ITEM_HPP

class Item :public Space
{
public:
	Item()
	{
		top = NULL;
		bottom = NULL;
		right = NULL;
		left = NULL;
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

#include"space.hpp"
#include"item.hpp"
#include<queue>
#ifndef MAP_HPP
#define MAP_HPP

class Map:public Space
{
public:
	Space *s;
	Space *l2;
	Space *l3;
	Map();
	~Map();
	void printMap();
	int get()
	{
		return 0;
	}
	bool open()
	{
		return false;
	}
	int fight()
	{
		return 0;
	}
	int search()
	{
		return 0;
	}
};


#endif

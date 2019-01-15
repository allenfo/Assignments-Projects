/*Base class for the game*/
#include<iostream>
#ifndef SPACE_HPP
#define SPACE_HPP
class Space
{
public:
	Space *top;
	Space *bottom;
	Space *left;
	Space *right;
	Space *ladder;
	Space *val;
	Space()
	{
		top = NULL;
		bottom = NULL;
		left = NULL;
		right = NULL;
		val = NULL;
	}
	~Space();
	virtual int get() = 0;
	virtual int search() = 0;
	virtual int fight() = 0;
	void setPlayer(Space*);
	void remove();
	void print();
};

#endif

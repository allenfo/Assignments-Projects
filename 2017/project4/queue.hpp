#include"character.hpp"
#include<iostream>
#ifndef QUEUE_HPP
#define QUEUE_HPP
class Queue
{
protected:
	struct playerList
	{
		Character *c;
		playerList *prev;
		playerList *next;
		playerList(Character *player, playerList *nex1=NULL, playerList *prev1=NULL)
		{
			c = player;
			next = nex1;
			prev = prev1;
		}
	};
	playerList *head; //pointer to head
	playerList *tail;//pointer to tail
public:
	void addPlayer(Character*);
	void trashPlayer(Character *);
	Queue();
	~Queue();
	void removePlayer();
	void move2Back();
	bool isEmpty();
	Character* getTop();
	void print();
};
#endif 

#include"map.hpp"
#include"item.hpp"
#include"healthpo.hpp"
#include"monster.hpp"
#include"l1monster.hpp"
#include"l2monster.hpp"
#include"attackup.hpp"
#include"boss.hpp"
#include "elevator.hpp"
#include<iostream>
Map::Map()
{
	/*First floor*/
	Space *temp;
	s = new Elevator;
	s->top=new Healthpo;
	temp = s->top;
	temp->bottom = s;
	s->bottom = new l1Monster;
	temp = s->bottom;
	temp->top = s;
	s->left = new Attackup;
	temp = s->left;
	temp->right = s;
	s->right = new l1Monster;
	temp = s->right;
	temp->left = s;
	/*Second floor*/
	l2 = new Elevator;
	s->ladder = l2;
	l2->ladder = s;
	l2->top = new l2Monster;
	temp = l2->top;
	temp->bottom = l2;
	l2->bottom = new l2Monster;
	temp = l2->bottom;
	temp->top = l2;
	l2->left = new Healthpo;
	temp = l2->left;
	temp->right = l2;
	l2->right = new Elevator;
	temp = l2->right;
	temp->left = l2;
	/* Third floor*/
	l3 = new Elevator;
	l2->right->ladder = l3;
	l3->ladder = l2->right;
	l3->right = new Boss;
}
Map::~Map()
{
Space *guide =s;
	delete guide->top;
	delete guide->bottom;
	delete guide->left;
	delete guide->right;
	delete guide->ladder;
	guide = l2;
	delete guide->top;
	delete guide->bottom;
	delete guide->left;
	delete guide->right;
	delete guide->ladder;
	guide = l3;
	delete guide->right;
	delete guide->ladder;
	delete guide;
	delete s;
	delete l2;

}
void Map::printMap()
{
	std::cout << "MAP\n";
	/*third floor*/
	std::cout << "Floor three\n";
	l3->print();
	std::cout << "--";
	l3->right->print();
	std::cout << std::endl;
	/*second floor*/
	std::cout << "Floor two\n";
	std::cout << "     ";
	l2->top->print();
	std::cout << std::endl;
	std::cout << "      |\n";
	l2->left->print();
	std::cout << "--";
	l2->print();
	std::cout << "--";
	l2->right->print();
	std::cout << std::endl;
	std::cout << "      |\n";
	std::cout << "     ";
	l2->bottom->print();
	std::cout << std::endl;
	/*first floor*/
	std::cout << "Floor one\n";
	std::cout << "     ";
	s->top->print();
	std::cout << std::endl;
	std::cout << "      |\n";
	s->left->print();
	std::cout << "--";
	s->print();
	std::cout << "--";
	s->right->print();
	std::cout << std::endl;
	std::cout << "      |\n";
	std::cout << "     ";
	s->bottom->print();
	std::cout << std::endl;
}

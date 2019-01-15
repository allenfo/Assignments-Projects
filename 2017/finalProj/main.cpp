#include"space.hpp"
#include"item.hpp"
#include"map.hpp"
#include"play.hpp"
#include"character.hpp"
#include<iostream>

int main()
{
	std::cout << "Welcome to tower climb. Your goal is to reach the top and fight the boss.\n";
	std::cout << "Along the way you must collect keys to advance to the next floor. There are\n";
	std::cout << "two health potions and one attack boost laying around as well. Be careful\n";
	std::cout << "as soon as your health runs out or you reach the 25 step limit you're dead. Your item bag can only hold one\n";
	std::cout << "health potion at a time.\n";
	std::cout << "Use the menu in the game to move around the map, search a room, check health, use items, or quit the game.\n";
	std::cout << "The 'o' on the map is you.\nGood luck!\n";
	Map *map = new Map;
	Character *me=new Character;
	map->s->setPlayer(me);
	play(map, me);
	//delete map;
	return 0;
}

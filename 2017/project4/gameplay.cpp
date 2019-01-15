#include"barbarian.hpp"
#include"vampire.hpp"
#include"queue.hpp"
#include"blueMen.hpp"
#include"medusa.hpp"
#include"character.hpp"
#include"harry_potter.hpp"
#include<iostream>

void gameplay(Character *player1, Character *player2)
{

	int round = 1;
	std::cout << "Player 1 info:\n";
	player1->info();
	std::cout << std::endl;
	std::cout << "Player 2 info:\n";
	player2->info();
	std::cout << std::endl;
	while (true)
	{
		std::cout << "Round: " << round << std::endl;
		std::cout << std::endl;
		std::cout << "Player 1 strength point: " << player1->strengthPoint << std::endl;
		std::cout << "Player 2 strength point: " << player2->strengthPoint << std::endl;
		int a1 = player1->attack();
		int d2 = player2->defense();
		std::cout << "Player one's "<<player1->getType()<<" named "<< player1->getName()<<" is attacking.\n";
		std::cout << "Player two's "<<player2->getType()<<" named "<<player2->getName()<<" is defending.\n";
		std::cout << "Player 1 attack dice roll: " << a1 << std::endl;
		std::cout << "Player 2 defense dice roll: " << d2 << std::endl;
		if (a1 > (d2 + player2->getArmor()))
		{
			int total=(a1 - (d2 + player2->getArmor()));
			std::cout << "Actual damage given: " << total << std::endl;
			player2->strengthPoint -=total;
			std::cout << "Player 2 new strength point: " << player2->strengthPoint << std::endl;
			std::cout << std::endl;
		}
		else
		{
			int total = 0;
			std::cout << "Actual damage given: " << total << std::endl;
			std::cout << "Player 2 strength point: " << player2->strengthPoint << std::endl;
			std::cout << std::endl;
		}
		player2->special();
		if (player2->strengthPoint <= 0)
		{
			std::cout << "Player two's "<<player2->getType()<<" has died. Player one's "<<player1->getType()<<" wins the fight.\n";
			return;
		}
		int a2 = player2->attack();
		int d1 = player1->defense();
		std::cout << "Player 1 strength point: " << player1->strengthPoint << std::endl;
		std::cout << "Player 2 strength point: " << player2->strengthPoint << std::endl;
		std::cout << "Player twos's " << player1->getType() << " named " << player2->getName() << " is attacking.\n";
		std::cout << "Player one's " << player2->getType() << " named " << player1->getName() << " is defending.\n";
		std::cout << "Player 1 defense dice roll: " << d1 << std::endl;
		std::cout << "Player 2 attack dice roll: " << a2 << std::endl;
		if (a2 > (d1 + player1->getArmor()))
		{
			int total = (a2 - (d1 + player1->getArmor()));
			std::cout << "Actual damage given: " << total << std::endl;
			player1->strengthPoint -= total;
			std::cout << "Player 1 new strength point: " << player1->strengthPoint << std::endl;
			std::cout << std::endl;
		}
		else
		{
			int total = 0;
			std::cout << "Actual damage given: " << total << std::endl;
			std::cout << "Player 1 strength point: " << player1->strengthPoint << std::endl;
			std::cout << std::endl;
		}
		player1->special();
		if (player1->strengthPoint <= 0)
		{
			std::cout << "Player one's "<<player1->getType()<<" has died. Player two's "<<player2->getType()<<" wins the fight.\n";
			return;
		}
		round++;
	}
}

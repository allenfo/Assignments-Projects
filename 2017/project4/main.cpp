#include"character.hpp"
#include"vampire.hpp"
#include"barbarian.hpp"
#include"blueMen.hpp"
#include"harry_potter.hpp"
#include"medusa.hpp"
#include"fight.hpp"
#include"gameplay.hpp"
#include"queue.hpp"
#include<iostream>
int main()
{
	Vampire * v;
	Barbarian *b;
	blueMen * bm;
	Medusa * m;
	Harry_Potter * hp;
	while (true)
	{
		Queue play1;
		Queue play2;
		Queue deadList;
		int p1;
		int p2;
		int num;
		std::string name;
		std::cout << "Welcome to fantasy combat game.\n";
		std::cout << "How many players do you want per team? There can be up to 10.\n";
		std::cin >> num;
		while (std::cin.fail() || num >= 11)
		{
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Not an option.Try again.\n";
			std::cin >> num;
		}
		for (int i = 0; i < num; i++)
		{
			std::cout << "Player 1 choose your character:1.vampire, 2.barbarian, 3.blue men, 4.medusa, 5.harry potter\n";
			std::cin >> p1;
			while (std::cin.fail() || p1 >= 6)
			{
				std::cin.clear();
				std::cin.ignore();
				std::cout << "Not a character option. Try again.\n";
				std::cin >> p1;
			}
			switch (p1)
			{
			case 1:
				v = new Vampire;
				std::cout << "Enter their name: ";
				std::cin >> name;
				v->setName(name);
				v->setTeam(1);
				play1.addPlayer(v);
				break;
			case 2:
				b = new Barbarian;
				std::cout << "Enter their name: ";
				std::cin >> name;
				b->setName(name);
				b->setTeam(1);
				play1.addPlayer(b);
				break;
			case 3:
				bm = new blueMen;
				std::cout << "Enter their name: ";
				std::cin >> name;
				bm->setName(name);
				bm->setTeam(1);
				play1.addPlayer(bm);
				break;
			case 4:
				m = new Medusa;
				std::cout << "Enter their name: ";
				std::cin >> name;
				m->setName(name);
				m->setTeam(1);
				play1.addPlayer(m);
				break;
			case 5:
				hp = new Harry_Potter;
				std::cout << "Enter their name: ";
				std::cin >> name;
				hp->setName(name);
				hp->setTeam(1);
				play1.addPlayer(hp);
				break;
			}
		}
		for (int i = 0; i < num; i++)
		{
			std::cout << "Player 2 choose your character:1.vampire, 2.barbarian, 3.blue men, 4.medusa, 5.harry potter\n";
			std::cin >> p2;
			while (std::cin.fail() || p2 >= 6)
			{
				std::cin.clear();
				std::cin.ignore();
				std::cout << "Not a character option. Try again.\n";
				std::cin >> p2;
			}
			switch (p2)
			{
			case 1:
				v = new Vampire;
				std::cout << "Enter their name: ";
				std::cin >> name;
				v->setName(name);
				v->setTeam(2);
				play2.addPlayer(v);
				break;
			case 2:
				b = new Barbarian;
				std::cout << "Enter their name: ";
				std::cin >> name;
				b->setName(name);
				b->setTeam(2);
				play2.addPlayer(b);
				break;
			case 3:
				bm = new blueMen;
				std::cout << "Enter their name: ";
				std::cin >> name;
				bm->setName(name);
				bm->setTeam(2);
				play2.addPlayer(bm);
				break;
			case 4:
				m = new Medusa;
				std::cout << "Enter their name: ";
				std::cin >> name;
				m->setName(name);
				m->setTeam(2);
				play2.addPlayer(m);
				break;
			case 5:
				hp = new Harry_Potter;
				std::cout << "Enter their name: ";
				std::cin >> name;
				hp->setName(name);
				hp->setTeam(2);
				play2.addPlayer(hp);
				break;
			}
		}
		fight(play1, play2, deadList);
		int dead;
		std::cout << "Do you want to print out the list of the fallen characters?1.yes 2.no:";
		std::cin >> dead;
		while (std::cin.fail() || dead >= 3)
		{
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Not an option. Try again.\n";
			std::cin >> dead;
		}
		if (dead == 1)
		{
			std::cout << "The fallen characters are:\n";
			deadList.print();
		}
		int play;
		std::cout << "1.Play again\n2.Exit\n";
		std::cin >> play;
		while (std::cin.fail() || play >= 3)
		{
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Not an option. Try again.\n";
			std::cin >> play;
		}
		if (play == 2)
		{
			std::cout << "Bye!\n";
			return 0;
		}
	}
}

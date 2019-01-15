#include"play.hpp"
#include"elevator.hpp"
#include"boss.hpp"
#include<iostream>
#include<cstdlib>
int menu()
{
	int ans;
	std::cout << "1.Move\n2.Search\n3.Print map\n4.Check health\n5.Use an item\n6.Check steps\n7.Quit\n";
	std::cin >> ans;
	while (std::cin.fail() || ans <= 0 ||ans >=8)
	{
		std::cin.clear();
		std::cin.ignore();
		std::cout << "Not an option, try again\n";
		std::cin >> ans;
	}
	switch (ans)
	{
	case 1:
		return 1;
		break;
	case 2:
		return 2;
		break;
	case 3:
		return 3;
		break;
	case 4:
		return 4;
		break;
	case 5:
		return 5;
		break;
	case 6:
		return 6;
		break;
	case 7:
		return 7;
		break;
	}
}
int bossBattle(Boss * b, Character *c)
{
	int ans;
	int a;
	std::cout << "This is the final battle. It will be a turn based fight\n";
	while (true)
	{
		std::cout << "1.Attack\n2.Use Item\n3.Check health\n";
		std::cin >> ans;
		while (std::cin.fail() || ans >= 4 || ans <= 0)
		{
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Not an option, try again\n";
			std::cin >> ans;
		}
		switch (ans)
		{
		case 1:
			a = rand() % c->attack + 1;
			std::cout << "You gave the boss " << a << " damage\n";
			b->health -= a;
			if (b->health <= 0)
			{
				return 1;
			}
			a = rand() % b->attack + 1;
			std::cout << "The boss gave you " << a << " damage\n";
			c->health -= a;
			if (c->health <= 0)
			{
				return 2;
			}
			break;
		case 2:
			c->use();
			std::cout << "The boss recovered 10 health\n";
			b->health += 10;
			break;
		case 3:
			std::cout << "Your health is " << c->health << "\n";
			std::cout << "The Boss health is " << b->health << "\n";
			break;
		}
	}

}
void play(Map *m, Character *c)
{
	int steps = 0;
	Boss b;
	int num;
	Space *guide = m->s;
	m->printMap();
	while (steps<=25)
	{
		switch (menu())
		{
		case 1:
			int ans;
			if (guide->ladder)
			{
				std::cout << "1.Up\n2.Down\n3.Left\n4.Right\n5.Use ladder\n";
			}
			else
			{
				std::cout << "1.Up\n2.Down\n3.Left\n4.Right\n";
			}
			std::cin >> ans;
			while (std::cin.fail() || ans > 5)
			{
				std::cin.clear();
				std::cin.ignore();
				std::cout << "Not an option, try again\n";
				std::cin >> ans;
			}
			switch (ans)
			{
			case 1:
				std::cout << std::endl;
				if (guide->top == NULL)
				{
					std::cout << "You can't go that way.\n";
				}

				else if (guide->top != NULL)
				{
					steps++;
					guide->remove();
					guide = guide->top;
					guide->setPlayer(c);
				}
				break;
			case 2:
				std::cout << std::endl;
				if (guide->bottom == NULL)
				{
					std::cout << "You can't go that way.\n";
				}

				else if (guide->bottom != NULL)
				{
					steps++;
					guide->remove();
					guide = guide->bottom;
					guide->setPlayer(c);
				}
				break;
			case 3:
				std::cout << std::endl;
				if (guide->left == NULL)
				{
					std::cout << "You can't go that way.\n";
				}

				else if (guide->left != NULL)
				{
					steps++;
					guide->remove();
					guide = guide->left;
					guide->setPlayer(c);
				}
				break;
			case 4:
				std::cout << std::endl;
				if (guide->right == NULL)
				{
					std::cout << "You can't go that way.\n";
				}
				else if (guide->right != NULL)
				{
					steps++;
					guide->remove();
					guide = guide->right;
					guide->setPlayer(c);
				}
				break;
			case 5:
				if (guide->ladder)
				{
					if (c->getKey() == 4)
					{
						steps++;
						guide->remove();
						guide = guide->ladder;
						guide->setPlayer(c);
					}
					else
					{
						if (guide == m->s && c->getKey() < 2)
						{
							std::cout << "You don't have enough keys to move up to floor 2\n";
						}
						else if (guide == m->s && c->getKey() >= 2)
						{
							steps++;
							guide->remove();
							guide = guide->ladder;
							guide->setPlayer(c);
						}
						else if (guide == m->l2)
						{
							steps++;
							guide->remove();
							guide = guide->ladder;
							guide->setPlayer(c);
						}
						if (guide == m->l2->right && c->getKey() <= 3)
						{
							std::cout << "You don't have enough keys to move up to the final floor\n";
						}
					}
				}
				else
				{
					std::cout << "That was not an option\n";
				}
			}
			break;
		case 2:
			num = guide->search();
			if (num <= 20)
			{
				c->health -= num;
				if (c->health <= 0)
				{
					std::cout << "You took too much damage and died. Game over\n";
					return;
				}
				else
				{
					std::cout << "You took some damage but managed to defeat the monster and collected a key.\n";
					std::cout << "Check how much health you have by selecting it on the menu screen\n";
					c->key();
				}
			}
			else if (num == 22)
			{
				int i = 0;
				std::cout << "Do you want to add it to your item bag?\n1.Yes\n2.No\n";
				std::cin >> i;
				while (std::cin.fail() || i >= 3 || i <= 0)
				{
					std::cin.clear();
					std::cin.ignore();
					std::cout << "Not an option, try again\n";
					std::cin >> i;
				}
				switch (i)
				{
				case 1:
					if (c->limit==0)
					{
						c->add(guide->get());
					}
					else
					{
						std::cout << "Item bag full. Use an item to empty it\n";
					}
					break;
				case 2:
					std::cout << "It will be there if you want it.\n";

					break;
				}
			}
			else if (num == 25)
			{
				int i = 0;
				std::cout << "Do you want to use it?\n1.Yes\n2.No\n";
				std::cin >> i;
				while (std::cin.fail() || i >= 3 || i <= 0)
				{
					std::cin.clear();
					std::cin.ignore();
					std::cout << "Not an option, try again\n";
					std::cin >> i;
				}
				switch (i)
				{
				case 1:
					c->attack += guide->get();
					std::cout << "Your attack is now " << c->attack << ".\n";
					break;
				case 2:
					std::cout << "It will be there if you want it\n";
					break;
				}
			}
			else if (num == 26)
			{
				if (bossBattle(&b, c) == 1)
				{
					std::cout << "You beat the boss! You win the game!\n";
					return;
				}
				else
				{
					std::cout << "You died in battle. Game over\n";
					return;
				}
			}
			break;
		case 3:
			m->printMap();
			break;
		case 4:
			std::cout << "Your health is " << c->getHealth() << ". Make sure it doesn't run out\n";
			break;
		case 5:
			c->use();
			break;
		case 6:
			std::cout << "You have used " << steps << "/25 steps\n";
			break;
		case 7:
			std::cout << "bye\n";
			return;
			break;
		}
	}
	std::cout << "You ran out of steps and died\nGame Over\n";
			
}

#include"character.hpp"

int Character::getHealth()
{
	return health;
}
void Character::add(int i)
{
	if (limit == 1)
	{
		std::cout << "You don't have room for another item. Make room\n";
	}
	else
	{
		bag.push(i);
		limit++;
	}
}
void Character::use()
{
	if(limit ==1)
	{
	int ans;
	std::cout << "Are you sure you want to use an item? Once used you can't get it back\n1.Yes\n2.No\n";
	std::cin >> ans;
	while (std::cin.fail() || ans <= 0 || ans >= 3)
	{
		std::cin.clear();
		std::cin.ignore();
		std::cout << "That was not an option, try again\n";
		std::cin >> ans;
	}
	switch (ans)
	{
	case 1:
		health +=(bag.top() - health);
		std::cout << "You have used your potion. Your health is now full\n";
		limit--;
		bag.pop();
		break;
	case 2:
		std::cout << "Smart move. Save it for later\n";
		break;
	}
	}
	else
	{
		std::cout<<"Your item bag is empty\n";
	}
}
void Character::key()
{
	keys++;
}
int Character::getKey()
{
	return keys;
}

#include"healthpo.hpp"

int Healthpo::search()
{
	if (isEmpty() == true)
	{
		std::cout << "You have done everything there is to do in this room\n";
		return 24;
	}
	else
	{
		std::cout << "You have discovered a health potion\n";
		return 22;
	}
}
bool Healthpo::isEmpty()
{
	if (count == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
int Healthpo::get()
{
	if (isEmpty() == false)
	{
		count++;
		return health;
	}
	else
	{
		return 23;
	}
}

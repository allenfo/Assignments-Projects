#include"attackup.hpp"

int Attackup::search()
{
	if (isEmpty() == true)
	{
		std::cout << "You have done everything there is to do in this room\n";
		return 24;
	}
	else
	{
		std::cout << "You have discovered an attack boost. It will increase your attack chances by 30.\n";
		return 25;
	}
}
bool Attackup::isEmpty()
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
int Attackup::get()
{
	if (isEmpty() == false)
	{
		count++;
		return boost;
	}
	else
	{
		return 23;
	}
}

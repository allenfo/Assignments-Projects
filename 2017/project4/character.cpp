#include"character.hpp"
#include<iostream>
int Character::getArmor()
{
	return armor;
}
void Character::info()
{	
	std::cout << "Name: " << name << std::endl;
	std::cout <<"Character type: " << type << std::endl;
	std::cout <<"Team number: " << team << std::endl;
}
std::string Character::getType()
{
	return type;
}
std::string Character::getName()
{
	return name;
}
void Character::setName(std::string n)
{
	name = n;
}
void Character::setTeam(int t)
{
	team = t;
}
int Character::getTeam()
{
	return team;
}

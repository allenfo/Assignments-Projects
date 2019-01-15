#include<string>
#include<iostream>
#ifndef CHARACTER_HPP
#define CHARACTER_HPP
class Character
{
protected:
	int armor;
	std::string type;
	std::string name;
	int team;
public:
	int strengthPoint;
	Character()
	{
		armor = 0;
		strengthPoint = 0;
		type = "Character";
		team = 0;
	}
	Character(const Character &c)
	{
		std::cout<<"This is the copy\n";
		armor = 0;
		strengthPoint = 0;
		type = "Character";
	}
	int getArmor();
	std::string getType();
	std::string getName();
	void setTeam(int);
	int getTeam();
	void setName(std::string);
	virtual int attack() = 0;
	virtual int defense() = 0;
	virtual void special() = 0;
	void info();
};
#endif


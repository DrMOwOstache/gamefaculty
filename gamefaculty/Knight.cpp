#include "Knight.h"

Knight::Knight() :Character{} {}

Knight::Knight(std::string name, int health, int level, float armor, int swordDamage) :Character{name,health,level}
{
	if (armor > 1)
		this->armor = 1;
	else if (armor < 0)
		this->armor = 0;
	else
		this->armor = armor;
	this->swordDamage = swordDamage;
}

Knight::~Knight()
{
	swordDamage = 0;
	armor = 0;
}

void Knight::takeDamage(int damage)
{
	armor -= damage / 50.0;
	if (armor < 0)
	{
		this->setHealth(0);
		armor = 0;
	}
}
#pragma once
#include "Character.h"

class Knight : public Character
{
private:
	float armor;
	int swordDamage;

public:

	Knight();
	Knight(std::string name, int health, int level, float armor, int swordDamage);
	~Knight();



	void takeDamage(int damage);
};
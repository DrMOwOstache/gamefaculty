#include <iostream>
#include <cstring>

#include "Character.h"

using namespace std;

Character::Character(const Character& other)
{
	this->name = other.name;
	this->level = other.level;
	this->health = other.health;
}

Character& Character::operator=(const Character& other)
{
	if (this != &other)
	{
		if (name.empty())
			name.erase();
		this->level = other.level;
		this->health = other.health;
		name = other.name;
	}
	return *this;
}

Character::Character()
{
	name = "";
	health = 0;
	level = 0;
}

Character::Character(std::string name, int health, int level)
{
	this->name = name;
	this->health = health;
	this->level = level;
}

void Character::setName(const std::string newName)
{
	name = newName;
}

void Character::setHealth(int newHealth) 
{
	health = newHealth;
}

void Character::setLevel(int newLevel)  
{
	level = newLevel;
}

std::string Character::getName()
{
	return this->name;
}

int Character::getHealth()
{
	return this->health;
}

int Character::getLevel()
{
	return this->level;
}

Character::~Character()
{
	if (!name.empty())
	{
		name.erase();
		health = 0;
		level = 0;
	}
}
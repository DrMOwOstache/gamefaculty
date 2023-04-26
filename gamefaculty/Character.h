#pragma once
#include <string>

class Character
{
public:
	Character();
	Character(std::string name, int health, int level);
	Character(const Character& other);
	virtual ~Character();

	void setName(const std::string newName);
	void setHealth(int newHealth);
	void setLevel(int newLevel);

	std::string getName();
	int getHealth();
	int getLevel();
	Character& operator=(const Character& other);

private:

	std::string name;
	int health;
	int level;
};


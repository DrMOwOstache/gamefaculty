#pragma once
#include <vector>
#include <string>
#include "Character.h"

class Wizard :public Character
{
private:
	int mana;
	std::vector<std::string> spells;
	int spellPower;

	int findIndexSpell(std::string spell);

public:

	Wizard();
	Wizard(std::string name, int health, int level, int m, std::vector<std::string> s, int sp);
	~Wizard();

	int getMana();
	int getSpellPower();
	std::vector<std::string> getSpellList();
	bool castSpell(std::string spell);
};
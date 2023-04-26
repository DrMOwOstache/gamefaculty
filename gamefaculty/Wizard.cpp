#include <vector>
#include <string>
#include "Wizard.h"

Wizard::Wizard(std::string name, int health, int level, int m, std::vector<std::string> s, int sp) : Character{ name,health,level }
{
	mana = m;
	spells = s;
	spellPower = sp;
}

Wizard::Wizard() :Character{} 
{
	mana = 0;
	spellPower = 0;
};

Wizard::~Wizard()
{
	if (!spells.empty())
	{
		for (int i = 0; i < spells.size(); i++)
			spells[i].erase();
		spells.clear();
	}
	mana = 0;
	spellPower = 0;
}

bool Wizard::castSpell(std::string spell)
{
	if (findIndexSpell(spell) != -1 && mana>10)
	{
		mana -= 10;
		return true;
	}
	return false;
}

//utils
int Wizard::findIndexSpell(std::string spell)
{
	for (int i = 0; i < spells.size(); i++)
		if (spell == spells[i])
			return i;
	return -1;
}

std::vector<std::string> Wizard::getSpellList()
{
	return spells;
}


int Wizard::getMana()
{
	return mana;
}

int Wizard::getSpellPower()
{
	return spellPower;
}


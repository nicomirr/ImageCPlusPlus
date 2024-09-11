#include "Wizard.h"
#include "RandomGen.h"

Wizard::Wizard(std::string name, int minPossibleDamage, int maxPossibleDamage, int minPossibleHealth, int maxPossibleHealth)
{
	RandomGen* randomGen = new RandomGen();

	SetName(name);
	SetWarriorClass("Hechicero");
	SetDamage(randomGen->RandomRange(minPossibleDamage, maxPossibleDamage));
	SetHealth(randomGen->RandomRange(minPossibleHealth, maxPossibleHealth));
	this->normalDamage = this->damage;
	this->critChance = 25;
	this->critMultiplier = 2;
	
	std::cout << "Hechicero " << this->name << " creado." << std::endl;;
	ShowStatistics();

	delete randomGen;

}

Wizard::~Wizard()
{
	std::cout << "Hechicero " << this->name << " destruido." << std::endl;;
}

bool Wizard::CheckCritSuccess()
{
	return (rand() % 100) + 1 <= this->critChance ? true : false;
}

bool Wizard::Attack(Warrior* warrior)
{
	bool isCrit = CheckCritSuccess();
	this->damage = this->normalDamage;

	if (isCrit)
	{
		this->damage *= this->critMultiplier;		
	}
	
	Warrior::Attack(warrior);

	return isCrit;	
}
#include "Wizard.h"
#include "RandomGen.h"

Wizard::Wizard(int minPossibleDamage, int maxPossibleDamage, int minPossibleHealth, int maxPossibleHealth)
{
	RandomGen* randomGen = new RandomGen();

	this->name = "Wizard";
	this->warriorType = WarriorType::Wizard;
	
	SetDamage(randomGen->RandomRange(minPossibleDamage, maxPossibleDamage));
	SetHealth(randomGen->RandomRange(minPossibleHealth, maxPossibleHealth));
	this->normalDamage = GetDamage();
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
	SetDamage(this->normalDamage);

	if (isCrit)
	{
		SetDamage(GetDamage() * this->critMultiplier);		
	}
	
	Warrior::Attack(warrior);

	return isCrit;	
}
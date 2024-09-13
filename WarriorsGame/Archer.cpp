#include "Archer.h"
#include "RandomGen.h"

Archer::Archer(int minPossibleDamage, int maxPossibleDamage, int minPossibleHealth, int maxPossibleHealth)
{
	RandomGen* randomGen = new RandomGen();

	this->name = "Archer";
	this->warriorType = WarriorType::Archer;
		
	SetDamage(randomGen->RandomRange(minPossibleDamage, maxPossibleDamage));
	SetHealth(randomGen->RandomRange(minPossibleHealth, maxPossibleHealth));

	this->normalDamage = GetDamage();
	this->damageMultiplier = 2;

	std::cout << "Arquero " << this->name << " creado." << std::endl;
	ShowStatistics();

	delete randomGen;

}

Archer::~Archer()
{
	std::cout << "Arquero " << this->name << " destruido." << std::endl;
}

bool Archer::CheckAttackSuccess()
{
	int randSuccessChance = rand() % 2;

	return randSuccessChance == 1 ? true : false;
}


bool Archer::Attack(Warrior* warrior)
{
	bool isSuccessfulAttack = CheckAttackSuccess();

	if (isSuccessfulAttack)
	{
		SetDamage(this->normalDamage);
		SetDamage(GetDamage() * damageMultiplier);

		Warrior::Attack(warrior);		
	}
	else
	{
		SetDamage(0);
	}

	return isSuccessfulAttack;
}

/*

PRAGMA ONCE:

HACE QUE EL ARCHIVO SE COPIE UNA VEZ.
*/
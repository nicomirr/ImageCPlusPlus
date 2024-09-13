#pragma once
#include "Warrior.h"
class Archer : public Warrior
{
	private:
		int normalDamage;
		int damageMultiplier;

		bool CheckAttackSuccess();

	public:

		Archer(int minPossibleDamage, int maxPossibleDamage, int minPossibleHealth, int maxPossibleHealth);

		~Archer();

		bool Attack(Warrior* warrior) override;

};


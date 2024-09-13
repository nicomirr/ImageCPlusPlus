#pragma once
#include "Warrior.h"

class Wizard : public Warrior
{
	private:
		int normalDamage;
		int critChance;
		int critMultiplier;

		bool CheckCritSuccess();

	public:

		Wizard(int minPossibleDamage, int maxPossibleDamage, 
			int minPossibleHealth, int maxPossibleHealth);

		~Wizard();

		bool Attack(Warrior* warrior) override;

		
};


#pragma once
#include "Warrior.h"

class Tank : public Warrior
{
	private:

		int shield;
		bool shieldDestroyed;

		void SetShield(int shield);
		int UseShieldAgainstAttack(int damage);

	public:

		Tank(int minPossibleDamage, int maxPossibleDamage, int minPossibleHealth, 
			int maxPossibleHealth, int minPossibleShield, int maxPossibleShield);

		~Tank();

		int GetShield();

		void ReceiveDamage(int damage) override;

		void ShowStatistics() override;
		
};
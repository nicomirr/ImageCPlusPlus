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

		void DrawWarriorIdle(bool isLeftSide, int yCursorPos) override;
		void DrawWarriorAttack(bool isLeftSide, int yCursorPos) override;
		virtual void DrawWarriorDamaged(bool isLeftSide, int yCursorPos,
			AttackState attackState) override;

		AttackState Attack(Warrior* warrior) override;

};


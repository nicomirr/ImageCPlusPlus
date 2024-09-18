#pragma once

#include <iomanip>
#include <Windows.h>
#include "RandomGen.h"
#include "CursorOptions.h"
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

		void DrawWarriorIdle(bool isLeftSide, int yCursorPos) override;
		void DrawWarriorAttack(bool isLeftSide, int yCursorPos) override;
		virtual void DrawWarriorDamaged(bool isLeftSide, int yCursorPos,
			AttackState attackState) override;

		AttackState Attack(Warrior* warrior) override;

		
};


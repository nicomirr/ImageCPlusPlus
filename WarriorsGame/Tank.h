#pragma once
#include <Windows.h>
#include <thread>
#include <iomanip>
#include "RandomGen.h"
#include "CursorOptions.h"
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
		void DrawWarriorIdle(bool isLeftSide, int yCursorPos) override;
		void DrawWarriorAttack(bool isLeftSide, int yCursorPos) override;
		virtual void DrawWarriorDamaged(bool isLeftSide, int yCursorPos,
			AttackState attackState) override;
};
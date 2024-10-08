#pragma once

#define NOMINMAX

#include <iostream>
#include <thread>
#include <chrono>
#include "Warrior.h"
#include "Tank.h"
#include "Archer.h"
#include "Wizard.h"
#include "RandomGen.h"

enum BattleMoment
{
	None = -1,
	IdleMoment,
	AttackMoment,
	End = 2,
};

static class Game
{
	private:

		static const int TOTAL_GROUPS = 2;
		static const int WARRIORS_IN_GROUPS = 4;

		static const int DRAWINGS_SPACING = 7;
		static int drawingsCurrentHeight;

		static int groupPoints[TOTAL_GROUPS];
		static Warrior* warriorGroups[TOTAL_GROUPS][WARRIORS_IN_GROUPS];  //DECLARACION ESTATICA
				
		static void InitGame(); 
		static void Gameloop();

		static void ResetPointers();
		static void GenerateRandomWarriors();
		static void DisplayGroups();

		static void BattleState(int& winnerGroup, int& groupsThatHaveAttacked, int firstAttackerGroup, 
			int defenderGroup, bool& attackerOnLeft, AttackState attackState, bool& inBattle, bool& isTie);

		static void DisplayIdleState(int firstAttackerGroup, int defenderGroup,
			bool attackerOnLeft, AttackState attackState);
		static void DisplayAttackState(int defenderGroup, int currentAttackingGroup, 
			bool attackerOnLeft, AttackState attackState);

		static void DrawIdleOrDead(int currentAttackingGroup, int currentWarrior,
						 int defenderGroup, bool attackerOnLeft, AttackState attackState);
		static void DrawAttack(int currentAttackingGroup, int currentWarrior,
			int defenderGroup, bool attackerOnLeft, AttackState attackState, 
			bool displayDamageDealth);
		static void Draw(Warrior* warriorAttacker, Warrior* warriorDefender,
			bool attackerIsOnLeft, BattleMoment battleMoment, AttackState attackState,
			bool showDamage);

		static void CheckForWinners(int& winnerGroup, int currentAttackingGroup, bool& inBattle);
		static void CheckForTie(bool& isTie, bool& inBattle);

		static void ResetCounterIfNeeded(int groupsThatHaveAttacked, int& currentAttackingGroup);

		static void PlayAgainQuestion();

		static void ResetPoints();
		static void DeletePointers();

	public:

		Game();
		virtual ~Game() = 0;

		static void Play();



};


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
		static Warrior* warriorGroups[TOTAL_GROUPS][WARRIORS_IN_GROUPS];  
				
		static void InitGame(); 
		static void ResetPointers();
		static void ResetPoints();
		static void Gameloop();
		static void GenerateRandomWarriors();
		static void DisplayGroups();
		static void Draw(Warrior* warriorAttacker, Warrior* warriorDefender,
			bool attackerIsOnLeft, BattleMoment battleMoment, AttackState attackState,
			bool showDamage);
		//static void DeletePointers();

	public:

		Game();
		virtual ~Game() = 0;

		static void Play();



};

